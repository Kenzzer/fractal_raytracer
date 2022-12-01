#pragma once

#include "Transform.hpp"
#include "Vector/Vector.hpp"
#include "Material/Material.hpp"

#include <memory>

namespace isim
{
struct Ray;

class MeshObject : public Transform
{
public:
	virtual const std::unique_ptr<Material>& getMaterial(const Ray& ray) const = 0;
	virtual Vector getNormal(const Ray& ray) const = 0;
	bool operator==(const MeshObject& B) const;
protected:
	explicit MeshObject(const nlohmann::json& json);
	MeshObject(const Vector& position);
private:
	FRIEND_TEST(MeshObject, constructor);
	FRIEND_TEST(MeshObject, constructorJson);
};
};