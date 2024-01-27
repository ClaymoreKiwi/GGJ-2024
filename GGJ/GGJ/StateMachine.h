#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "MainMenu.h"
#include "Gameloop.h"

class StateMachine
{
public:
	StateMachine();
	int init();
	void updateState();

private:
	enum state
	{
		Menu = 0,
		GamePlay = 1,
		Lose = 2,
		Win = 3,
		Exit = 5
	};

	int state = GamePlay;

	SDL_Window*		_window = nullptr;
	SDL_Renderer*	_renderer = nullptr;

	const int	    _windowWidth = 1000,
					_windowHeight = 600;
};

