#include "PointLight.hpp"

namespace isim
{
static ObjectFactory<PointLight> factory("point_light");

PointLight::PointLight(const Vector& position, double intensity) : Light(intensity, position)
{
}

PointLight::PointLight(const nlohmann::json& json) : Light(json)
{
}
};