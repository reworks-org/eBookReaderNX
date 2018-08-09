///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include <iostream>
#include <filesystem>
#include <switch/services/hid.h>

#include "App.hpp" // Includes gui.hpp

GUI::GUI(Window* window)
:m_index(0), m_curFilePage(1), m_isMenu(true), m_showInfo(false), m_window(window), m_book(nullptr), m_selected("")
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
	// ensures memory is freed.
	destroy();
}

void GUI::create()
{
	// Load UI textures.
	Texture* menu = new Texture;
	Texture* info = new Texture;
	Texture* exitButton = new Texture;
	Texture* infoButton = new Texture;
	Texture* fileBox = new Texture;
	Texture* loading = new Texture;

	menu->create(*m_window, "romfs:/textures/library_menu.png");
	info->create(*m_window, "romfs:/textures/library_info.png");
	exitButton->create(*m_window, "romfs:/textures/button_exit.png");
	infoButton->create(*m_window, "romfs:/textures/button_info.png");
	fileBox->create(*m_window, "romfs:/textures/file_list_box.png");
	loading->create(*m_window, "romfs:/textures/loading.png");

	App::s_textures.m_textures.emplace("menu", menu);
	App::s_textures.m_textures.emplace("info", info);
	App::s_textures.m_textures.emplace("exitButton", exitButton);
	App::s_textures.m_textures.emplace("infoButton", infoButton);
	App::s_textures.m_textures.emplace("fileBox", fileBox);
	App::s_textures.m_textures.emplace("loading", loading);

	// Create UI font.
	m_uiFont.create("romfs:/fonts/SourceSansPro-Light.ttf", 18, TTF_STYLE_NORMAL);
}

void GUI::destroy()
{
	if (m_book != nullptr)
	{
		delete m_book;
		m_book = nullptr;
	}

	m_uiFont.destroy();
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
	if (kDown & KEY_L)
	{
		if (!m_showInfo)
		{
			m_showInfo = true;
		}
		else
		{
			m_showInfo = false;
		}
	}

	if (kDown & KEY_R)
	{
		m_window->m_open = false;
	}

	if (kDown & KEY_X) 
	{ 
		std::string bookToRemove = "sdmc:/books/" + m_bookFiles[m_index + ((10 * m_curFilePage) - 10)];
		std::filesystem::remove(bookToRemove);

		auto found = std::find(m_bookFiles.begin(), m_bookFiles.end(), bookToRemove);
		if (found != m_bookFiles.end())
		{
			m_bookFiles.erase(found);
		}
	}

	if (kDown & KEY_A) 
	{
		m_selected = m_bookFiles[m_index + ((10 * m_curFilePage) - 10)];

		m_window->beginRender();
		
		App::s_textures.m_textures["loading"]->draw(*m_window, 0, 0);	

		m_window->endRender();

		m_book = new Book(m_selected);
		m_book->parse(*m_window);

		m_isMenu = false;

		SDL_SetRenderDrawColor(m_window->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	}

	if (kDown & KEY_UP)
	{
		--m_index;
		if (m_index < 0)
		{
			m_index = 0;
		}
	}

	if (kDown & KEY_DOWN)
	{ 
		++m_index;
		if (m_index > 9)
		{
			m_index = 9;
		}

		int correctPos = m_index + ((10 * m_curFilePage) - 10);
		if (correctPos >= m_bookFiles.size())
		{
			correctPos = m_bookFiles.size() - 1;
			m_index = correctPos - ((10 * m_curFilePage) - 10);
		}
	}

	if (kDown & KEY_LEFT)
	{
		--m_curFilePage;
		m_index = 0;
	}
			
	if (kDown & KEY_RIGHT)
	{ 
		++m_curFilePage;
		m_index = 0;
	}
}

void GUI::eventBook(u32 kDown)
{
	if (kDown & KEY_B) 
	{
		m_selected = "";
		delete m_book;
		m_book = nullptr;
		m_isMenu = true;
	}
}

void GUI::updateMenu()
{
}

void GUI::updateBook()
{
	// We render twice, because the first render calculates and returns the optimal page width.
	int optimal = m_book->m_document->render(720);
	if(optimal < 720)
	{
		m_book->m_document->render(optimal);
	}
}

void GUI::renderMenu()
{
	if (!m_showInfo)
	{
		App::s_textures.m_textures["menu"]->draw(*m_window, 0, 0);
		App::s_textures.m_textures["fileBox"]->draw(*m_window, 426, 314);
		App::s_textures.m_textures["infoButton"]->draw(*m_window, 256, 620);
		App::s_textures.m_textures["exitButton"]->draw(*m_window, 896, 620);

		int baseY = 330; 
		auto result = std::div(m_bookFiles.size(), 10);
		int pageCount = 0;

		if (result.quot == 0)
		{
			pageCount = 1;
		}
		else if (result.quot != 0 && result.rem == 0)
		{
			pageCount = result.quot;
		}
		else if (result.quot != 0 && result.rem != 0)
		{
			pageCount = result.quot + 1;
		}

		if (m_curFilePage < 1)
		{
			m_curFilePage = 1;
		}
		else if (m_curFilePage > pageCount)
		{
			m_curFilePage = pageCount;
		}

		int begin = (m_curFilePage * 10) - 10;
		int end = begin + 10;

		if (begin < 0)
		{
			begin = 0;
		}

		if (end > m_bookFiles.size())
		{
			end = m_bookFiles.size();
		}

		for (int i = begin; i < end; ++i)
		{
			m_uiFont.renderText(m_window, m_bookFiles[i].c_str(), SDL_Colour{0, 0, 0, 255}, 494, baseY);
			baseY += 20;
		}

		float indexYPos = 330 + (m_index * 20);
		m_uiFont.renderText(m_window, "->", {0, 0, 0, 255}, 494 - 15, indexYPos);
	}
	else
	{
		App::s_textures.m_textures["info"]->draw(*m_window, 0, 0);
	}
}

void GUI::renderBook()
{
	litehtml::position pos(0, 0, 720, 1280);
	m_book->m_document->draw(nullptr, 0, 0, &pos);
}