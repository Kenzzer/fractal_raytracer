#pragma once

#include "Image/Color.hpp"
#include "Scene/Ray.hpp"

namespace isim
{
struct MaterialInfo
{
	Color color;
	double kd;
	double ks;
	double kr;
	double ka;
	double km;
	double ns;
};

class Material
{
public:
	virtual ~Material() = default;
	virtual MaterialInfo getInfo(const Ray& ray) = 0;
};
};