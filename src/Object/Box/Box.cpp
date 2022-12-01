#include "Object/Box/Box.hpp"

namespace isim
{
bool Box::isIntersected(Ray& ray) const
{
	/*auto rt = this->getPosition() + m_maxs;
	auto lb = this->getPosition() + m_mins;

	auto lbv = (lb - ray.startpos) * ray.invdir;
	auto rtv = (rt - ray.startpos) * ray.invdir;

	float tmin = std::max(std::max(std::min(lbv.x, rtv.x), std::min(lbv.y, rtv.y)), std::min(lbv.z, rtv.z));
	float tmax = std::min(std::min(std::max(lbv.x, rtv.x), std::max(lbv.y, rtv.y)), std::max(lbv.z, rtv.z));
	//std::cout << "tmin: " << tmin << " tmax: " << tmax << std::endl;

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax <= 0)
	{
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return false;
	}

	if (tmin < 0.0)
	{
		tmin = 0;
	}*/

	/*float tmin, tmax, tymin, tymax, tzmin, tzmax;
	auto minBoundsX = (ray.invdir.x < 0) ? m_maxs.x : m_mins.x;
	auto minBoundsY = (ray.invdir.y < 0) ? m_maxs.y : m_mins.y;
	auto maxBoundsX = (ray.invdir.x < 0) ? m_mins.x : m_maxs.x;
	auto maxBoundsY = (ray.invdir.y < 0) ? m_mins.y : m_maxs.y;

	tmin = (minBoundsX - ray.startpos.x) * ray.invdir.x; 
	tmax = (maxBoundsX - ray.startpos.x) * ray.invdir.x; 
	tymin = (minBoundsY - ray.startpos.y) * ray.invdir.y; 
	tymax = (maxBoundsY - ray.startpos.y) * ray.invdir.y;
	Vector bounds[2] = {m_mins, m_maxs};
	uint8_t signs[3] = {ray.invdir.x < 0, ray.invdir.y < 0, ray.invdir.z < 0};

	double tmin = (bounds[signs[0]].x - ray.startpos.x) * ray.invdir.x;
	double tmax = (bounds[1-signs[0]].x - ray.startpos.x) * ray.invdir.x;
	double tymin = (bounds[signs[1]].y - ray.startpos.y) * ray.invdir.y;
	double tymax = (bounds[1-signs[1]].y - ray.startpos.y) * ray.invdir.y;

	if ((tmin > tymax) || (tymin > tmax)) 
		return false;
	if (tymin > tmin) 
		tmin = tymin; 
	if (tymax < tmax) 
		tmax = tymax;

	auto minBoundsZ = (ray.invdir.z < 0) ? m_maxs.z : m_mins.z;
	auto maxBoundsZ = (ray.invdir.z < 0) ? m_mins.z : m_maxs.z;
	tzmin = (minBoundsZ - ray.startpos.z) * ray.invdir.z;
	tzmax = (maxBoundsZ - ray.startpos.z) * ray.invdir.z;

	double tzmin = (bounds[signs[2]].z - ray.startpos.z) * ray.invdir.z;
	double tzmax = (bounds[1-signs[2]].z - ray.startpos.z) * ray.invdir.z;

	std::cout << "tmin: " << tmin << " tmax: " << tmax << std::endl;

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	
	if (tmin < 0.0)
	{
		tmin = 0;
	}*/

	Vector bounds[2] = {m_mins + this->getPosition(), m_maxs + this->getPosition()};
	uint8_t signs[3] = {ray.invdir.x < 0, ray.invdir.y < 0, ray.invdir.z < 0};
	double tmin, tmax, tymin, tymax, tzmin, tzmax;
	tmin = (bounds[signs[0]].x - ray.startpos.x) * ray.invdir.x;
	tmax = (bounds[1-signs[0]].x - ray.startpos.x) * ray.invdir.x;
	tymin = (bounds[signs[1]].y - ray.startpos.y) * ray.invdir.y;
	tymax = (bounds[1-signs[1]].y - ray.startpos.y) * ray.invdir.y;
	if ( (tmin > tymax) || (tymin > tmax) )
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (bounds[signs[2]].z - ray.startpos.z) * ray.invdir.z;
	tzmax = (bounds[1-signs[2]].z - ray.startpos.z) * ray.invdir.z;
	if ( (tmin > tzmax) || (tzmin > tmax) )
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	if (tmax <= 0)
	{
		return false;
	}
	if (tmin <= 0)
	{
		tmin = 0;
	}
	ray.distance = tmin;
	ray.endpos = ray.startpos + ray.dir * (ray.distance - 0.01);
	ray.obj = this;
	return true;
}

Vector Box::alignOnNormal(const Vector& point) const
{
	Vector pos = getPosition();
	Vector cornerBottom = m_mins + getPosition();
	Vector cornerTop = m_maxs + getPosition();
	if (point.x == cornerTop.x
	|| point.x == cornerBottom.x)
	{
		return Vector(point.x, pos.y, pos.z);
	}
	else if (point.y == cornerTop.y
	|| point.y == cornerBottom.y)
	{
		return Vector(pos.x, point.y, pos.z);
	}
	return Vector(pos.x, pos.y, point.z);
}

Vector Box::getNormal(const Ray& ray) const
{
    Vector dir = ray.endpos - getPosition();
    Vector delta = (m_maxs - m_mins) * 0.5;
    double bias = 1.000001;
	Vector ret = Vector{((dir.x / delta.x) * bias),
	((dir.y / delta.y) * bias),
	((dir.z / delta.z) * bias)}.GetNormalize();

	double absX = std::abs(ret.x), absY = std::abs(ret.y), absZ = std::abs(ret.z);
	if (absX > absY && absX > absZ)
	{
		ret.x = (ret.x < 0) ? -1 : 1;
		ret.y = 0;
		ret.z = 0;
	}
	if (absY > absX && absY > absZ)
	{
		ret.x = 0;
		ret.y = (ret.y < 0) ? -1 : 1;
		ret.z = 0;
	}
	if (absZ > absX && absZ > absY)
	{
		ret.x = 0;
		ret.y = 0;
		ret.z = (ret.z < 0) ? -1 : 1;
	}
	return ret.GetNormalize();
}

Box::Box(const Vector& mins, const Vector& maxs, const Vector& position) : MeshObject(position),
		m_mins(mins),
		m_maxs(maxs)
{
}

Box::Box(const Vector& mins, const Vector& maxs, const nlohmann::json& json) : MeshObject(json),
		m_mins(mins),
		m_maxs(maxs)
{
}

Box::Box(const nlohmann::json& json) : MeshObject(json)
{
}
};