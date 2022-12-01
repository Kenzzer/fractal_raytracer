#pragma once

#include "MeshObject.hpp"
#include "Material/Material.hpp"

namespace isim
{
class Sphere : public MeshObject
{
public:
	virtual const std::unique_ptr<Material>& getMaterial(const Ray& ray) const override;
	virtual bool isIntersected(Ray& ray) const override;
	virtual Vector getNormal(const Ray& ray) const override;
protected:
	double m_radiusSqr;
	std::unique_ptr<Material> m_mat;

	friend class ObjectFactory<Sphere>;
	Sphere(const nlohmann::json& json);

private:
	FRIEND_TEST(Sphere, constructorJson);
};
};