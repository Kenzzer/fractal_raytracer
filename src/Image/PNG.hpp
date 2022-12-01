#pragma once

#include <cstdio>
#include <memory>
#include <png.h>
#include <string>

#include "Image.hpp"

namespace isim
{
class PNG : public Image
{
public:
	PNG(const std::string& path, std::uint32_t width, std::uint32_t height);
	virtual ~PNG() noexcept override;

	virtual void OnUpdate() override;

private:
	std::unique_ptr<FILE, decltype(&fclose)> m_fd;
	png_structp m_png;
	png_infop m_pngInfo;
	png_bytep* m_rowpointers;
	std::uint32_t m_numframes;
};
};
