#pragma once
#include "SDL.h"
#include <string>

class Window {
private:
	SDL_Window* window;

public:
	Window() {
		window = SDL_CreateWindow("Base", 0, 0, 0, 0, SDL_WindowFlags::SDL_WINDOW_RESIZABLE);
		if (window == nullptr)
		{
			throw std::exception("Error in window");
		}
	}
	~Window()
	{
		SDL_DestroyWindow(window);
	}

	// Delete copy operations
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	// Delete move operations
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	constexpr SDL_Window* getWindow() const noexcept {
		return window;
	}

	void SetWindowParams(int width, int height, std::string title)
	{
		SDL_SetWindowSize(window, width, height);
		SDL_SetWindowTitle(window, title.c_str());
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
};