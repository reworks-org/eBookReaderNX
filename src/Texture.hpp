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
	/// Destructor.
	///
	~Texture();

	///
	/// Creates the texture from a jpg or png.
	///
	/// \param window Window object to get renderer from.
	/// \param file File to create texture from.
	///
	void create(Window& window, const char* file);

	///
	/// Create texture from memory.
	///
	/// \param window Window object to get renderer from.
	/// \param memory Memory to load texture from.
	/// \param size Size of memory that the texture is being loaded from.
	///
	void create(Window& window, void* memory, int size);

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

	///
	/// Draws the texture to the screen.
	///
	/// \param window Window to get the renderer from.
	/// \param src source rectangle.
	/// \param dest dest rectangle.
	///
	void draw(Window& window, SDL_Rect* src, SDL_Rect* dest);

	///
	/// Get width.
	///
	/// \return Width.
	///
	int getWidth() const;

	///
	/// Get height.
	///
	/// \return Height.
	///
	int getHeight() const;

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