#include "Object/MeshObject.hpp"

namespace isim
{
class Box : public MeshObject
{
public:
	virtual bool isIntersected(Ray& ray) const override;
	virtual Vector getNormal(const Ray& ray) const override;

protected:
	Vector alignOnNormal(const Vector& point) const;

	Vector m_mins;
	Vector m_maxs;

	Box(const Vector& mins, const Vector& maxs, const Vector& position);
	Box(const Vector& mins, const Vector& maxs, const nlohmann::json& json);
	Box(const nlohmann::json& json);
};
}