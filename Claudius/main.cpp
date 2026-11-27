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


int main()
{
	bool running = true;
	RenderManager renderManager;

	SDLInit init;
	Window window;
	Renderer renderer(window);

	ResourceImpl resourceImpl(renderer.getRenderer());

	window.SetWindowParams(Game::windowWidth, Game::windowHeight, Game::title);


	Game game;
	
	float dt = 1.0f / 60.0f;
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT: running = false; break;
			case SDL_KEYDOWN: game.OnKeyDown(convertInput(e.key.keysym.sym)); break;
			}
		}

		game.Update(dt);
		game.Render(renderManager);
		
		SDL_SetRenderDrawColor(renderer.getRenderer(),0,0,0,0);
		SDL_RenderClear(renderer.getRenderer());
		for (auto &&entry : renderManager.spriteEntries)
		{
			if (entry.sprite.image != nullptr)
			{
				SDL_Rect src{ entry.sprite.source.x, entry.sprite.source.y, entry.sprite.source.w, entry.sprite.source.h };
				SDL_Rect dst{ static_cast<int>(entry.trans.position.x),
							  static_cast<int>(entry.trans.position.y),
							  static_cast<int>(entry.sprite.image->width),
							  static_cast<int>(entry.sprite.image->height) };
				SDL_RenderCopy(renderer.getRenderer(), resourceImpl.GetTexture(entry.sprite.image->id), &src, &dst);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer.getRenderer(), entry.sprite.color.r, entry.sprite.color.g, entry.sprite.color.b, entry.sprite.color.a);
				SDL_Rect rect{ static_cast<int>(entry.trans.position.x),
							   static_cast<int>(entry.trans.position.y),
							   entry.sprite.source.w,
							   entry.sprite.source.h };
				SDL_RenderDrawRect(renderer.getRenderer(), &rect);
			}
		}
		for (auto&& entry : renderManager.rectEntries)
		{
			SDL_SetRenderDrawColor(renderer.getRenderer(), entry.color.r, entry.color.g, entry.color.b, entry.color.a);
			SDL_Rect rect{ static_cast<int>(entry.trans.position.x),
						   static_cast<int>(entry.trans.position.y),
						   entry.rect.w,
						   entry.rect.h };
			//SDL_RenderDrawRect(renderer, &rect);	// <- If you want to draw the "outline" of the rectangle.
			SDL_RenderFillRect(renderer.getRenderer(), &rect);  // <- If you want to draw a "filled" rectangle. 
		}
		SDL_RenderPresent(renderer.getRenderer());
		renderManager.Clear();
		SDL_Delay(1000 / 20); //<- "Framerate".
	}


	return 0;
}
