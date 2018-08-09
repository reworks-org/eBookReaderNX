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

Texture::~Texture()
{
	// Ensure texture is actually destroyed.
	destroy();
}

void Texture::create(Window& window, const char* file)
{
	// Create surface of texture.
	SDL_Surface* surface = IMG_Load(file);

	// Then create the texture using the renderer.
	m_texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);

	// Cleanup.
	SDL_FreeSurface(surface);

	// Set up dest rect.
	int w = 0, h = 0;

	// Retrieve info.
	SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);

	m_dest.x = 0;
	m_dest.y = 0;
	m_dest.w = w;
	m_dest.h = h;
}

void Texture::create(Window& window, int size, void* memory)
{
	// Retrieve RWops handle.
	SDL_RWops* rwops = SDL_RWFromMem(memory, size);

	// Then create surface.
	SDL_Surface* surface = IMG_Load_RW(rwops, 0);

	// Then create the texture using the renderer.
	m_texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);

	// Cleanup.
	SDL_RWclose(rwops);
	SDL_FreeSurface(surface);

	// Set up dest rect.
	int w = 0, h = 0;

	// Retrieve info.
	SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);

	m_dest.x = 0;
	m_dest.y = 0;
	m_dest.w = w;
	m_dest.h = h;
}

void Texture::create(Window& window, Font& font, const char* text, SDL_Colour col)
{
	// Create surface, then texture from text.		
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font.getFont(), text, col);
	m_texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);

	// Destination to draw to.
	m_dest.x = 0;
	m_dest.y = 0;
	m_dest.w = surface->w;
	m_dest.h = surface->h;

	// cleanup
	SDL_FreeSurface(surface);
}

void Texture::destroy()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

void Texture::draw(Window& window, int x, int y, double rotation)
{
	// Set up destination...
	m_dest.x = x;
	m_dest.y = y;

	// ... and draw the texture.
	SDL_RenderCopyEx(window.getRenderer(), m_texture, nullptr, &m_dest, rotation, nullptr, SDL_FLIP_NONE);
}

void Texture::draw(Window& window, SDL_Rect* src, SDL_Rect* dest, double rotation)
{
	SDL_RenderCopyEx(window.getRenderer(), m_texture, src, dest, rotation, nullptr, SDL_FLIP_NONE);
}

int Texture::getWidth() const
{
	return m_dest.w;
}

int Texture::getHeight() const
{
	return m_dest.h;
}