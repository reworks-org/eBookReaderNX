///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_FONT_HPP_
#define EBRNX_FONT_HPP_

#include <SDL2/SDL_ttf.h>

///
/// Manages an sdl2 font object..
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
	/// Defaulted destructor.
	///
	~Font() = default;

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