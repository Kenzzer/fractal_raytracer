#include "Vector/Vector.hpp"

#include <exception>
#include <gtest/gtest.h>

#include "Parser.hpp"

namespace isim
{

TEST(vector, equals)
{
	Vector p(1, 2, 3);
	ASSERT_EQ(p, p);
}

TEST(vector, not_equals)
{
	Vector v1(1, 2, 3);
	Vector v2(1, 2, 1);
	ASSERT_NE(v1, v2);
}

TEST(vector, loadJSON)
{
	try
	{
		const std::string filename = "resources/Vector.json";
		auto j = TEST_JSON_OPEN(filename);
		Vector v(j);
		ASSERT_EQ(v.x, 1);
		ASSERT_EQ(v.y, 2);
		ASSERT_EQ(v.z, 3);
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}
}; // namespace isim