///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "App.hpp" // Includes gui.hpp

GUI::GUI(Window* window)
:m_window(window), m_isMenu(true)
{
	// Load ebooks in directory.
	// Have to use DIR over std::filesystem, as the latter is C++17.
	DIR *dir;
	struct dirent *ent;
	mkdir("sdmc:/books", 777);
	dir = opendir("sdmc:/books");

	while ((ent = readdir (dir)) != nullptr	)		
	{
		m_bookFiles.push_back(ent->d_name);
	}
	
	closedir(dir);

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

GUI::~GUI()
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
	App::s_textures.m_textures["fileBox"]->draw(*m_window, 476, 250);
	App::s_textures.m_textures["infoButton"]->draw(*m_window, 116, 620);
	App::s_textures.m_textures["exitButton"]->draw(*m_window, 476, 620);
}

void GUI::renderBook()
{

}