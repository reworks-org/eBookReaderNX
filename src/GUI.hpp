///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_GUI_HPP_
#define EBRNX_GUI_HPP_

#include <vector>
#include <switch/types.h>

class Window;

class GUI
{
public:
	///
	/// \brief Constructor.
	///
	/// Loads books from directory on root of sd card.
	/// Create the directory if it does not exist.
	///
	/// \param window Window pointer to use internally.
	///
	GUI(Window* window);

	///
	/// Destructor.
	///
	~GUI();

	///
	/// Load the UI textures and other resources.
	///
	void create();

	///
	/// Clean up the UI.
	///
	void destroy();

	///
	/// Process UI events.
	///
	/// \param kDown Events from main event loop.
	///
	void event(u32 kDown);

	///
	/// Process UI updates.
	///
	void update();
	
	///
	/// Draw UI.
	///
	void render();

private:
	///
	/// Event processing for menu.
	///
	/// \param kDown Events from main event loop.
	///
	void eventMenu(u32 kDown);

	///
	/// Event processing for book ui.
	///
	/// \param kDown Events from main event loop.
	///
	void eventBook(u32 kDown);

	///
	/// Process updates for menu.
	///
	void updateMenu();

	///
	/// Process updates for book ui.
	///
	void updateBook();

	///
	/// Render menu.
	///
	void renderMenu();

	///
	/// Render book.
	///
	void renderBook();

private:
	///
	/// Pointer to window.
	///
	Window* m_window;

	///
	///	Is the app in the menu or reading a book.
	///
	bool m_isMenu;

	///
	/// All the names of the books in the books directory.
	///
	std::vector<std::string> m_bookFiles;
};

#endif