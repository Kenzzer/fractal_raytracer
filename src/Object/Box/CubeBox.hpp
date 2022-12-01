#include "Box.hpp"

namespace isim
{
class CubeBox : public Box
{
public:
	virtual const std::unique_ptr<Material>& getMaterial(const Ray& ray) const override;
	double getSideLength() const;
	void setSideLength(double length);

protected:
	friend class ObjectFactory<CubeBox>;
	friend class Menger;
	friend class Scene;
	CubeBox();
	CubeBox(const nlohmann::json& json);
	CubeBox(const Vector& center, double length);

private:
	std::unique_ptr<Material>* m_mat;//Ugly
	void setMaterial(const std::unique_ptr<Material>* mat);
	FRIEND_TEST(CubeBox, insideCollision);
};
}