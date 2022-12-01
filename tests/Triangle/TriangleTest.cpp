#include "Object/Triangle/Triangle.hpp"
#include "Vector/Vector.hpp"
#include "Pyramide/Pyramide.hpp"

#include <gtest/gtest.h>

namespace isim
{
bool findPoint(const std::vector<Vector>& result, Vector key);
void assertIfPointIsOnTheList(const std::vector<Vector>& listOfPositions, const Vector& point);

TEST(Triangle, contructor)
{
	const double length = 1;
	Vector direction(0, 1, 0);
	const double height = 3;
	Vector center(0, 0, 0);
	Triangle triangle(center, length, height, direction);

	ASSERT_EQ(triangle, triangle);
}

TEST(Triangle, getter)
{
	const double length = 1;
	const double height = 3;
	Vector center(0, 0, 0);
	Vector direction(0, 1, 0);
	Triangle triangle(center, length, height, direction);

	ASSERT_EQ(triangle.getHeight(), height);
	ASSERT_EQ(triangle.getLength(), length);
	ASSERT_EQ(triangle.getPosition(), center);
}

TEST(Triangle, setter)
{
	const double length = 1;
	const double height = 3;
	Vector center(0, 0, 0);
	Vector direction(0, 1, 0);
	Triangle triangle(center, length, height, direction);

	const double new_length = 1;
	const double new_height = 3;

	triangle.setHeight(new_height);
	triangle.setLength(new_length);

	ASSERT_EQ(triangle.getHeight(), height);
	ASSERT_EQ(triangle.getLength(), length);
	ASSERT_EQ(triangle.getPosition(), center);
}

bool findPoint(const std::vector<isim::Vector>& result, Vector key)
{
	for (const isim::Vector& point : result)
	{
		if (key == point)
		{
			return true;
		}
	}
	return false;
}

}
