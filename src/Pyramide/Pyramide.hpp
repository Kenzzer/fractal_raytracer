#pragma once

#include "Object/Triangle/Triangle.hpp"

namespace isim
{
class Pyramide
{
public:
	Pyramide(double mLength, double mHeight, const Vector& mCenter, double mNbIterations, const Vector& mDirection);
	void transform(const Vector& point);
	void reset();

protected:
	std::set<std::unique_ptr<Triangle>> m_triangles;

private:
	double m_length;
	double m_height;
	Vector m_center;

	double m_originHeight;
	Vector m_originCenter;
	double m_nbIterations;

	double m_originLength;
	Vector m_direction;
	std::vector<isim::Vector> getPositions(const Triangle& triangle) const;
	static isim::Vector getTopPosition(const Triangle& triangle);

	FRIEND_TEST(Pyramide, constructor);
	FRIEND_TEST(Pyramide, transform);
	FRIEND_TEST(Pyramide, reset);
};
}
