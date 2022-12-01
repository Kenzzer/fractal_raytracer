#pragma once

#include <algorithm>
#include <cstdint>
#include <cmath>
#include <ostream>

namespace isim
{
struct Color
{
	Color() : r(0),
			g(0),
			b(0),
			a(255)
	{
	}

	Color(std::uint8_t r, std::uint8_t g, std::uint8_t b) : r(r),
			g(g),
			b(b),
			a(255)
	{
	}

	Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) : r(r),
			g(g),
			b(b),
			a(a)
	{
	}

	std::uint8_t r;
	std::uint8_t g;
	std::uint8_t b;
	std::uint8_t a;

	friend inline std::ostream& operator<<(std::ostream& os, const Color& dt)
	{
		os << "(R:" << std::to_string(dt.r) << ", G:" << std::to_string(dt.g) << ", B:" << std::to_string(dt.b)
		   << ", A:" << std::to_string(dt.a) << ")";
		return os;
	}

	void inline operator*=(const double& k)
	{
		this->r = std::clamp<std::uint16_t>(std::floor<std::uint16_t>((std::uint16_t)this->r * k), 0, 255);
		this->g = std::clamp<std::uint16_t>(std::floor<std::uint16_t>((std::uint16_t)this->g * k), 0, 255);
		this->b = std::clamp<std::uint16_t>(std::floor<std::uint16_t>((std::uint16_t)this->b * k), 0, 255);
	}

	Color inline operator*(const double& k) const
	{
		std::uint8_t newR = std::clamp<std::uint16_t>(std::floor<std::uint16_t>((std::uint16_t)this->r * k), 0, 255);
		std::uint8_t newG = std::clamp<std::uint16_t>(std::floor<std::uint16_t>((std::uint16_t)this->g * k), 0, 255);
		std::uint8_t newB = std::clamp<std::uint16_t>(std::floor<std::uint16_t>((std::uint16_t)this->b * k), 0, 255);
		return {newR, newG, newB};
	}

	Color inline operator+(const Color &c) const
	{
		std::uint8_t newR = std::clamp<std::uint16_t>(std::floor<std::uint16_t>((std::uint16_t)this->r + c.r / 2), 0, 255);
		std::uint8_t newG = std::clamp<std::uint16_t>(std::floor<std::uint16_t>((std::uint16_t)this->g + c.g / 2), 0, 255);
		std::uint8_t newB = std::clamp<std::uint16_t>(std::floor<std::uint16_t>((std::uint16_t)this->b + c.b / 2), 0, 255);
		return {newR, newG, newB};
	}
};
};
