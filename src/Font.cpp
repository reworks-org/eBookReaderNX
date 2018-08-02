///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include "Font.hpp"

Font::Font()
:m_font(nullptr)
{
}

void Font::create(const char* file, int size, int style)
{
	m_font = TTF_OpenFont(file, size);
	TTF_SetFontStyle(m_font, style);
}

void Font::destroy()
{
	TTF_CloseFont(m_font);
}

TTF_Font* Font::getFont() const
{
	return m_font;
}