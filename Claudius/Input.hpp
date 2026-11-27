#pragma once
#include <SDL.h>

enum class Input
{
	Left,
	Right,
	Up,
	Down
};

static Input convertInput(SDL_Keycode key)
{
	if (key == SDLK_LEFT || key == SDLK_a) return Input::Left;
	if (key == SDLK_RIGHT || key == SDLK_d) return Input::Right;
	if (key == SDLK_UP || key == SDLK_w) return Input::Up;
	if (key == SDLK_DOWN || key == SDLK_s) return Input::Down;
}