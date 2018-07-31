///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include "Window.hpp"

Window::Window()
:m_open(true), m_window(nullptr), m_renderer(nullptr)
{
}

void Window::create(const char* title)
{
	// Create sdl2 window and renderer, ensuring compatibility with switch, and that window takes up whole switch screen.
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
}

void Window::destroy()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void Window::beginRender()
{
	SDL_RenderClear(m_renderer);
}

void Window::endRender()
{
	SDL_RenderPresent(m_renderer);
}

SDL_Renderer* Window::getRenderer() const
{
	return m_renderer;
}