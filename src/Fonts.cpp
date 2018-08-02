///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include "Fonts.hpp"

Fonts::Fonts(const char* regularFile, const char* boldFile, const char* italicFile, int size)
{
	m_regularFont.create(regularFile, size, TTF_STYLE_NORMAL);
	m_boldFont.create(boldFile, size, TTF_STYLE_BOLD);
	m_italicFont.create(italicFile, size, TTF_STYLE_ITALIC);
}

Fonts::~Fonts()
{
	m_regularFont.destroy();
	m_boldFont.destroy();
	m_italicFont.destroy();
}