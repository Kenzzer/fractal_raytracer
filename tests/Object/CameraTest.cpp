#include "Object/Camera/Camera.hpp"
#include "Parser.hpp"

#include <gtest/gtest.h>

namespace isim
{

void assertCameraEquals(const Camera& camera);

TEST(camera, json)
{
	Camera camera(TEST_JSON_OPEN("resources/tests/Object/Camera.json"));

	assertCameraEquals(camera);
}

TEST(camera, value)
{
	Vector position(1, 1, 1);
	Vector focus(1, 1, 1);
	Vector up(1, 1, 1);

	Camera camera(position, focus, up);

	assertCameraEquals(camera);
}

TEST(camera, setFocus)
{
	Vector position(1, 1, 1);
	Vector focus(1, 1, 1);
	Vector up(1, 1, 1);

	Camera camera(position, focus, up);

	Vector newFocus(2, 1, 1);

	camera.setFocus(newFocus);

	ASSERT_EQ(camera.getFocus(), newFocus);
}

TEST(camera, setPosition)
{
	Vector position(1, 1, 1);
	Vector focus(1, 1, 1);
	Vector up(1, 1, 1);

	Camera camera(position, focus, up);

	Vector newPosition(2, 1, 1);

	camera.setPosition(newPosition);

	ASSERT_EQ(camera.getPosition(), newPosition);
}

TEST(camera, setUp)
{
	Vector position(1, 1, 1);
	Vector focus(1, 1, 1);
	Vector up(1, 1, 1);

	Camera camera(position, focus, up);

	Vector newUpVector(2, 1, 1);

	camera.setUp(newUpVector);

	ASSERT_EQ(camera.getUp(), newUpVector);
}

TEST(camera, equals)
{
	Camera c1(Vector(0, 0, 0), Vector(1, 1, 1), Vector(0, 1, 0));
	Camera c2(Vector(0, 0, 0), Vector(1, 1, 1), Vector(0, 1, 0));
	ASSERT_EQ(c1, c1);
	ASSERT_EQ(c1, c2);
}

TEST(camera, not_equals)
{
	Camera c1(Vector(0, 0, 0), Vector(1, 1, 1), Vector(0, 1, 0));
	Camera c2(Vector(0, 1, 0), Vector(1, 1, 1), Vector(0, 1, 0));
	Camera c3(Vector(0, 0, 0), Vector(1, 0, 1), Vector(0, 1, 0));
	Camera c4(Vector(0, 0, 0), Vector(1, 1, 1), Vector(0, 0, 0));
	ASSERT_NE(c1, c2);
	ASSERT_NE(c1, c3);
	ASSERT_NE(c1, c4);
}

TEST(camera, factory)
{
	auto obj = TheFactories["camera"]->New(TEST_JSON_OPEN("resources/tests/Object/Camera.json"));
	ASSERT_NE(dynamic_cast<Camera*>(obj), nullptr);
	assertCameraEquals(*(static_cast<Camera*>(obj)));
	delete obj;
}

void assertCameraEquals(const Camera& camera)
{
	ASSERT_EQ(camera.getFocus().x, 1);
	ASSERT_EQ(camera.getFocus().y, 1);
	ASSERT_EQ(camera.getFocus().z, 1);

	ASSERT_EQ(camera.getPosition().x, 1);
	ASSERT_EQ(camera.getPosition().y, 1);
	ASSERT_EQ(camera.getPosition().z, 1);

	ASSERT_EQ(camera.getUp().x, 1);
	ASSERT_EQ(camera.getUp().y, 1);
	ASSERT_EQ(camera.getUp().z, 1);
}

};