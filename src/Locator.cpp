///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include "Book.hpp"
#include "Textures.hpp"
#include "SwitchContainer.hpp"

#include "Locator.hpp"

Textures Locator::s_textures;
std::unique_ptr<Book> Locator::s_book;
SwitchContainer Locator::s_container;