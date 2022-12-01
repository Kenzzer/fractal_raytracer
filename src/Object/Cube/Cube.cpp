#include "Cube.hpp"
#include "Material/UniformMaterial.hpp"
#include "Vector/Vector.hpp"

#include <iostream>

namespace isim
{
static ObjectFactory<Cube> factory("cube");

Cube::Cube(const nlohmann::json& json) : MeshObject(json),
		m_halfSideLength(0.5 * json["length"].get<double>()),
		m_mat(new UniformMaterial(Color(255, 0, 0), 1.0))
{
	generatePlanes();
}

Cube::Cube(const Vector& position, double length) : MeshObject(position),
		m_halfSideLength(length / 2),
		m_mat(new UniformMaterial(Color(255, 0, 0), 1.0))
{
	m_isEmpty = false;
	generatePlanes();
}

double Cube::getSideLength() const
{
	return m_halfSideLength * 2;
}

void Cube::setSideLength(double length)
{
	m_halfSideLength = length / 2;
	generatePlanes();
}

const std::unique_ptr<Material>& Cube::getMaterial(const Ray& ray) const
{
	auto normal = getNormal(ray);
	if (normal.x > 0.0)
	{
		static std::unique_ptr<Material> red(new UniformMaterial(Color(255, 0, 0), 1.0));
		return red;
	}
	if (normal.x < 0.0)
	{
		static std::unique_ptr<Material> yellow(new UniformMaterial(Color(255, 255, 0), 1.0));
		return yellow;
	}
	if (normal.y > 0.0)
	{
		static std::unique_ptr<Material> blue(new UniformMaterial(Color(0, 0, 255), 1.0));
		return blue;
	}
	if (normal.y < 0.0)
	{
		static std::unique_ptr<Material> blue(new UniformMaterial(Color(255, 0, 255), 1.0));
		return blue;
	}
	if (normal.z > 0.0)
	{
		static std::unique_ptr<Material> green(new UniformMaterial(Color(0, 255, 0), 1.0));
		return green;
	}
	static std::unique_ptr<Material> cyan(new UniformMaterial(Color(0, 255, 255), 1.0));
	return cyan;
}

bool Cube::RayIntersectsTriangle(const Plane& T, Ray& ray) const
{
	auto firstEdge = (T.B - T.A), secondEdge = (T.C - T.A);
	Vector h = ray.dir.Cross(secondEdge);
	double determinant = firstEdge.DotProduct(h);
	const double epsilon = 0.0000001;
	if (abs(determinant) < epsilon)
	{
		return false;
	}
	double inverseDeterminant = 1.0 / determinant;
	Vector distStartA = ray.startpos - T.A;
	double u = inverseDeterminant * distStartA.DotProduct(h);
	if (u < 0.0 || u > 1.0)
	{
		return false;
	}
	Vector q = distStartA.Cross(firstEdge);
	double v = inverseDeterminant * ray.dir.DotProduct(q);
	if (v < 0.0 || u + v > 1.0)
	{
		return false;
	}
	double t = inverseDeterminant * secondEdge.DotProduct(q);
	Vector endpos = ray.startpos + ray.dir * t;
	double distance = (endpos - ray.startpos).GetLength();
	if (distance < ray.distance)
	{
		ray.distance = distance;
		ray.endpos = endpos;
		ray.obj = this;
	}
	return true;
}

void Cube::generatePlanes()
{
	for (int i = 0; i < 8; i++)
	{
		int signX = ((i & 0b1) == 0b0) ? -1 : 1;
		int signY = ((i & 0b10) == 0b10) ? -1 : 1;
		int signZ = ((i & 0b100) == 0b100) ? -1 : 1;
		m_points[i].x = m_position.x + m_halfSideLength * signX;
		m_points[i].y = m_position.y + m_halfSideLength * signY;
		m_points[i].z = m_position.z + m_halfSideLength * signZ;
	}

	m_planes[0] = Plane(m_points[0], m_points[1], m_points[3]);
	m_planes[1] = Plane(m_points[0], m_points[2], m_points[3]);
	m_planes[2] = Plane(m_points[0], m_points[1], m_points[5]);
	m_planes[3] = Plane(m_points[0], m_points[4], m_points[5]);
	m_planes[4] = Plane(m_points[4], m_points[5], m_points[7]);
	m_planes[5] = Plane(m_points[4], m_points[6], m_points[7]);
	m_planes[6] = Plane(m_points[6], m_points[2], m_points[3]);
	m_planes[7] = Plane(m_points[6], m_points[7], m_points[3]);
	m_planes[8] = Plane(m_points[1], m_points[3], m_points[7]);
	m_planes[9] = Plane(m_points[1], m_points[5], m_points[7]);
	m_planes[10] = Plane(m_points[0], m_points[2], m_points[6]);
	m_planes[11] = Plane(m_points[0], m_points[5], m_points[6]);
}

bool Cube::isIntersected(Ray& ray) const
{
	bool didHit = false;
	for (auto& plane : m_planes)
	{
		didHit |= RayIntersectsTriangle(plane, ray);
	}
	return didHit;
}

Vector Cube::alignOnNormal(const Vector& point) const
{
	Vector res;
	if (point.x == m_position.x + m_halfSideLength ||
		point.x == m_position.x - m_halfSideLength)
	{
		res = Vector(point.x, m_position.y, m_position.z);
	}
	else if (point.y == m_position.y + m_halfSideLength ||
			point.y == m_position.y - m_halfSideLength)
	{
		res = Vector(m_position.x, point.y, m_position.z);
	}
	else if (point.z == m_position.z + m_halfSideLength ||
			 point.z == m_position.z - m_halfSideLength)
	{
		res = Vector(m_position.x, m_position.y, point.z);
	}
	return res;
}

Vector Cube::getNormal(const Ray& ray) const
{
	Vector center = getPosition();
	Vector collision = ray.endpos;
	Vector norm = alignOnNormal(collision) - center;
	norm.Normalize();

	return norm;
}

bool Cube::operator==(const Cube& B) const
{
	return m_halfSideLength == B.m_halfSideLength && m_position == B.m_position;
}

bool Cube::isEmpty() const
{
	return m_isEmpty;
}

void Cube::setIsEmpty(bool isEmpty)
{
	m_isEmpty = isEmpty;
}

std::ostream& operator<<(std::ostream& os, const Cube& c)
{
	return os << c.getPosition();
}
};
