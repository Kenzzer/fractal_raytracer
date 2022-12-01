#pragma once

#include "Object/MeshObject.hpp"
#include "Object/Plane.hpp"

#include <cmath>

namespace isim
{
class Menger;

class Cube : public MeshObject
{
public:
	virtual const std::unique_ptr<Material>& getMaterial(const Ray& ray) const override;
	virtual bool isIntersected(Ray& ray) const override;
	virtual Vector getNormal(const Ray& ray) const override;

	void generatePlanes();
	double getSideLength() const;
	void setSideLength(double length);
	bool operator==(const Cube& B) const;
	friend std::ostream& operator<<(std::ostream& os, const Cube& c);
	bool isEmpty() const;
	void setIsEmpty(bool isEmpty);
	bool RayIntersectsTriangle(const Plane& T, Ray& ray) const;
	Vector alignOnNormal(const Vector& point) const;

protected:
	double m_halfSideLength;
	bool m_isEmpty;
	Vector m_points[8];
	Plane m_planes[12];
	std::unique_ptr<Material> m_mat;
	
	friend Menger;
	friend ObjectFactory<Cube>;
	explicit Cube(const nlohmann::json& json);
	Cube(const Vector& position, double length);
private:
	FRIEND_TEST(cube, constructor);
	FRIEND_TEST(cube, constructorJson);
	FRIEND_TEST(cube, factory);
	FRIEND_TEST(cube, not_equals);
	FRIEND_TEST(cube, generate);
	FRIEND_TEST(cube, isEmpty);
	FRIEND_TEST(cube, setter);
	FRIEND_TEST(cube, equals);
	FRIEND_TEST(cubeIntersect, intersectFroBottomLeft);
	FRIEND_TEST(cubeIntersect, intersectFromBottom);
	FRIEND_TEST(cubeIntersect, intersectFromBehind);
	FRIEND_TEST(cubeIntersect, intersectFromFront);
	FRIEND_TEST(cubeIntersect, getPlaneFromPoints);
	FRIEND_TEST(cubeIntersect, intersectFromRight);
	FRIEND_TEST(cubeIntersect, intersectFromLeft);
	FRIEND_TEST(cubeIntersect, intersectFromTop);
	FRIEND_TEST(cubeIntersect, randomIntersect);
	FRIEND_TEST(cubeIntersect, noIntersect);
};
};
