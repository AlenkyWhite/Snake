#pragma once

#include "SDL.h"
#include <exception>
#include <string>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void SetWindowParams(int width, int height, std::string title);
	
	//temporary
	SDL_Renderer* getRenderer();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
