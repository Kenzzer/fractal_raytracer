#include "Pyramide.hpp"

isim::Pyramide::Pyramide(double mLength, double mHeight, const isim::Vector& mCenter, double mNbIterations,
						 const isim::Vector& mDirection) : m_length(mLength),
		m_height(mHeight),
		m_center(mCenter),
		m_originHeight(mHeight),
		m_originCenter(mCenter),
		m_nbIterations(mNbIterations),
		m_originLength(mLength),
		m_direction(mDirection)
{
	auto triangle = Triangle(m_center, m_length, m_height, m_direction);
	const Vector up(0, 0, 1);
	const Vector down(0, 0, -1);
	for (std::vector<isim::Vector> positionsList = getPositions(triangle); auto const& p : positionsList)
	{
		m_triangles.emplace(new Triangle(p, m_length / 2, m_height / 2, up));
	}
	isim::Vector topTrianglePos = getTopPosition(triangle);
	m_triangles.emplace(new Triangle(topTrianglePos, m_length / 2, m_height / 2, down));
	m_triangles.emplace(new Triangle(topTrianglePos, m_length / 2, m_height / 2, up));
}

std::vector<isim::Vector> isim::Pyramide::getPositions(const Triangle& triangle) const
{
	std::vector<isim::Vector> result;
	const double centerX = triangle.getPosition().x;
	const double centerY = triangle.getPosition().y;
	const double centerZ = triangle.getPosition().z;

	result.emplace_back(centerX + m_length / 2, centerY + m_length / 2, centerZ);
	result.emplace_back(centerX - m_length / 2, centerY + m_length / 2, centerZ);
	result.emplace_back(centerX + m_length / 2, centerY - m_length / 2, centerZ);
	result.emplace_back(centerX - m_length / 2, centerY - m_length / 2, centerZ);

	return result;
}

isim::Vector isim::Pyramide::getTopPosition(const Triangle& triangle)
{

	const double centerX = triangle.getPosition().x;
	const double centerY = triangle.getPosition().y;
	const double centerZ = triangle.getPosition().z;

	Vector result(centerX, centerY, centerZ + triangle.m_height / 2);

	return result;
}

void isim::Pyramide::transform(const Vector& point)
{
	m_center = point;
	m_length /= 2;
	m_height /= 2;
	auto triangle = Triangle(m_center, m_length, m_height, m_direction);
	std::vector<isim::Vector> positionsList = getPositions(triangle);
	int i = 0;
	isim::Vector topTrianglePos = getTopPosition(triangle);
	for (const std::unique_ptr<Triangle>& t : m_triangles)
	{
		t->setHeight(m_height / 2);
		t->setLength(m_length / 2);
		if (i == 4 || i == 5)
		{
			t->setPosition(topTrianglePos);
		}
		else
		{
			t->setPosition(positionsList[i]);
		}
		i++;
	}
}

void isim::Pyramide::reset()
{
	m_length = m_originLength;
	m_height = m_originHeight;
	m_center = m_originCenter;
	auto triangle = Triangle(m_center, m_length, m_height, m_direction);
	int i = 0;
	isim::Vector topTrianglePos = getTopPosition(triangle);
	std::vector<isim::Vector> positionsList = getPositions(triangle);
	for (const std::unique_ptr<Triangle>& t : m_triangles)
	{
		t->setHeight(m_height / 2);
		t->setLength(m_length / 2);
		if (i == 4 || i == 5)
		{
			t->setPosition(topTrianglePos);
		}
		else
		{
			t->setPosition(positionsList[i]);
		}
		i++;
	}

}
