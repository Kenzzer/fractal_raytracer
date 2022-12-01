#include "Light.hpp"

namespace isim
{
Light::Light(double intensity, const Vector& position) : Transform(position),
		m_intensity(intensity)
{
}

Light::Light(const nlohmann::json& json) : Transform(json),
		m_intensity(json["intensity"])
{
}

double Light::getIntensity() const
{
	return m_intensity;
}

void Light::setIntensity(double intensity)
{
	Light::m_intensity = intensity;
}

bool Light::isIntersected(Ray&) const
{
	return false;
}

};