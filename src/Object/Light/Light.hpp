#pragma once

#include "Object/Transform.hpp"

namespace isim
{
class Light : public Transform
{
	friend class Scene;
protected:
	virtual bool isIntersected(Ray& ray) const override;
	
	double getIntensity() const;
	void setIntensity(double intensity);

protected:
	double m_intensity;

	explicit Light(const nlohmann::json& j);
	Light(double intensity, const Vector& position);
private:
	FRIEND_TEST(PointLight, setIntensity);
};
};
