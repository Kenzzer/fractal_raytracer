#pragma once

#include "Vector/Vector.hpp"
#include "Scene/Factory/Factory.hpp"

#include <nlohmann/json.hpp>
#include <gtest/gtest.h>

namespace isim
{
struct Ray;
class Transform
{
public:
	virtual ~Transform() = default;
	virtual bool isIntersected(Ray& ray) const = 0;
	virtual const Vector& getPosition() const
	{
		return m_position;
	}
	virtual void setPosition(const Vector& pos)
	{
		m_position = pos;
	}
protected:
	Vector m_position;
	Transform(const nlohmann::json& json) : m_position(json["position"])
	{
	}
	Transform(const Vector& position) : m_position(position)
	{
	}
private:
	FRIEND_TEST(Transform, constructor);
	FRIEND_TEST(Transform, constructorJson);
};
}