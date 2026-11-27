#pragma once
#include "SDL.h"
#include "Window.hpp"
#include <exception>

class Renderer {
private:
	SDL_Renderer* renderer;

public:
	explicit Renderer(const Window& window) {
		renderer = SDL_CreateRenderer(window.getWindow(), -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr)
		{
			throw std::exception(SDL_GetError());
		}
	}
	~Renderer() {
		SDL_DestroyRenderer(renderer);
	}

	// Delete copy operations
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	// Delete move operations
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	constexpr SDL_Renderer* getRenderer() const noexcept {
		return renderer;
	}

	void clear() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
	}

	void RenderRect(const SDL_Rect* rect)
	{
		//SDL_RenderDrawRect(renderer, &rect);	// <- If you want to draw the "outline" of the rectangle.
		SDL_RenderFillRect(renderer, rect);  // <- If you want to draw a "filled" rectangle. 
	}

	void RenderPresent()
	{
		SDL_RenderPresent(renderer);
	}
};