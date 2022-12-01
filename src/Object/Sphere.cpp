#include "Sphere.hpp"
#include "Material/UniformMaterial.hpp"

#include <cmath>

namespace isim
{
static ObjectFactory<Sphere> factory("sphere");

Sphere::Sphere(const nlohmann::json& json) : MeshObject(json),
		m_radiusSqr(std::pow(json["radius"], 2.0)),
		m_mat(new UniformMaterial(json["material"]))
{
}

const std::unique_ptr<Material>& Sphere::getMaterial(const Ray&) const
{
	return m_mat;
}

bool Sphere::isIntersected(Ray& ray) const
{
	Vector diff = ray.startpos - getPosition();
	float a = ray.dir.DotProduct(ray.dir);
	float b = 2.0 * diff.DotProduct(ray.dir);
	float c = diff.DotProduct(diff) - m_radiusSqr;

	float delta = (b * b) - (4.0 * a * c);
	if (delta < 0.0)
	{
		return false;
	}

	float hit1 = (-b + std::sqrt(delta)) / (2.0 * a);
	float hit2 = (-b - std::sqrt(delta)) / (2.0 * a);

	auto hit = std::fmin(hit1, hit2);
	if (hit < 0)
	{
		return false;
	}

	ray.endpos = ray.startpos + (ray.dir * hit);
	ray.distance = hit;
	ray.obj = this;

	return true;
}

Vector Sphere::getNormal(const Ray& ray) const
{
	return (ray.endpos - getPosition()).GetNormalize();
}
};