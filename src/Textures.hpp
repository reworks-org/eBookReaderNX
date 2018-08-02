///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_TEXTURES_HPP_
#define EBRNX_TEXTURES_HPP_

#include "Texture.hpp"

///
/// Data structure to manage textures used by app.
///
struct Textures
{
	///
	/// Do not want this class to be default constructed.
	///
	Textures() = delete;

	///
	/// Constructs the textures.
	///
	Textures(const char* makesuniquefromdefault_isaplaceholder);

	///
	/// Ensure Textures are cleaned up.
	///
	~Textures();
};

#endif