#include "Object/Sphere.hpp"
#include "Parser.hpp"

namespace isim
{
TEST(Sphere, constructorJson)
{
	Sphere empty(TEST_JSON_OPEN("resources/tests/Object/Sphere.json"));
}
};