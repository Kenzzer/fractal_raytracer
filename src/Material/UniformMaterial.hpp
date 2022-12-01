#pragma once

#include "Material.hpp"

namespace isim
{
class UniformMaterial : public Material
{
public:
	UniformMaterial(const Color& c, double kd);
	UniformMaterial(const nlohmann::json& json);
	virtual MaterialInfo getInfo(const Ray& ray) override;
private:
	Color m_color;
	double m_kd;
	double m_ks;
	double m_kr;
	double m_ka;
	double m_km;
	double m_ns;
};
};