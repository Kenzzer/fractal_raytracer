#include "Image.hpp"

namespace isim
{
std::uint32_t Image::GetWidth()
{
	return this->m_width;
}

std::uint32_t Image::GetHeight()
{
	return this->m_height;
}

std::uint32_t Image::GetSize()
{
	return this->m_size;
}

Color* Image::GetPixels()
{
	return this->m_pixels;
}

Image::Image(std::uint32_t width, std::uint32_t height) : m_width(width),
		m_height(height),
		m_size(width * height),
		m_pixels(static_cast<Color*>(calloc(width * height, sizeof(Color))))
{
}
};