#include "Object/Cube/Cube.hpp"
#include "Scene/Factory/Dictionary.hpp"
#include "Parser.hpp"

#include <gtest/gtest.h>

namespace isim
{
TEST(cube, constructor)
{
	Vector position(0, 0, 0);
	double length = 2;
	Cube cube(position, length);

	ASSERT_EQ(cube.getSideLength(), length);
	ASSERT_EQ(cube.getPosition().x, 0);
	ASSERT_EQ(cube.getPosition().y, 0);
	ASSERT_EQ(cube.getPosition().z, 0);
}

TEST(cube, constructorJson)
{
	Cube cube(TEST_JSON_OPEN("resources/tests/Object/Cube.json"));
}

TEST(cube, factory)
{
	auto cube = TheFactories["cube"]->New(TEST_JSON_OPEN("resources/tests/Object/Cube.json"));
	ASSERT_NE(dynamic_cast<Cube*>(cube), nullptr);
	delete cube;
}

TEST(cube, equals)
{
	Cube s1(Vector(0, 0, 0), 2);
	ASSERT_EQ(s1, s1);
}

TEST(cube, not_equals)
{
	Cube s1(Vector(0, 0, 0), 2);
	Cube s2(Vector(0, 1, 0), 2);
	ASSERT_NE(s1, s2);
}

TEST(cube, setter)
{
	Vector position(0, 0, 0);
	double length = 2;
	Cube cube(position, length);
	double newLength = 1;
	cube.setSideLength(newLength);

	ASSERT_EQ(cube.getSideLength(), newLength);
}

TEST(cube, isEmpty)
{
	Vector position(0, 0, 0);
	double length = 2;
	Cube cube(position, length);

	ASSERT_FALSE(cube.isEmpty());
	cube.setIsEmpty(true);
	ASSERT_TRUE(cube.isEmpty());
}

TEST(cubeIntersect, intersectFromLeft)
{
	const Vector origin(0, 0, 0);
	const double length = 2;
	Cube cube(origin, length);

	Ray ray = Ray(Vector(-4, 0, 0), Vector(1, 0, 0));

	ASSERT_TRUE(cube.isIntersected(ray));

	Vector expected(-1, 0, 0);
	ASSERT_EQ(ray.endpos, expected);
	ASSERT_EQ(cube.getNormal(ray), expected);
}

TEST(cubeIntersect, intersectFromRight)
{
	const Vector origin(0, 0, 0);
	const double length = 2;
	Cube cube(origin, length);

	Ray ray(Vector(4, 0, 0), Vector(-1, 0, 0));

	ASSERT_TRUE(cube.isIntersected(ray));

	Vector expected(1, 0, 0);
	ASSERT_EQ(ray.endpos, expected);

	ray.reset();
	const double epsilon = 0.01;
	for (double d = 0; d < (length / 2) - epsilon; d += epsilon)
	{
		for (double e = -(length / 2); e < (length / 2) - epsilon; e += epsilon)
		{
			Ray testRay = ray;
			testRay.startpos.y += e;
			testRay.startpos.z += d;
			std::cout << testRay.startpos << std::endl;
			ASSERT_TRUE(cube.isIntersected(testRay));
			Vector expectedCollision = expected;
			expectedCollision.y += e;
			expectedCollision.z += d;
			ASSERT_EQ(testRay.endpos, expectedCollision);
		}
	}
}

TEST(cubeIntersect, intersectFromBehind)
{
	const Vector origin(0, 0, 0);
	const double length = 2;
	Cube cube(origin, length);

	Ray ray = Ray(Vector(0, -4, 0), Vector(0, 1, 0));

	ASSERT_TRUE(cube.isIntersected(ray));

	Vector expected(0, -1, 0);
	ASSERT_EQ(ray.endpos, expected);
}

TEST(cubeIntersect, intersectFromFront)
{
	const Vector origin(0, 0, 0);
	const double length = 2;
	Cube cube(origin, length);

	Ray ray(Vector(0, 4, 0), Vector(0, -1, 0));

	ASSERT_TRUE(cube.isIntersected(ray));

	Vector expected(0, 1, 0);
	ASSERT_EQ(ray.endpos, expected);
}

TEST(cubeIntersect, intersectFromTop)
{
	const Vector origin(0, 0, 0);
	const double length = 2;
	Cube cube(origin, length);

	Ray ray(Vector(0, 0, 4), Vector(0, 0, 1));

	ASSERT_TRUE(cube.isIntersected(ray));

	Vector expected(0, 0, 1);
	ASSERT_EQ(ray.endpos, expected);
}

TEST(cubeIntersect, intersectFromBottom)
{
	const Vector origin(0, 0, 0);
	const double length = 2;
	Cube cube(origin, length);

	Ray ray(Vector(0, 0, -4), Vector(0, 0, -1));

	ASSERT_TRUE(cube.isIntersected(ray));

	Vector expected(0, 0, -1);
	ASSERT_EQ(ray.endpos, expected);
}

TEST(cubeIntersect, intersectFroBottomLeft)
{
	const Vector origin(0, 0, 0);
	const double length = 2;
	Cube cube(origin, length);

	Ray ray(Vector(-4, -4, -4), Vector(1, 1, 1));
	ray.startpos = Vector(-4, -4, -4);
	ray.dir = Vector(1, 1, 1);

	ASSERT_TRUE(cube.isIntersected(ray));

	Vector expected(-1, -1, -1);
	ASSERT_EQ(ray.endpos, expected);
	ASSERT_EQ(ray.obj, &cube);
}

TEST(cubeIntersect, randomIntersect)
{
	const Vector origin(0, 0, 0);
	const double length = 4;
	Cube cube(origin, length);

	Ray ray(Vector(-4, 0, 0), Vector(2, 0, 1));

	ASSERT_TRUE(cube.isIntersected(ray));

	Vector expected(-2, 0, 1);
	ASSERT_EQ(ray.endpos, expected);
}

TEST(cubeIntersect, noIntersect)
{
	const Vector origin(0, 0, 0);
	const double length = 4;
	Cube cube(origin, length);

	Ray ray(Vector(0, 5, 0), Vector(1, 0, 0));

	ASSERT_FALSE(cube.isIntersected(ray));
}
};
