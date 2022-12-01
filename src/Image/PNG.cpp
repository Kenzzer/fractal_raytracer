#include "PNG.hpp"

#include <iostream>
#include <limits>

namespace isim
{
PNG::PNG(const std::string& path, std::uint32_t width, std::uint32_t height) : Image(width, height),
		m_fd(nullptr, &fclose),
		m_png(nullptr),
		m_pngInfo(nullptr),
		m_rowpointers((png_bytep*) malloc(sizeof(png_bytep) * m_height)),
		m_numframes(0)
{
	for (auto it = m_height; it;)
	{
		it--;
		m_rowpointers[it] = reinterpret_cast<png_bytep>(&m_pixels[m_width * it]);
	}

	FILE* fd = fopen(path.c_str(), "wb");
	if (fd == nullptr)
	{
		throw std::invalid_argument("Couldn't open file: " + path);
	}
	m_fd.reset(fd);

	m_png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (m_png == nullptr)
	{
		throw std::invalid_argument("Couldn't create png write struct.");
	}

	m_pngInfo = png_create_info_struct(m_png);
	if (m_pngInfo == nullptr)
	{
		throw std::invalid_argument("Couldn't create png info struct.");
	}
#ifdef PNG_SETJMP_SUPPORTED
	setjmp(png_jmpbuf(m_png));
#endif

	png_init_io(m_png, m_fd.get());
	png_set_IHDR(m_png, m_pngInfo, m_width, m_height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
				 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_set_acTL(m_png, m_pngInfo, std::numeric_limits<std::int32_t>::max(), 0);
	png_set_first_frame_is_hidden(m_png, m_pngInfo, false);
	png_write_info(m_png, m_pngInfo);

	auto palette = (png_colorp) png_malloc(m_png, PNG_MAX_PALETTE_LENGTH * (sizeof(png_color)));
	png_set_PLTE(m_png, m_pngInfo, palette, PNG_MAX_PALETTE_LENGTH);
	// png_set_swap_alpha(m_png);
}

void PNG::OnUpdate()
{
	png_write_frame_head(m_png, m_pngInfo, m_rowpointers, m_width, m_height, 0, 0, 1, 30, PNG_DISPOSE_OP_NONE,
						 PNG_BLEND_OP_SOURCE);
	png_write_image(m_png, m_rowpointers);
	png_write_frame_tail(m_png, m_pngInfo);

	m_numframes++;
}

PNG::~PNG() noexcept
{
	// Fix acTL
	png_set_acTL(m_png, m_pngInfo, 1, 0);
	png_write_frame_tail(m_png, m_pngInfo);

	auto pos = png_get_acTL_chunk_pos(m_png);
	png_byte buf[8];
	png_save_uint_32(buf, m_numframes);
	png_save_uint_32(buf + 4, 0);

	png_write_end(m_png, m_pngInfo);
	png_destroy_write_struct(&m_png, &m_pngInfo);

	fseek(m_fd.get(), pos + 8, SEEK_SET);
	fwrite(buf, sizeof(char), 8, m_fd.get());

	free(m_rowpointers);
}
};
