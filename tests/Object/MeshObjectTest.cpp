#include "Object/MeshObject.hpp"
#include "Material/UniformMaterial.hpp"

#include "Parser.hpp"

namespace isim
{

UniformMaterial* placeholder = new UniformMaterial(Color{0, 0, 0}, 0);
std::unique_ptr<Material> placeholderMat(placeholder);

class EmptyVisibleObject : public MeshObject
{
public:
	virtual bool isIntersected(Ray&) const override
	{
		return false;
	}

	virtual const std::unique_ptr<Material>& getMaterial(const Ray&) const override
	{
		return placeholderMat;
	}

	virtual Vector getNormal(const Ray&) const override
	{
		return Vector{0, 0, 0};
	}

	EmptyVisibleObject(const nlohmann::json& json) : MeshObject(json)
	{
	}

	EmptyVisibleObject(const Vector& position) : MeshObject(position)
	{
	}
};

TEST(MeshObject, constructor)
{
	EmptyVisibleObject empty(Vector{12, 26, 43});
}

TEST(MeshObject, constructorJson)
{
	EmptyVisibleObject empty(TEST_JSON_OPEN("resources/tests/Object/MeshObject.json"));
}
};