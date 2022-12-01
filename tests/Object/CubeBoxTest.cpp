#include "Object/Box/CubeBox.hpp"

#include <gtest/gtest.h>

namespace isim
{
TEST(CubeBox, insideCollision)
{
	Vector pos(0, 100, 0);
	double length = 50.0;
	CubeBox box(pos, length);

	Vector rayPos(0, 0, 0);
	Vector rayDir(0, 1, 0);
	Ray cubeRay(rayPos, rayDir);

	ASSERT_EQ(box.isIntersected(cubeRay), true);
	ASSERT_EQ(cubeRay.didHit(), true);

	rayPos = cubeRay.endpos;
	rayDir = Vector(0, -1, 0);
	std::cout << rayPos << std::endl;
	cubeRay = Ray(rayPos, rayDir);
	ASSERT_EQ(box.isIntersected(cubeRay), false);
	ASSERT_EQ(cubeRay.didHit(), false);	

	rayPos = Vector(0, 100, 0);
	cubeRay = Ray(rayPos, rayDir);
	ASSERT_EQ(box.isIntersected(cubeRay), true);
	ASSERT_EQ(cubeRay.didHit(), true);
	ASSERT_EQ(cubeRay.distance, 0.0);
}
};