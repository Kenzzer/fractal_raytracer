#include "Object/Transform.hpp"
#include "Parser.hpp"

namespace isim
{
class EmptyTransform : public Transform
{
public:
	virtual bool isIntersected(Ray&) const override
	{
		return false;
	}

	EmptyTransform(const nlohmann::json& json) : Transform(json)
	{
	}

	EmptyTransform(const Vector& position) : Transform(position)
	{
	}
};

TEST(Transform, constructor)
{
	EmptyTransform empty(Vector{12, 26, 43});
}

TEST(Transform, constructorJson)
{
	EmptyTransform empty(TEST_JSON_OPEN("resources/tests/Object/Transform.json"));
}

};