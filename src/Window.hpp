///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_WINDOW_HPP_
#define EBRNX_WINDOW_HPP_

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

///
/// The Window class to hold data about
/// an SDL_Window object.
///
class Window
{
public:
	///
	/// \brief Default constructor.
	///
	/// m_open defaults to true, and sdl2 window & renderer default to nullptr.
	///
	Window();

	///
	/// Defaulted destructor.
	///
	~Window() = default;

	///
	/// \brief Creates the window.
	///
	/// By default, the window takes up the entire screen.
	///
	/// \param title Title for the window / of the app.
	///
	void create(const char* title);

	///
	/// Clean up memory, sdl2 stuff, etc.
	///
	void destroy();

	///
	/// Clears the renderer in prep to draw to it.
	///
	void beginRender();

	///
	/// Displays everything to the renderer.
	///
	void endRender();

	///
	/// Retrieve the renderer.
	///
	/// \return CONST pointer to SDL_Renderer object. We want it const because we don't want the pointer to change.
	///
	SDL_Renderer* getRenderer() const;

public:
	///
	/// Keep track of window being open or not.
	///
	bool m_open;

private:
	///
	/// Pointer to sdl2 window data.
	///
	SDL_Window* m_window;

	///
	/// Pointer to sdl2 renderer data.
	///
	SDL_Renderer* m_renderer;
};

#endif