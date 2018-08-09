///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_BOOK_HPP_
#define EBRNX_BOOK_HPP_

#include <vector>

#include "Manifest.hpp"
#include "libs/blzip/BLUnZip.h"
#include "SwitchContainer.hpp"

class Window;

///
/// This class represents a book object.
///
class Book
{
public:
	///
	/// Constructor.
	///
	/// \param book Book to store to call parse() on.
	///
	Book(const std::string& book);

	///
	/// Destructor.
	///
	~Book();

	///
	/// Parse the books content.
	///
	/// \param window Used when loading images.
	///
	void parse(Window& window);

	///
	/// Get the internal zip file.
	///
	BLUnZip& getZip();

	///
	/// Retrieve manifest.
	///
	const Manifest& getManifest() const;

	///
	/// Retrieve spine.
	///
	const std::vector<std::string>& getSpine() const;

public:
	///
	/// Represents a page.
	///
	litehtml::document::ptr m_document;

private:
	///
	/// Object holding epub zip in memory.
	///
	BLUnZip m_zip;

	///
	/// Book file to parse.
	///
	std::string m_book;

	///
	/// Contains meta information about book.
	///
	std::string m_opf;

	///
	/// Version of the format of the book.
	///
	float m_version;

	///
	/// The title of the book.
	///
	std::string m_title;

	///
	/// The author of the book.
	///
	std::string m_author;
	
	///
	/// The manifest object of the book.
	///
	Manifest m_manifest;

	///
	/// Litehtml primary css.
	///
	litehtml::context m_context;

	///
	/// The books spine. I.e. the pages with text on them.
	///
	std::vector<std::string> m_spine;

	///
	/// Litehtml container for this app.
	///
	SwitchContainer m_container;
};

#endif