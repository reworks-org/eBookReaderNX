///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include "Book.hpp"
#include "Window.hpp"

#include "Textures.hpp"

Textures::~Textures()
{
	destroy();
}

void Textures::destroy()
{
	for (auto& pair : m_textures)
	{
		if (pair.second != nullptr)
		{
			pair.second->destroy();
			
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

void Textures::loadImagesFromBook(Window& window, Book& book)
{
	// Iterate over manifest
	for (auto& pair : book.getManifest())
	{
		// Looking for media-types that contain "image/"
		if (pair.second.m_type.find("image/") != std::string::npos)
		{
			std::string str = book.getZip().ExtractToString(pair.second.m_href);
			
			// Uhh, yeah i know, super hacky, but w/e.
			const auto size = str.size() + 1;
			char* buffer = new char[size];
			strcpy(buffer, str.c_str());

			// This is deleted in the destroy() method, or destructor.
			Texture* texture = new Texture;
			texture->create(window, size, static_cast<void*>(buffer));

			m_textures.emplace(pair.second.m_href, texture);

			// delete buffer.
			delete[] buffer;
		}
	}
}

Texture* Textures::findFromPartial(const std::string& partialKey)
{
	// Set up return pointer.
	Texture* texture = nullptr;

	// Iterate through the textures
	for (auto& pair : m_textures)
	{
		// Trying to match the partial key to a full key.
		if (pair.first.find(partialKey) != std::string::npos)
		{
			texture = pair.second;
		}
	}

	return texture;
}