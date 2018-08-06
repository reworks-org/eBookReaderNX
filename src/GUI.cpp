///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include <iostream>
#include <filesystem>

#include "App.hpp" // Includes gui.hpp

GUI::GUI(Window* window)
:m_window(window), m_isMenu(true)
{
	// Check that books directory exists, and create it if it does not.
	if(!std::filesystem::exists("sdmc:/books/"))
	{
		std::filesystem::create_directory("sdmc:/books/");
	}

	// Load books from directory recursively.
	for (auto& entry : std::filesystem::recursive_directory_iterator("sdmc:/books/"))
	{
		// Ensure it is a file, we dont want to load directories.
		if (std::filesystem::is_regular_file(entry))
		{
			// Add that entry, by getting the filename from the path of the file.
			m_bookFiles.push_back(entry.path().filename());
		}
	}
}

GUI::~GUI()
{	
	// ensures cleanup.	
	// if not some condition:
	// destroy();
}

void GUI::create()
{
	// Load UI textures.
	Texture* menu = new Texture;
	Texture* info = new Texture;
	Texture* exitButton = new Texture;
	Texture* infoButton = new Texture;
	Texture* fileBox = new Texture;

	menu->create(*m_window, "romfs:/textures/library_menu.png");
	info->create(*m_window, "romfs:/textures/library_info.png");
	exitButton->create(*m_window, "romfs:/textures/button_exit.png");
	infoButton->create(*m_window, "romfs:/textures/button_info.png");
	fileBox->create(*m_window, "romfs:/textures/file_list_box.png");

	App::s_textures.m_textures.emplace("menu", menu);
	App::s_textures.m_textures.emplace("info", info);
	App::s_textures.m_textures.emplace("exitButton", exitButton);
	App::s_textures.m_textures.emplace("infoButton", infoButton);
	App::s_textures.m_textures.emplace("fileBox", fileBox);
}

void GUI::destroy()
{
}

void GUI::event(u32 kDown)
{
	if (m_isMenu)
	{
		eventMenu(kDown);
	}
	else
	{
		eventBook(kDown);
	}
}

void GUI::update()
{
	if (m_isMenu)
	{
		updateMenu();
	}
	else
	{
		updateBook();
	}
}

void GUI::render()
{
	if (m_isMenu)
	{
		renderMenu();
	}
	else
	{
		renderBook();
	}
}

void GUI::eventMenu(u32 kDown)
{

}

void GUI::eventBook(u32 kDown)
{

}

void GUI::updateMenu()
{

}

void GUI::updateBook()
{

}

void GUI::renderMenu()
{
	App::s_textures.m_textures["menu"]->draw(*m_window, 0, 0);
	App::s_textures.m_textures["fileBox"]->draw(*m_window, 426, 314);
	App::s_textures.m_textures["infoButton"]->draw(*m_window, 256, 620);
	App::s_textures.m_textures["exitButton"]->draw(*m_window, 896, 620);
}

void GUI::renderBook()
{

}