#pragma once

#include <string>
#include <vector>
#include "KeyCode.h"
#include "Apple.h"
#include "Player.h"

class Game
{
	Player playerOne;
	Apple apple;

public:
	//Teemu Code Begin.

	// float timer; <- can be used in delta time
	// float updateInterval; <- check Game.h
	static const int windowWidth = 1250;
	static const int windowHeight = 700;
	inline static const std::string title = "Snake";

	Game();
	~Game();
	void Update(double dt);
	void Render(RenderManager& rendererManager);
	void OnKeyDown(KeyCode key);
	void OnKeyUp(KeyCode key);
};