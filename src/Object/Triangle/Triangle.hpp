#pragma once

#include "Object/MeshObject.hpp"
#include "Vector/Vector.hpp"

namespace isim
{
class Pyramide;
class Triangle : public MeshObject
{
public:
	virtual const std::unique_ptr<Material>& getMaterial(const Ray& ray) const override;
	virtual bool isIntersected(Ray& ray) const override;
	virtual Vector getNormal(const Ray& ray) const override;

	friend Pyramide;
	double getLength() const;
	void setLength(double length);
	double getHeight() const;
	void setHeight(double height);
	bool operator==(const Triangle& T) const;
	friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
	const Vector& getDirection() const;

protected:
	Triangle(const Vector& position, double length, double height, Vector direction);
	double m_length;
	double m_height;
	Vector m_direction;
	std::unique_ptr<Material> m_mat;

private:
	FRIEND_TEST(Triangle, contructor);
	FRIEND_TEST(Triangle, getter);
	FRIEND_TEST(Triangle, setter);
	FRIEND_TEST(Triangle, getPositions);
	FRIEND_TEST(Triangle, getTopPosition);
	FRIEND_TEST(Triangle, print);
	FRIEND_TEST(Triangle, generate);
	FRIEND_TEST(Pyramide, constructor);
	FRIEND_TEST(Pyramide, transform);
	FRIEND_TEST(Pyramide, reset);
};
};