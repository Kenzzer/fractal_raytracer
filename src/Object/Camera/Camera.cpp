#include "Camera.hpp"
#include "Scene/Scene.hpp"

namespace isim
{
static ObjectFactory<Camera> factory("camera");

Camera::Camera(const Vector& position, const Vector& focus, const Vector& up) : Transform(position),
		m_focus(focus),
		m_up(up),
		m_fov(45.0f),
		m_focal(1.0f)
{
}

Camera::Camera(const nlohmann::json& json) : Transform(json),
		m_focus(json["focus"]),
		m_up(json["up"]),
		m_fov(json["fov"]),
		m_focal(json["focal"])
{
}

bool Camera::isIntersected(Ray&) const
{
	return false;
}

const Vector& Camera::getFocus() const
{
	return m_focus;
}

void Camera::setFocus(const Vector& focus)
{
	m_focus = focus;
}

const Vector& Camera::getUp() const
{
	return m_up;
}

void Camera::setUp(const Vector& up)
{
	m_up = up;
}

float Camera::getFov() const
{
	return m_fov;
}

void Camera::setFov(float fov)
{
	m_fov = fov;
}

float Camera::getFocal() const
{
	return m_focal;
}

void Camera::setFocal(float focal)
{
	m_focal = focal;
}

bool Camera::operator==(const Camera& B) const
{
	return m_position == B.m_position && m_up == B.m_up && m_focus == B.m_focus;
}
};