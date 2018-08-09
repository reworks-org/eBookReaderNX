///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_FONT_HPP_
#define EBRNX_FONT_HPP_

#include <SDL2/SDL_ttf.h>

#include "Window.hpp"

///
/// Manages an sdl2 font object.
///
class Font
{
public:
	///
	/// \brief Default constructor.
	///
	/// Defaults m_font to nullptr.
	///
	Font();

	///
	/// Destructor.
	///
	~Font();

	///
	/// \brief Creates the texture from a jpg or png.
	///
	/// \param file File to create font from.
	/// \param size Size of the font to be created at.
	/// \param style The style of the font, using TTF_STYLE_<TYPE> macro from SDL_TTF.
	///
	void create(const char* file, int size, int style);

	///
	/// Clean up font memory.
	///
	void destroy();

	///
	/// Renders text to the screen in a convenient function.
	///
	/// \param window Window to render to.
	/// \param text Text to render.
	/// \param col Colour to draw text in.
	/// \param x x pos to draw to.
	/// \param y y pos to draw to.
	/// \param rotation Rotation of the text.
	///
	void renderText(Window* window, const char* text, SDL_Colour col, int x, int y, double rotation = 0.0);

	///
	/// Retrieve internal font.
	///
	/// \return Const Pointer to internal TTF_Font.
	///
	TTF_Font* getFont() const;

private:
	///
	/// The actual sdl font object.
	///
	TTF_Font* m_font;
};

#endif