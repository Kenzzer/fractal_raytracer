#include <gtest/gtest.h>
#include "Vector/Vector.hpp"
#include "Object/Triangle/Triangle.hpp"
#include "Pyramide/Pyramide.hpp"

namespace isim
{
struct PyramideDim
{
	double length;
	double height;
	size_t numberOfTriangles;
};

struct NumberOfTypeTriangles
{
	double numberOfTrianglesWithUpPos = 0;
	double numberOfTrianglesWithDownPos = 0;
	double numberOfUpTriangle = 0;
	double numberOfDownTriangle = 0;
};

void assertPyramideDimensions(double expectedLength, double expectedHeight, const PyramideDim &p);
void assertTrianglesOrientations(const NumberOfTypeTriangles& t);

TEST(Pyramide, constructor)
{
	const double length = 4;
	const double height = 3;
	const double nbIterations = 1;
	Vector center(0, 0, 0);
	Vector direction(0, 1, 0);
	Pyramide pyramide(length, height, center, nbIterations, direction);
	Triangle triangle(center, length, height, direction);

	ASSERT_EQ(length, pyramide.m_length);
	ASSERT_EQ(height, pyramide.m_height);
	const double expectedListOfTriangleSize = 6;
	ASSERT_EQ(expectedListOfTriangleSize, pyramide.m_triangles.size());

	NumberOfTypeTriangles numberOfTypeTriangles;

	isim::Vector upPos = isim::Pyramide::getTopPosition(triangle);
	for (const std::unique_ptr<Triangle>& t : pyramide.m_triangles)
	{
		if (t->getDirection().z < 0)
		{
			numberOfTypeTriangles.numberOfDownTriangle += 1;
		}
		else if (t->getDirection().z > 0)
		{
			numberOfTypeTriangles.numberOfUpTriangle += 1;
		}

		if (t->getPosition() == upPos)
		{
			numberOfTypeTriangles.numberOfTrianglesWithUpPos++;
		}
		else
		{
			numberOfTypeTriangles.numberOfTrianglesWithDownPos++;
		}

		ASSERT_NE(0, t->getDirection().z);
		ASSERT_EQ(t->getLength(), length / 2);
		ASSERT_EQ(t->getHeight(), height / 2);
	}
	assertTrianglesOrientations(numberOfTypeTriangles);
}

TEST(Pyramide, transform)
{
	const double length = 4;
	const double height = 3;
	const double nbIterations = 1;
	Vector center(0, 0, 0);
	Vector direction(0, 1, 0);
	Pyramide pyramide(length, height, center, nbIterations, direction);
	pyramide.transform(center);
	Triangle triangle(pyramide.m_center, pyramide.m_length, pyramide.m_height, pyramide.m_direction);

	struct PyramideDim p{};
	p.height = pyramide.m_height;
	p.length = pyramide.m_length;
	p.numberOfTriangles = pyramide.m_triangles.size();
	assertPyramideDimensions(length / 2, height / 2, p);

	NumberOfTypeTriangles numberOfTypeTriangles;
	isim::Vector upPos = isim::Pyramide::getTopPosition(triangle);
	for (const std::unique_ptr<Triangle>& t : pyramide.m_triangles)
	{
		if (t->getDirection().z < 0)
		{
			numberOfTypeTriangles.numberOfDownTriangle += 1;
		}
		else if (t->getDirection().z > 0)
		{
			numberOfTypeTriangles.numberOfUpTriangle += 1;
		}

		if (t->getPosition() == upPos)
		{
			numberOfTypeTriangles.numberOfTrianglesWithUpPos++;
		}
		else
		{
			numberOfTypeTriangles.numberOfTrianglesWithDownPos++;
		}

		ASSERT_NE(0, t->getDirection().z);
		ASSERT_EQ(t->getLength(), length / 4);
		ASSERT_EQ(t->getHeight(), height / 4);
	}
	assertTrianglesOrientations(numberOfTypeTriangles);

}

TEST(Pyramide, reset)
{

	const double length = 4;
	const double height = 3;
	const double nbIterations = 1;
	Vector center(0, 0, 0);
	Vector direction(0, 1, 0);
	Pyramide expectedPyramide(length, height, center, nbIterations, direction);
	expectedPyramide.transform(center);
	expectedPyramide.reset();

	Pyramide result(expectedPyramide.m_length, expectedPyramide.m_height, expectedPyramide.m_center,
					expectedPyramide.m_nbIterations, expectedPyramide.m_direction);

	ASSERT_EQ(result.m_length, expectedPyramide.m_length);
	ASSERT_EQ(result.m_height, expectedPyramide.m_height);

	for (auto& p : expectedPyramide.m_triangles)
	{
		bool present = false;
		for (auto& p1 : result.m_triangles)
		{
			if (*p1 == *p)
			{
				present = true;
				break;
			}
		}
		ASSERT_TRUE(present);
	}
}

void assertPyramideDimensions(double expectedLength, double expectedHeight, const PyramideDim& p)
{
	ASSERT_EQ(expectedLength, p.length);
	ASSERT_EQ(expectedHeight, p.height);

	const double expectedListOfTriangleSize = 6;
	ASSERT_EQ(expectedListOfTriangleSize, p.numberOfTriangles);

}

void assertTrianglesOrientations(const NumberOfTypeTriangles& t)
{
	const int expectedNumberOfTrianglesWithUpPos = 2;
	ASSERT_EQ(t.numberOfTrianglesWithUpPos, expectedNumberOfTrianglesWithUpPos);
	const int expectedNumberOfTrianglesWithDownPos = 4;
	ASSERT_EQ(t.numberOfTrianglesWithDownPos, expectedNumberOfTrianglesWithDownPos);

	const int expectedNumberOfUpTriangle = 5;
	ASSERT_EQ(expectedNumberOfUpTriangle, t.numberOfUpTriangle);
	const int expectedNumberOfDownTriangle = 1;
	ASSERT_EQ(expectedNumberOfDownTriangle, t.numberOfDownTriangle);
}
}
