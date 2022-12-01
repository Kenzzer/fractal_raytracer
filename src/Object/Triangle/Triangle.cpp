#include "Object/Triangle/Triangle.hpp"

namespace isim
{
Triangle::Triangle(const Vector& position, double length, double height, Vector direction) : MeshObject(position),
		m_length(length),
		m_height(height),
		m_direction(direction)
{
}

double Triangle::getLength() const
{
	return m_length;
}

void Triangle::setLength(double length)
{
	Triangle::m_length = length;
}

double Triangle::getHeight() const
{
	return m_height;
}

void Triangle::setHeight(double height)
{
	m_height = height;
}

bool Triangle::operator==(const Triangle& T) const
{
	return this->m_height == T.m_height && this->m_direction == T.m_direction && this->m_length == T.m_length;
}

const std::unique_ptr<Material>& Triangle::getMaterial(const Ray&) const
{
	return m_mat;
}

bool Triangle::isIntersected(Ray&) const
{
	return false;
}

Vector Triangle::getNormal(const Ray&) const
{
	return Vector();
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
	return os << "Center : " << t.getPosition() << std::endl << "length : " << t.getLength() << std::endl << "height : "
			  << t.getHeight() << std::endl << "Vector Direction : " << t.getDirection() << std::endl;
}

const Vector& Triangle::getDirection() const
{
	return m_direction;
}
};
