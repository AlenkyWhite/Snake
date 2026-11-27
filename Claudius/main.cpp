#include "SDL.h"
#include "RenderManager.h"
#include "Game.h"
#include "Sprite.h"
#include "Transform.h"
#include "Image.h"
#include "SDLInit.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Input.hpp"

#undef main

//TODO delete everything about this
struct ResourceImpl
{
	ResourceImpl(SDL_Renderer* renderer) : renderer(renderer) {};
	std::vector<std::pair<std::string, SDL_Texture*>> textures;
	SDL_Renderer* renderer;
	SDL_Texture* GetTexture(unsigned int id)
	{
		if (id < textures.size())
			return textures[id].second;
		else
			return nullptr;
	}
};
struct RenderImpl
{
	SDL_Renderer* renderer;

};
void RenderManager::Render(const Sprite& sprite, const Transform& trans)
{
	spriteEntries.push_back({ sprite, trans });
}

void RenderManager::Render(const Rectangle& rect, const Color& color, const Transform& trans)
{
	rectEntries.push_back({ rect, color, trans });
}

void RenderManager::Clear()
{
	spriteEntries.clear();
	rectEntries.clear();
}

void CheckInput(bool& running, Game& game)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			running = false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			game.OnKeyDown(convertInput(e.key.keysym.sym));
		}
	}
}

int main()
{
	bool running = true;
	RenderManager renderManager;

	SDLInit init;
	Window window;
	Renderer renderer(window);

	window.SetWindowParams(Game::windowWidth, Game::windowHeight, Game::title);

	Game game;
	
	const float dt = 1.0f / 60.0f;
	while (running)
	{
		CheckInput(running, game);

		game.Update(dt);
		game.Render(renderManager);
		
		renderer.clear();
		
		for (auto&& entry : renderManager.rectEntries)
		{
			SDL_SetRenderDrawColor(renderer.getRenderer(), entry.color.r, entry.color.g, entry.color.b, entry.color.a);
			SDL_Rect rect{ static_cast<int>(entry.trans.position.x),
						   static_cast<int>(entry.trans.position.y),
						   entry.rect.w,
						   entry.rect.h };
			
			renderer.RenderRect(&rect);
		}
		renderer.RenderPresent();
		renderManager.Clear();
		SDL_Delay(1000 / 20); //<- "Framerate".
	}

	return 0;
}
