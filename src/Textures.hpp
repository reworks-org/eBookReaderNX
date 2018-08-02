///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_TEXTURES_HPP_
#define EBRNX_TEXTURES_HPP_

#include <string>
#include <unordered_map>

#include "Texture.hpp"

// Forward decs:

class Book;
class Window;

///
/// Data structure to manage textures used by app. Calls destroy() for you.
///
class Textures
{
	friend class App;
public:
	///
	/// Destructor.
	///
	~Textures();

	///
	/// Destroys textures used.
	///
	void destroy();

	///
	/// Convenience function that loads images from a book. Book must be parsed!
	///
	/// \param window Window to use in creation of images.
	/// \param book Book to load images from.
	///
	void loadImagesFromBook(Window& window, Book& book);

	///
	/// \brief Convenience function to find a texture from a partial key.
	///
	/// Helps to work around ebook html pages having different paths to images than that of the manifest.
	/// It's a function specific to this application implementation and I wouldn't recommend writing code like this anywhere else heh.
	///
	/// \param partialKey Part of a key i.e. key = "meta/img/1.png" and key is "img/1.png"
	///
	/// \return Returns the found texture, else nullptr.
	///
	Texture* findFromPartial(const std::string& partialKey);

public:
	///
	/// HashMap that stores textures
	/// KVP is id, texture.
	///
	std::unordered_map<std::string, Texture*> m_textures;

private:
	///
	/// Private constructor, so class can only be created by Application class.
	///
	Textures() = default;
};

#endif