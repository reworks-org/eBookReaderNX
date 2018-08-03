///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_APP_HPP_
#define EBRNX_APP_HPP_

#include <memory>

#include "Book.hpp"
#include "Textures.hpp"
#include "SwitchContainer.hpp"

///
/// Represents the structure of the application.
///
class App
{
public:
	///
	/// Default constructor.
	///
	App();

	///
	/// Default destructor.
	///
	~App();

	///
	/// Main loop.
	///
	/// \return EXIT_SUCCESS.
	///
	int run();

	///
	/// Process events.
	///
	void event();

	///
	/// Update system based off of events.
	///
	void update();

	///
	/// Render everything to the screen.
	///
	void render();

public:
	///
	/// App textures.
	///
	static Textures s_textures;

	///
	/// The book being read.
	///
	static std::unique_ptr<Book> s_book;

private:
	///
	/// Represents the window.
	///
	Window m_window;

	///
	/// Litehtml container for this app.
	///
	SwitchContainer m_container;
};

#endif