#pragma once

#include "Object/Light/Light.hpp"
#include "Vector/Vector.hpp"

#include <gtest/gtest.h>

namespace isim
{
class Scene;

class PointLight : public Light
{
private:
	FRIEND_TEST(PointLight, constructor);
	FRIEND_TEST(PointLight, constructorJson);
	FRIEND_TEST(PointLight, setIntensity);
	FRIEND_TEST(PointLight, setPosition);

protected:
	friend ObjectFactory<PointLight>;
	explicit PointLight(const nlohmann::json& json);
	PointLight(const Vector& position, double intensity);
};
};