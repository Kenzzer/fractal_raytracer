#pragma once

#include "Object/Camera/Camera.hpp"
#include "Object/Light/Light.hpp"
#include "Image/Color.hpp"
#include "Object/MeshObject.hpp"
#include "Factory/Dictionary.hpp"
#include "Ray.hpp"

#include <memory>
#include <set>

namespace isim
{
class Scene
{
public:
	explicit Scene(const nlohmann::json& json);

	void addLights(const nlohmann::json& lights);
	void addCameras(const nlohmann::json& cameras);
	void addObjects(const nlohmann::json& objects);
	const std::set<std::unique_ptr<Camera>>& getCameras() const;
	const std::set<std::unique_ptr<const Light>>& getLights() const;
	const std::set<std::unique_ptr<const MeshObject>>& getObjects() const;
	int getDepth() const;

	Color castRay(Ray& ray, int depth = 1) const;
	Color castRayLights(Ray& ray, int depth) const;
	void castRayObjects(Ray& ray) const;

	void bruh(const Vector& center, const int i);

protected:
	const int m_maxDepth;
	const double m_ambientLightIntensity;
	std::set<std::unique_ptr<Camera>> m_cameras;
	std::set<std::unique_ptr<const Light>> m_lights;
	std::set<std::unique_ptr<const MeshObject>> m_objects;
	Scene();

private:
	FRIEND_TEST(Scene, addCameras);
	FRIEND_TEST(Scene, addLights);
	FRIEND_TEST(Scene, addObjects);
	FRIEND_TEST(Scene, constructorJson);
};
}