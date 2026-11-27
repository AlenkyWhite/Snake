#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Base", 0, 0, 0, 0, SDL_WindowFlags::SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		throw new std::exception("Error in window");
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		throw new std::exception("Error in renderer");
	}
}

ResourceManager::~ResourceManager()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void ResourceManager::SetWindowParams(int width, int height, std::string title)
{
	SDL_SetWindowSize(window, width, height);
	SDL_SetWindowTitle(window, title.c_str());
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

//temporary
SDL_Renderer* ResourceManager::getRenderer() { return renderer; }