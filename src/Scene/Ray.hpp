#pragma once

#include "Vector/Vector.hpp"
#include "Object/Transform.hpp"

#include <limits>

namespace isim
{
static double inf = std::numeric_limits<double>::infinity();
struct Ray
{
	explicit Ray(const Vector& startpos, const Vector& dir)
	{
		this->startpos = startpos;
		this->dir = dir.GetNormalize();
		this->invdir = Vector{1 / this->dir.x, 1 / this->dir.y, 1 / this->dir.z};
		this->distance = inf;
		this->obj = nullptr;
		this->threadId = -1;
	}
	Vector startpos;
	Vector dir;

	Vector invdir;

	Vector endpos;
	double distance;

	const Transform* obj;

	int threadId;

	bool didHit()
	{
		return this->distance != inf;
	}

	void reset()
	{
		this->distance = inf;
		this->obj = nullptr;
	}
};
};