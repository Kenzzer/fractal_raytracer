#pragma once

#include <cstdint>

#include "Color.hpp"

namespace isim
{
class Image
{
public:
	std::uint32_t GetWidth();
	std::uint32_t GetHeight();
	std::uint32_t GetSize();
	Color* GetPixels();

	virtual ~Image()
	{
	};

	virtual void OnUpdate() = 0;

protected:
	std::uint32_t m_width;
	std::uint32_t m_height;
	std::uint32_t m_size;
	Color* m_pixels;

	Image(std::uint32_t width, std::uint32_t height);
};
};
