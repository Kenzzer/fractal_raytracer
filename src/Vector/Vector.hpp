#pragma once

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

namespace isim
{
struct Vector
{
public:
	Vector() : x(0),
	y(0),
	z(0)
	{
	}

	Vector(const nlohmann::json& json) : x(json["x"]),
		y(json["y"]),
		z(json["z"])
	{
	}

	Vector(double x, double y, double z) : x(x),
		y(y),
		z(z)
	{
	}

	bool operator==(const Vector& B) const
	{
		return this->x == B.x && this->y == B.y && this->z == B.z;
	}

	Vector operator*(const float& s) const
	{
		return Vector{this->x * s, this->y * s, this->z * s};
	}

	void operator*=(const float& s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
	}

	Vector operator*(const double& s) const
	{
		return Vector{this->x * s, this->y * s, this->z * s};
	}

	void operator*=(const double& s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
	}

	Vector operator+(const Vector& v) const
	{
		return Vector{x + v.x, y + v.y, z + v.z};
	}

	void operator+=(const Vector& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}

	Vector operator-(const Vector& v) const
	{
		return Vector{this->x - v.x, this->y - v.y, this->z - v.z};
	}

	void operator-=(const Vector& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
	}

	double GetLength() const
	{
		return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	double DotProduct(const Vector& v) const
	{
		return (this->x * v.x + this->y * v.y + this->z * v.z);
	}

	float Normalize()
	{
		float length = this->GetLength();
		this->x /= length;
		this->y /= length;
		this->z /= length;
		return length;
	}

	Vector GetNormalize() const
	{
		float length = this->GetLength();
		return Vector{this->x / length, this->y / length, this->z / length};
	}

	Vector Cross(const Vector& v) const
	{
		return Vector{this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x};
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector& dt)
	{
		os << '(' << dt.x << ',' << dt.y << ',' << dt.z << ')';
		return os;
	}

	friend Vector operator*(const Vector& r, const Vector& l)
	{
		return Vector(r.x * l.x, r.y * l.y, r.z * l.z);
	}

	double x, y, z;
};
};
