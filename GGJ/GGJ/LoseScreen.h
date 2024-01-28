#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "AudioPlayer.h"
#include "Button.h"
#include "FontRendering.h"

class LoseScreen
{
public:
	LoseScreen(SDL_Renderer* r, const int& screenWidth, const int& screenHeight)
		: ls_renderer(r), screenWidth(screenWidth), screenHeight(screenHeight)
	{
		init();
	}
	int init();
	void update();
	void draw();
	bool processInput();
	bool LoseScreenRunning();
	void clean();
	int LoseScreenStateUpdate();

	~LoseScreen()
	{
		clean();
	}
private:
	SDL_Renderer* ls_renderer = nullptr;
	SDL_Texture*  ls_texture = nullptr;
	SDL_Rect	  ls_positionDest = { 0,0,0,0 }; //destination on that source to be viewed
	SDL_Rect	  ls_positionSrc = { 0,0,0,0 }; //source rect for the button
	//
	AudioPlayer* ls_audioPlayer = nullptr;
	//
	Button* mainMenu = nullptr;
	Button* retry = nullptr;
	Button* exitGame = nullptr;
	//
	std::unique_ptr<FontRendering> fontRenderer;
	//
	const int screenWidth = 0, screenHeight = 0;

	int m_state = 0;
};

