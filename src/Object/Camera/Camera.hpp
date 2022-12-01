#pragma once

#include "Object/Transform.hpp"

namespace isim
{
class Scene;
class Camera : public Transform
{
public:
	virtual bool isIntersected(Ray& ray) const override;

	const Vector& getFocus() const;
	void setFocus(const Vector& focus);
	const Vector& getUp() const;
	void setUp(const Vector& up);
	float getFov() const;
	void setFov(float fov);
	float getFocal() const;
	void setFocal(float focal);

	bool operator==(const Camera& B) const;
protected:
	Vector m_focus;
	Vector m_up;
	float m_fov;
	float m_focal;

	friend ObjectFactory<Camera>;
	explicit Camera(const nlohmann::json& json);
	Camera(const Vector& position, const Vector& focus, const Vector& up);
private:
	FRIEND_TEST(camera, json);
	FRIEND_TEST(camera, value);
	FRIEND_TEST(camera, setFocus);
	FRIEND_TEST(camera, setPosition);
	FRIEND_TEST(camera, setUp);
	FRIEND_TEST(camera, equals);
	FRIEND_TEST(camera, not_equals);
	FRIEND_TEST(camera, factory);
};
};
