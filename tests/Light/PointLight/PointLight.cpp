#include "Object/Light/PointLight.hpp"
#include "Parser.hpp"

#include <gtest/gtest.h>
#include <fstream>

namespace isim
{
TEST(PointLight, constructorJson)
{
	PointLight pointLight(TEST_JSON_OPEN("resources/tests/Object/Light.json"));
	ASSERT_EQ(pointLight.getIntensity(), 1.0);
	ASSERT_EQ(pointLight.getPosition(), Vector(1, 1, 1));
}

TEST(PointLight, constructor)
{
	PointLight pl(Vector(1, 1, 1), 1.0);
	ASSERT_EQ(pl.getIntensity(), 1.0);
	ASSERT_EQ(pl.getPosition(), Vector(1, 1, 1));
}

TEST(PointLight, setIntensity)
{
	PointLight pl(Vector(1, 1, 1), 1.0);

	auto intensity = 2.0;

	pl.setIntensity(intensity);

	ASSERT_EQ(pl.getIntensity(), intensity);
}

TEST(PointLight, setPosition)
{
	PointLight pl(Vector(1, 1, 1), 1.0);

	Vector position(1, 1, 0);

	pl.setPosition(position);

	ASSERT_EQ(pl.getPosition(), position);
}
};