#include "MeshObject.hpp"

namespace isim
{
MeshObject::MeshObject(const nlohmann::json& json) : Transform(json)
{
}

MeshObject::MeshObject(const Vector& position) : Transform(position)
{
}

bool MeshObject::operator==(const MeshObject& B) const
{
	return m_position == B.m_position;
}
};