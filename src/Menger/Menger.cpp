#include "Menger.hpp"
#include "Material/UniformMaterial.hpp"
#include "Profiler/Profiler.hpp"

#include <stack>

namespace isim
{
static Vector spongeCubesPos[20] = {Vector(-1,-1,-1),
Vector(-1,-1,0),
Vector(-1,-1,1),
Vector(-1,0,-1),
Vector(-1,0,1),
Vector(-1,1,-1),
Vector(-1,1,0),
Vector(-1,1,1),
Vector(0,-1,-1),
Vector(0,-1,1),
Vector(0,1,-1),
Vector(0,1,1),
Vector(1,-1,-1),
Vector(1,-1,0),
Vector(1,-1,1),
Vector(1,0,-1),
Vector(1,0,1),
Vector(1,1,-1),
Vector(1,1,0),
Vector(1,1,1)};
static ObjectFactory<Menger> factory("menger");

MaterialInfo Menger::Mat::getInfo(const Ray& ray)
{
	auto info = UniformMaterial::getInfo(ray);
	auto normal = ((MeshObject*)ray.obj)->getNormal(ray);
	if (normal.x != 0 || normal.y != 0)
	{
		info.color *= 0.8;
	}
	return info;
}

Menger::Menger(double sideLength, const Vector& center, int nbIterations) : CubeBox(center, sideLength),
		m_nbIterations(nbIterations),
		m_originLength(m_maxs.x * 2),
		m_mat(new UniformMaterial(Color(200,200,200), 1.0))
{
}

Menger::Menger(const nlohmann::json& json) : CubeBox(json),
		m_nbIterations(json["iterations"]),
		m_originLength(m_maxs.x * 2),
		m_mat(new Menger::Mat(json["material"]))
{
}

bool Menger::isIntersected(Ray& ray) const
{
	if (!CubeBox::isIntersected(ray))
	{
		return false;
	}
	ray.reset();

	struct depthInfo
	{
		depthInfo() : parsed(0), position(0)
		{
			for (int i = 0; i < 5; i++)
			{
				cubeIt[i].second = 20;
			}
		}
		void insert(double distance, int index)
		{
			if (parsed == 5)
			{
				return;
			}
			cubeIt[this->parsed++] = {distance, index};
		}
		void sort()
		{
			std::sort(std::begin(this->cubeIt), std::end(this->cubeIt), [](const std::pair<double,std::uint8_t>& left, const std::pair<double,std::uint8_t>& right)
			{
				return left.first < right.first && left.second != 20;
			});
			/*
			for (int i = 0; i < 5; i++)
			{
				std::cout << "distance: " << cubeIt[i].first << '|' << std::to_string(cubeIt[i].second) << std::endl;
			}*/
		}
		std::uint8_t parsed;
		std::uint8_t position;
		Vector center;
		std::pair<double, std::uint8_t> cubeIt[5];
	};

	auto pos = getPosition();
	if (!m_cubes.contains(ray.threadId))
	{
		m_cubes[ray.threadId] = std::vector<std::unique_ptr<CubeBox>>(20);
		auto& cubes = m_cubes[ray.threadId];
		for (auto it = 0; it < 20; it++)
		{
			cubes[it].reset(new CubeBox(pos, 2.0));
			cubes[it]->setMaterial(&m_mat);
		}
	}
	auto& cubes = m_cubes[ray.threadId];

	int depth = 1;
	double currentLength = m_originLength;
	depthInfo firstDepth;
	Ray cubeRay = ray;

	transform(pos, currentLength / 3, cubes);
	for (auto it = 0; it < 20; it++)
	{
		if (cubes[it]->isIntersected(cubeRay))
		{
			if (cubeRay.distance > 0)
			{
				firstDepth.insert(cubeRay.distance, it);
			}
			else
			{
				firstDepth.insert((cubeRay.startpos - cubes[it]->getPosition()).GetLength(), it);
			}
		}
	}
	firstDepth.center = getPosition();
	firstDepth.sort();
	std::stack<depthInfo> depthStack;
	depthStack.push(firstDepth);
	//assert(false);
	while (depth >= 1)
	{
		if (depthStack.top().position >= depthStack.top().parsed)
		{
			depthStack.pop();
			currentLength *= 3;
			depth--;
			continue;
		}

		currentLength /= 3;
		depth++;
		if (depth <= m_nbIterations)
		{
			auto center = depthStack.top().center;
			auto cubePos = spongeCubesPos[depthStack.top().cubeIt[depthStack.top().position++].second];
			auto newCenter = center + cubePos * currentLength;
			transform(newCenter, currentLength / 3, cubes);

			depthInfo nextDepth;
			Ray cubeRay = ray;
			for (auto it = 0; it < 20; it++)
			{
				if (cubes[it]->isIntersected(cubeRay))
				{
					nextDepth.insert(cubeRay.distance, it);
				}
			}

			nextDepth.center = newCenter;
			nextDepth.sort();
			depthStack.push(nextDepth);
		}
		else
		{
			if (depthStack.top().position >= 0 && depthStack.top().position < depthStack.top().parsed && depthStack.top().parsed <= 5)
			{
				auto cubeIt = depthStack.top().cubeIt[depthStack.top().position].second;

				ray.distance = depthStack.top().cubeIt[depthStack.top().position].first;
				ray.endpos = ray.startpos + ray.dir * ray.distance;
				//std::cout << std::to_string(cubeIt) << std::endl;
				ray.obj = cubes[cubeIt].get();
			}
			break;
		}
	}
	return ray.didHit();
}

const std::unique_ptr<Material>& Menger::getMaterial(const Ray&) const
{
	return m_mat;
}

void Menger::transform(const Vector& center, double cubeLength, const std::vector<std::unique_ptr<CubeBox>>& cubes) const
{
	for (auto it = 0; it < 20; it++)
	{
		cubes[it]->setPosition(center + (spongeCubesPos[it] * cubeLength));
		cubes[it]->setSideLength(cubeLength);
	}
}

void Menger::setIterations(int iter)
{
	m_nbIterations = iter;
}
};