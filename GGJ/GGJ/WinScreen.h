#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "AudioPlayer.h"
#include "Button.h"
#include "FontRendering.h"
#include <fstream>

class WinScreen
{
public:
	WinScreen(SDL_Renderer* r, const int& screenWidth, const int& screenHeight)
		: ws_renderer(r), screenWidth(screenWidth), screenHeight(screenHeight)
	{
		init();
	}
	int init();
	void update();
	void draw();
	bool processInput();
	bool WinScreenRunning();
	void clean();
	int WinScreenStateUpdate();

	~WinScreen()
	{
		clean();
	}
private:
	SDL_Renderer* ws_renderer = nullptr;
	SDL_Surface*  ws_surface = nullptr;
	SDL_Texture*  ws_texture = nullptr;
	SDL_Rect	  ws_positionDest = { 0,0,0,0 }; //destination on that source to be viewed
	SDL_Rect	  ws_positionSrc = { 0,0,0,0 }; //source rect for the button
	//
	AudioPlayer* ws_audioPlayer = nullptr;
	//
	Button* mainMenu = nullptr;
	Button* retry = nullptr;
	Button* exitGame = nullptr;
	//
	int ws_score;
	//
	std::unique_ptr<FontRendering> fontRenderer;
	//
	const int screenWidth = 0, screenHeight = 0;

	int m_state = 0;
};

