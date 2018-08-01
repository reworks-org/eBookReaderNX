///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_MANIFEST_HPP_
#define EBRNX_MANIFEST_HPP_

#include <string>
#include <unordered_map>

///
/// Represents an item element in a manifest.
///
struct Item
{
	///
	/// The type of document the href is pointing to.
	///
	std::string m_type;

	///
	/// The location of the item in the ebook structure.
	///
	std::string m_href;
};

///
/// Represents a manifest type to store item elements in.
/// The std::string is the "id" attribute from the item element tag.
///
typedef std::unordered_map<std::string, Item> Manifest;

#endif