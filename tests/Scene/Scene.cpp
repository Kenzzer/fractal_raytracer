#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "Parser.hpp"
#include "Scene/Scene.hpp"

namespace isim
{
TEST(Scene, addCameras)
{
	Scene scene;
	scene.addCameras(TEST_JSON_OPEN("resources/tests/Scene/Cameras.json"));

	ASSERT_NE(scene.getCameras().size(), 0);
}

TEST(Scene, addLights)
{
	Scene scene;
	scene.addLights(TEST_JSON_OPEN("resources/tests/Scene/Lights.json"));

	ASSERT_NE(scene.getLights().size(), 0);
}

TEST(Scene, addObjects)
{
	Scene scene;
	scene.addObjects(TEST_JSON_OPEN("resources/tests/Scene/Objects.json"));

	ASSERT_NE(scene.getObjects().size(), 0);
}

TEST(Scene, constructorJson)
{
	auto j = TEST_JSON_OPEN("resources/tests/Scene/Scene.json");
	Scene scene(j);
	ASSERT_NE(scene.getLights().size(), 0);
	ASSERT_NE(scene.getCameras().size(), 0);
	ASSERT_NE(scene.getObjects().size(), 0);
}
};
