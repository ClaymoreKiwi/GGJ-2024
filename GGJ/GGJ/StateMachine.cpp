#include "StateMachine.h"

StateMachine::StateMachine()
{
	init();
}

int StateMachine::init()
{
	//initialise the SDL Lib
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "could not initialize SDL2!\n";
		std::cerr << SDL_GetError() << std::endl;
		return 1;
	}

	//create a window
	_window = SDL_CreateWindow("GGJ 2024", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN);
	//if window could not be initialised
	if (_window == NULL)
	{
		std::cerr << "could not initialize window!\n";
		std::cerr << SDL_GetError() << std::endl;
		return 1;
	}
	//initialise the renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//if renderer could not be initialised
	if (_renderer == NULL)
	{
		std::cerr << "could not initialize renderer!\n";
		std::cerr << SDL_GetError() << std::endl;
		return 1;
	}
	return 0;
}

void StateMachine::updateState()
{
	while (state != Exit)
	{
		switch (state)
		{
		case Menu:
		{
		#pragma region MainMenu loop
			MainMenu* mainMenu = new MainMenu(this->_renderer, _windowWidth, _windowHeight);
			if (mainMenu->init() < 0)
				mainMenu->menuRunning();
			//menu loop
			while (mainMenu->menuRunning())
			{
				//run all updates
				mainMenu->update();
			}
			state = mainMenu->menuStateUpdate();
			//destroy menu
			delete mainMenu;
			mainMenu = nullptr;
		#pragma endregion
		}
		break;
		case GamePlay:
		{
		#pragma region Gameloop
			//game loop goes here
			Gameloop* game = new Gameloop(this->_renderer, _windowWidth, _windowHeight);
			//init added to start application and init all game aspects
			if (game->init() < 0)
				game->gameRunning();
			//game loop
			while (game->gameRunning())
			{
				//run all updates
				game->update();
			}
			state = game->gameStateUpdate();
			//destroy all things and free memory before closing
			delete game;
			game = nullptr;
		#pragma endregion
		}
		break;

		case Lose:
		{
		#pragma region LoseGame loop
			LoseScreen* loseScreen = new LoseScreen(this->_renderer, _windowWidth, _windowHeight);
			if (loseScreen->init() < 0)
				loseScreen->LoseScreenRunning();
			//menu loop
			while (loseScreen->LoseScreenRunning())
			{
				//run all updates
				loseScreen->update();
			}
			state = loseScreen->LoseScreenStateUpdate();
			//destroy menu
			delete loseScreen;
			loseScreen = nullptr;
		#pragma endregion
		}
		break;
		case Win:
		{
		#pragma region WinGame loop
			WinScreen* winScreen = new WinScreen(this->_renderer, _windowWidth, _windowHeight);
			if (winScreen->init() < 0)
				winScreen->WinScreenRunning();
			//menu loop
			while (winScreen->WinScreenRunning())
			{
				//run all updates
				winScreen->update();
			}
			state = winScreen->WinScreenStateUpdate();
			//destroy menu
			delete winScreen;
			winScreen = nullptr;
		#pragma endregion
		}
		break;
		case Exit:
		{
			//close game
			SDL_DestroyWindow(_window);
			SDL_Quit();
		}
		break;
		};
	}
}
