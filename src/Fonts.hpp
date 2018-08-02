///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_FONTS_HPP_
#define EBRNX_FONTS_HPP_

#include "Font.hpp"

///
/// Data structure to manage fonts used by app.
///
struct Fonts
{
	///
	/// Do not want this class to be default constructed.
	///
	Fonts() = delete;

	///
	/// Constructs the fonts.
	///
	/// \param regularFile font location.
	/// \param boldFile font location.
	/// \param italicFile font location.
	/// \param size Size of the fonts.
	///
	Fonts(const char* regularFile, const char* boldFile, const char* italicFile, int size);

	///
	/// Ensure fonts are cleaned up.
	///
	~Fonts();

	///
	/// The font for regular book text.
	///
	Font m_regularFont;

	///
	/// The font for bold book text.
	///
	Font m_boldFont;

	///
	/// The font for italic book text.
	///
	Font m_italicFont;
};

#endif