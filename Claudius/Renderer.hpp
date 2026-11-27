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
			throw std::exception("Error in renderer");
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
};