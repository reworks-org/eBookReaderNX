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

void Texture::create(Window& window, void* memory, int size)
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

void Texture::destroy()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

void Texture::draw(Window& window, int x, int y)
{
	// Set up destination...
	m_dest.x = x;
	m_dest.y = y;

	// ... and draw the texture.
	SDL_RenderCopy(window.getRenderer(), m_texture, nullptr, &m_dest);
}

void Texture::draw(Window& window, SDL_Rect* src, SDL_Rect* dest)
{
	SDL_RenderCopy(window.getRenderer(), m_texture, src, dest);
}

int Texture::getWidth() const
{
	return m_dest.w;
}

int Texture::getHeight() const
{
	return m_dest.h;
}