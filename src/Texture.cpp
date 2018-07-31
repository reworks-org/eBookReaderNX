///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include <SDL2/SDL_image.h>

#include "Texture.hpp"

Texture::Texture()
:m_texture(nullptr), m_dest({0, 0, 0, 0})
{
}

void Texture::create(Window& window, const char* file)
{
	// Create surface of texture.
	SDL_Surface* surface = IMG_Load(file);

	// Then create the texture using the renderer.
	m_texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);

	SDL_FreeSurface(surface);

	// Set up dest rect.
	int w = 0;
	int h = 0;

	// Retrieve info.
	SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);

	m_dest.x = 0;
	m_dest.y = 0;
	m_dest.w = w;
	m_dest.h = h;
}

void Texture::destroy()
{
	SDL_DestroyTexture(m_texture);
}

void Texture::draw(Window& window, int x, int y)
{
	// Set up destination...
	m_dest.x = x;
	m_dest.y = y;

	// ... and draw the texture.
	SDL_RenderCopy(window.getRenderer(), m_texture, nullptr, &m_dest);
}