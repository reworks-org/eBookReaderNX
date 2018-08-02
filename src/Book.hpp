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
	void parse();

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
	/// The books spine. I.e. the pages with text on them.
	///
	std::vector<std::string> m_spine;
};

#endif