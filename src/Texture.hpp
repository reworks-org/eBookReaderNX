///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_TEXTURE_HPP_
#define EBRNX_TEXTURE_HPP_

#include <SDL2/SDL_rect.h>

#include "Window.hpp"

///
/// Manages an SDL_Texture.
///
class Texture
{
public:
	///
	/// \brief Default constructor.
	///
	/// m_texture defaults to nullptr and dest is null.
	///
	Texture();

	///
	/// Defaulted destructor.
	///
	~Texture() = default;

	///
	/// \brief Creates the texture from a jpg or png.
	///
	/// \param window Window object to get renderer from.
	/// \param file File to create texture from.
	///
	void create(Window& window, const char* file);

	///
	/// Clean up texture memory.
	///
	void destroy();

	///
	/// Draws the texture to the screen.
	///
	/// \param window Window to get the renderer from.
	/// \param x x position to draw to.
	/// \param y y position to draw to.
	///
	void draw(Window& window, int x, int y);

private:
	///
	/// The actual sdl texture object.
	///
	SDL_Texture* m_texture;

	///
	/// The destination rect.
	///
	SDL_Rect m_dest;
};

#endif