///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_LOCATOR_HPP_
#define EBRNX_LOCATOR_HPP_

#include <memory>

class Book;
class Textures;
class SwitchContainer;

struct Locator
{
	///
	/// App textures.
	///
	static Textures s_textures;

	///
	/// The book being read.
	///
	static std::unique_ptr<Book> s_book;

	///
	/// Litehtml container for this app.
	///
	static SwitchContainer s_container;
};

#endif