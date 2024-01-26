#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include "AudioPlayer.h"
#include "Button.h"
//#include "FontRendering.h"
//#include "Background.h"

class MainMenu
{
public:
	MainMenu(SDL_Renderer*, const int&, const int&);
	int init();
	void update();
	void draw();
	bool processInput();
	bool menuRunning();
	void clean();
	int menuStateUpdate();

	~MainMenu()
	{
		clean();
	}

private:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Surface* m_surface = nullptr;
	SDL_Rect	  m_positionDest = { 0,0,0,0 }; //destination on that source to be viewed
	SDL_Rect	  m_positionSrc = { 0,0,0,0 }; //source rect for the button
	//
	//AudioPlayer* m_audioPlayer = nullptr;
	//
	Button* startGame = nullptr;
	Button* exitGame = nullptr;
	//
	//Background* background = nullptr;
	//
	//std::unique_ptr<FontRendering> fontRenderer;
	//
	const int screenWidth = 0, screenHeight = 0;

	int m_state = 0;
};

