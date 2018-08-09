///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_TEXTURE_HPP_
#define EBRNX_TEXTURE_HPP_

#include <SDL2/SDL_rect.h>

#include "Font.hpp"

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
	/// \param size Size of memory that the texture is being loaded from.
	/// \param memory Memory to load texture from.
	///
	void create(Window& window, int size, void* memory);

	///
	/// Create the texture from a font.
	///
	/// \param window Window object to get renderer from.
	/// \param font Font object that determintes font, style and size of text.
	/// \param text Text to create texture from.
	/// \param col Colour of text.
	///
	void create(Window& window, Font& font, const char* text, SDL_Colour col);

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
	/// \param rotation Degrees to rotate the texture by.
	///
	void draw(Window& window, int x, int y, double rotation = 0.0);

	///
	/// Draws the texture to the screen.
	///
	/// \param window Window to get the renderer from.
	/// \param src source rectangle.
	/// \param dest dest rectangle.
	/// \param rotation Degrees to rotate the texture by.
	///
	void draw(Window& window, SDL_Rect* src, SDL_Rect* dest, double rotation = 0.0);

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