#include "Menger/Menger.hpp"

#include <gtest/gtest.h>
#include <string>

namespace isim
{
/*TEST(menger, constructor)
{
	const int sideLength = 3;
	const Vector point = Vector(0, 1, 2);
	const int nbIteration = 0;

	Menger menger(sideLength, point, nbIteration);
	const int expectedNumberOfCubes = 20;
	auto it = 0;
	for (auto& cube : menger.m_cubes)
	{
		if (cube.get() != nullptr)
		{
			it++;
		}
	}
	ASSERT_EQ(expectedNumberOfCubes, it);

	const double expectedLengthCube = 1;

	for (auto& cube : menger.m_cubes)
	{
		ASSERT_EQ(expectedLengthCube, cube->getSideLength());
	}

	ASSERT_EQ(menger.getSideLength(), sideLength);
	ASSERT_EQ(menger.getBottomLeft(), point);
}

TEST(menger, transform)
{
	const int sideLength = 3;
	const Vector point = Vector(0, 1, 2);
	const int nbIteration = 0;
	Menger menger(sideLength, point, nbIteration);

	const double expectedLengthCube = sideLength / 3;
	const double expectedLength = sideLength;

	Vector newPoint(0, 0, 0);
	menger.transform(newPoint);
	ASSERT_EQ(expectedLength, menger.getSideLength());

	for (auto& cube : menger.m_cubes)
	{
		ASSERT_EQ(expectedLengthCube, cube->getSideLength());
	}
}

TEST(menger, reset)
{
	const double sideLength = 3;
	const Vector point = Vector(0, 1, 2);
	const int nbIteration = 0;
	Menger menger(sideLength, point, nbIteration);

	Vector newPoint(0, 0, 0);
	menger.transform(newPoint);
	menger.reset();

	ASSERT_EQ(sideLength, menger.getSideLength());
	ASSERT_EQ(point, menger.m_center);

	Menger mengerOrigin(sideLength, point, nbIteration);
	const double expectedCubeLength = sideLength / 3;
	for (const auto& m_cube : menger.m_cubes)
	{
		ASSERT_EQ(m_cube->getSideLength(), expectedCubeLength);
	}
}

TEST(menger, intersect)
{
	const double sideLength = 3;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 0;
	Menger menger(sideLength, center, nbIteration);

	Ray ray(Vector(-5, -1, -1), Vector(1, 0, 0));

	ASSERT_TRUE(menger.isIntersected(ray));
	Vector expected(-1.5, -1, -1);

	ASSERT_EQ(ray.endpos, expected);
}

TEST(menger, getCenter)
{
	const double sideLength = 3;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 0;
	Menger menger(sideLength, center, nbIteration);

	Ray ray(Vector(-5, -1, -1), Vector(1, 0, 0));

	menger.isIntersected(ray);

	Vector obtainedCenter = ray.obj->getPosition();
	Vector expectedCenter(-1, -1, -1);
	ASSERT_EQ(obtainedCenter, expectedCenter);
}

TEST(menger, intersect2Generation)
{
	const double sideLength = 3;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 2;
	Menger menger(sideLength, center, nbIteration);

	Ray ray(Vector(-5, -1, -1), Vector(1, 0, 0));

	menger.isIntersected(ray);
	auto cube = static_cast<const CubeBox*>(ray.obj);
	ASSERT_EQ(cube->getSideLength(), sideLength / 27);
}

TEST(menger, intersect3Generation)
{
	const double sideLength = 3;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 3;
	Menger menger(sideLength, center, nbIteration);

	Ray ray(Vector(-5, -1, -1), Vector(1, 0, 0));

	menger.isIntersected(ray);
	auto cube = static_cast<const CubeBox*>(ray.obj);
	ASSERT_EQ(cube->getSideLength(), sideLength / (std::pow(3, nbIteration + 1)));
}


TEST(menger, intersect4Generation)
{
	const double sideLength = 4;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 3;
	Menger menger(sideLength, center, nbIteration);

	Ray ray(Vector(-5, -1, -1), Vector(1, 0, 0));

	menger.isIntersected(ray);
	auto cube = static_cast<const CubeBox*>(ray.obj);
	ASSERT_EQ(cube->getSideLength(), sideLength / (std::pow(3, nbIteration + 1)));
}*/
};