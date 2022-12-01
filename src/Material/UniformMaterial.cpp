#include "UniformMaterial.hpp"

namespace isim
{
UniformMaterial::UniformMaterial(const Color& c, double kd) : m_color(c),
		m_kd(kd),
		m_ks(0.0),
		m_kr(0.0),
		m_ka(0.2),
		m_km(1.0),
		m_ns(0.0)
{
}

UniformMaterial::UniformMaterial(const nlohmann::json& json) : m_color(Color(json["r"], json["g"], json["b"])),
		m_kd(json["kd"]),
		m_ks(json["ks"]),
		m_kr(json["kr"]),
		m_ka(json["ka"]),
		m_km(json["km"]),
		m_ns(json["ns"])
{
}

MaterialInfo UniformMaterial::getInfo(const Ray&)
{
	return MaterialInfo{m_color, m_kd, m_ks, m_kr, m_ka, m_km, m_ns};
}
};