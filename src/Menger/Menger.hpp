#pragma once

#include "Object/Box/CubeBox.hpp"
#include "Material/Material.hpp"
#include "Material/UniformMaterial.hpp"

#include <vector>

namespace isim
{
class Menger : public CubeBox
{
	class Mat : public UniformMaterial
	{
	public:
		Mat(const nlohmann::json& json) : UniformMaterial(json) {};
		virtual MaterialInfo getInfo(const Ray& ray) override;
	};
public:
	virtual bool isIntersected(Ray& ray) const override;
	virtual const std::unique_ptr<Material>& getMaterial(const Ray& ray) const override;

	void transform(const Vector& center, double cubeLength, const std::vector<std::unique_ptr<CubeBox>>& cubes) const;
	const Vector& getBottomLeft() const;
	void setIterations(int iter);

protected:
	void initMenger();

	int m_nbIterations;
	const double m_originLength;
	std::unique_ptr<Material> m_mat;
	mutable std::map<int, std::vector<std::unique_ptr<CubeBox>>> m_cubes;

	friend ObjectFactory<Menger>;
	Menger(double sideLength, const Vector& center, int nbIterations);
	Menger(const nlohmann::json& json);
};
};
