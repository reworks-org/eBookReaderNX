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

Font::~Font()
{
	// Ensure font is actually destroyed.
	destroy();
}

void Font::create(const char* file, int size, int style)
{
	// Create font and then set its style.
	m_font = TTF_OpenFont(file, size);
	TTF_SetFontStyle(m_font, style);
}

void Font::destroy()
{
	// Clean up font.
	if (m_font != nullptr)
	{
		TTF_CloseFont(m_font);
		m_font = nullptr;
	}
}

void Font::renderText(Window* window, const char* text, SDL_Colour col, int x, int y)
{
	// Create surface, then texture from text.		
	SDL_Surface* surface = TTF_RenderUTF8_Blended(m_font, text, col);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(window->getRenderer(), surface);

	// Destination to draw to.
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;

	// render
	SDL_RenderCopy(window->getRenderer(), texture, nullptr, &dest);

	// cleanup
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

TTF_Font* Font::getFont() const
{
	return m_font;
}