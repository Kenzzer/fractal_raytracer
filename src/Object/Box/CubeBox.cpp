#include "CubeBox.hpp"
#include "Material/UniformMaterial.hpp"

namespace isim
{
ObjectFactory<CubeBox> factory("cube_box");

const std::unique_ptr<Material>& CubeBox::getMaterial(const Ray&) const
{
	if (m_mat)
	{
		return *m_mat;
	}
	static std::unique_ptr<Material> color(new UniformMaterial(Color(200, 200, 200), 0.1));
	return color;
}

CubeBox::CubeBox() : Box(Vector(-0.1, -0.1, -0.1), Vector(0.1, 0.1, 0.1), Vector()),
	m_mat(nullptr)
{
}

CubeBox::CubeBox(const nlohmann::json& json) : Box(json),
	m_mat(nullptr)
{
	setSideLength(json["length"]);
}

CubeBox::CubeBox(const Vector& center, double length) : Box(Vector(-length/2, -length/2, -length/2), Vector(length/2, length/2, length/2), center),
	m_mat(nullptr)
{
}

double CubeBox::getSideLength() const
{
	return m_maxs.x * 2;
}

void CubeBox::setSideLength(double length)
{
	auto half = length / 2;
	m_mins = Vector(-half, -half, -half);
	m_maxs = Vector(half, half, half);
}

void CubeBox::setMaterial(const std::unique_ptr<Material>* mat)
{
	m_mat = (std::unique_ptr<Material>*)mat;
}
}