#include "Scene/Scene.hpp"
#include "Image/PNG.hpp"
#include "Profiler/Profiler.hpp"
#include "Menger/Menger.hpp"

#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace isim;

// Thread pools
struct renderJob
{
	float l;
	float r;
	float t;
	float b;
	float focal;
	Vector startPos;
	Vector up;
	Vector reversedDir;
	Vector forward;
	std::uint32_t width;
	std::uint32_t height;
	Color* pixels;

	std::uint32_t startHeight;
	std::uint32_t endHeight;
};

struct renderResult
{
	Color color;
	std::uint32_t pos;
};

static Scene* renderScene = nullptr;

static std::vector<std::thread> threadsPool;
static int threadsCount;
static bool terminate = false;

static std::queue<renderJob> renderQueue;
static std::mutex renderQueueMutex;
static std::condition_variable renderQueueMutexCv;

static int renderDone;
static std::mutex resultQueueMutex;
static std::condition_variable resultQueueMutexCv;

void render_loop(int threadId)
{
	while (true)
	{
		renderJob job;
		{
        	std::unique_lock<std::mutex> lock(renderQueueMutex);
        	renderQueueMutexCv.wait(lock, []{return !renderQueue.empty();});
			if (terminate)
			{
				return;
			}
        	job = renderQueue.front();
        	renderQueue.pop();
		}

		auto MAX_DEPTH = renderScene->getDepth();

		for (std::uint32_t x = 0; x < job.width; x++)
		{
			for (std::uint32_t y = job.startHeight; y < job.endHeight; y++)
			{
				float u = job.l + ((job.r-job.l)*(x + 0.5)) / job.width;
				float v = job.b + ((job.t-job.b)*(y + 0.5)) / job.height;

				auto pos = (job.height - 1 - y) * job.width + x;
				Ray ray(job.startPos, job.reversedDir * -job.focal + job.up * u + job.forward * v);
				ray.threadId = threadId;
				job.pixels[pos] = renderScene->castRay(ray, MAX_DEPTH);
			}
		}
		renderResult result;
		{
        	std::unique_lock<std::mutex> lock(resultQueueMutex);
			renderDone++;
			resultQueueMutexCv.notify_all();
		}
	}
}

int pool_amount()
{
	return threadsCount;
}

void setup_pool(Scene* scene)
{
	std::cout << "Setting up rendering pool...";
	for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
	{
		std::cout << "\nCreated render thread: " << i;
		threadsPool.push_back(std::thread(render_loop, threadsCount++));
	}
	std::cout << std::endl;
	renderScene = scene;
}

void shutdown_pool()
{
	{
		std::unique_lock<std::mutex> lock(renderQueueMutex);
		renderJob emptyJob;
		renderQueue.push(emptyJob);
		terminate = true;
		renderQueueMutexCv.notify_all();
	}
	std::cout << "Shutting down render pool..." << std::endl;
	for (auto& thread: threadsPool)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

const double RADIAN = 0.01745329251;
void snapshot(const std::unique_ptr<Camera>& camera, const std::unique_ptr<PNG>& png);

int main(int argc, char** argv)
{
	if (argc != 3 || !argv[1][0] || !argv[2][0])
	{
		return 0;
	}
	std::fstream file(argv[1]);
	assert(file.is_open());
	std::unique_ptr<PNG> png = std::make_unique<PNG>(argv[2], 2560, 1440);

	Scene scene(nlohmann::json::parse(file));
	setup_pool(&scene);

	auto& camera = *scene.getCameras().begin();

	auto& objs = scene.getObjects();
	for (auto& obj : objs)
	{
		auto sponge = dynamic_cast<const Menger*>(obj.get());
		if (sponge != nullptr)
		{
			auto ratio = (((sponge->getPosition() - camera->getPosition()).GetLength())/sponge->getSideLength());
			int nbIter = 0;
			if (ratio >= 1.0)
			{
				nbIter = std::floor(1.0 / ratio * 10) + 2;
			}
			else
			{
				nbIter = std::floor((1.0 - ratio) / 0.1) + 10;
			}
			((Menger*)sponge)->setIterations(nbIter);
		}
	}

	snapshot(camera, png);

	shutdown_pool();
}

void snapshot(const std::unique_ptr<Camera>& camera, const std::unique_ptr<PNG>& png)
{
	float hh = std::tan(camera->getFov() * RADIAN / 2.0) * camera->getFocal();
	float hw = static_cast<float>(png->GetWidth()) / static_cast<float>(png->GetHeight()) * hh;

	float l = -hw, r = hw, t = hh, b = -hh;

	auto width = png->GetWidth(), height = png->GetHeight();

	Vector reversedDir = camera->getPosition() - camera->getFocus();
	reversedDir.Normalize();

	Vector up = camera->getUp().Cross(reversedDir);
	up.Normalize();

	Vector forward = reversedDir.Cross(up);
	forward.Normalize();

	renderJob job;
	job.l = l;
	job.r = r;
	job.t = t;
	job.b = b;
	job.startPos = camera->getPosition();
	job.focal = camera->getFocal();
	job.up = up;
	job.reversedDir = reversedDir;
	job.forward = forward;
	job.height = height;
	job.width = width;
	job.pixels = png->GetPixels();
	auto threadCount = pool_amount();
	{
		std::unique_lock<std::mutex> lock(resultQueueMutex);
		renderDone = 0;
		for (auto i = 0; i < threadCount; i++)
		{
			auto chunkSize = height / threadCount;
			job.startHeight = chunkSize * i;
			job.endHeight = (i == threadCount) ? height : chunkSize * (i + 1);

			std::unique_lock<std::mutex> lock(renderQueueMutex);
			renderQueue.push(job);
			renderQueueMutexCv.notify_one();
		}
	}

	for (auto k = 0; k < threadCount;)
	{
		{
			std::unique_lock<std::mutex> lock(resultQueueMutex);
			resultQueueMutexCv.wait(lock, [t=threadCount]
			{
				return renderDone == t;
			});
			k = renderDone;
		}
	}
	png->OnUpdate();
}