#include "Object/Light/PointLight.hpp"
#include "Scene.hpp"
#include "Profiler/Profiler.hpp"

#include "Object/Box/CubeBox.hpp"

#include <algorithm>
#include <cmath>

namespace isim
{
Scene::Scene(const nlohmann::json& json) : m_maxDepth(json["depth"]),
		m_ambientLightIntensity(json["ambient"])
{
	addLights(json["lights"]);
	addCameras(json["cameras"]);
	addObjects(json["objects"]);
}

Scene::Scene() : m_maxDepth(2),
		m_ambientLightIntensity(0.3)
{
}

void Scene::addCameras(const nlohmann::json& cameras)
{
	for (const auto& camera : cameras)
	{
		auto obj = TheFactories["camera"]->New(camera);
		if (dynamic_cast<Camera*>(obj) != nullptr)
		{
			m_cameras.emplace(static_cast<Camera*>(obj));
		}
		else if (obj != nullptr)
		{
			delete obj;
		}
	}
}

void Scene::addLights(const nlohmann::json& lights)
{
	for (const auto& light : lights)
	{
		auto obj = TheFactories[light["type"]]->New(light);
		if (dynamic_cast<Light*>(obj) != nullptr)
		{
			m_lights.emplace(static_cast<Light*>(obj));
		}
		else if (obj != nullptr)
		{
			delete obj;
		}
	}
}

void Scene::addObjects(const nlohmann::json& objects)
{
	for (const auto& object : objects)
	{
		auto obj = TheFactories[object["type"]]->New(object);
		if (dynamic_cast<MeshObject*>(obj) != nullptr)
		{
			m_objects.emplace(static_cast<MeshObject*>(obj));
		}
		else if (obj != nullptr)
		{
			delete obj;
		}
	}
}

const std::set<std::unique_ptr<Camera>>& Scene::getCameras() const
{
	return m_cameras;
}

const std::set<std::unique_ptr<const Light>>& Scene::getLights() const
{
	return m_lights;
}

const std::set<std::unique_ptr<const MeshObject>>& Scene::getObjects() const
{
	return m_objects;
}

int Scene::getDepth() const
{
	return m_maxDepth;
}

Color Scene::castRay(Ray& ray, int depth) const
{
	static Color COLOR_VOID = Color(0, 0, 0, 255);

	if (depth == 0)
	{
		return COLOR_VOID;
	}

	this->castRayObjects(ray);
	if (ray.didHit())
	{
		return this->castRayLights(ray, depth);
	}
	return COLOR_VOID;
}

void Scene::castRayObjects(Ray& ray) const
{
	for (auto it = m_objects.begin(); it != m_objects.end(); it++)
	{
		Ray newRay = ray;
		if ((*it)->isIntersected(newRay))
		{
			if (newRay.distance < ray.distance)
			{
				ray = newRay;
			}
		}
	}
}

Color Scene::castRayLights(Ray& ray, int depth) const
{
	auto obj = static_cast<const MeshObject*>(ray.obj);
	const auto info = obj->getMaterial(ray)->getInfo(ray);
	auto normal = obj->getNormal(ray);

	double Ld = 0;
	double Ls = 0;
	Color currColor = info.color;
	for (const auto& light : m_lights)
	{
		Ray lightRay(ray.endpos, light->getPosition() - ray.endpos);
		lightRay.startpos += normal * 0.1;
		lightRay.threadId = ray.threadId;
		this->castRayObjects(lightRay);

		if (!lightRay.didHit())
		{
			Ld += std::max(0.0, info.kd * normal.DotProduct(lightRay.dir) * light->getIntensity());

			auto h = (lightRay.dir - ray.dir).GetNormalize();
			Ls += info.ks * light->getIntensity() * std::pow(std::max(normal.DotProduct(h), 0.0), info.ns);
		}

		/*Ray reflectRay(ray.endpos, (ray.dir - normal * 2.0 * ray.dir.DotProduct(normal)));
		reflectRay.threadId = ray.threadId;
		Color rc = this->castRay(reflectRay, depth - 1);
		if (reflectRay.didHit())
		{
			currColor = currColor + rc * info.kr;
		}*/
	}

	auto v = (ray.startpos - ray.endpos).GetNormalize();
	auto vr = (normal * (normal.DotProduct(v) * 2)) - v;
	Ray reflectRay(ray.endpos, vr);
	reflectRay.startpos += normal * 0.1;
	reflectRay.threadId = ray.threadId;
	auto Lm = this->castRay(reflectRay, depth - 1);

	double lightComposition = m_ambientLightIntensity * info.ka + Ld + Ls;
	Color r = (currColor * lightComposition) + (Lm * info.km);
	return r;
}
};