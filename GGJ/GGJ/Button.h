#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "FontRendering.h"
//#include "AudioPlayer.h"

class Button
{
public:

	Button(SDL_Renderer* r, std::string fPath, const int& screenW, const int& screenH);
	int init();
	bool processInput(SDL_Event e);
	/// <summary>
	/// pass in the text you want displayed and an X position and a Y position for the positioning of the button 
	/// </summary>
	/// <param name="">Text</param>
	/// <param name="">PosX</param>
	/// <param name="">PosY</param>
	void draw(std::string, const int&, const int&);
	void clean();

private: // variables
	SDL_Renderer* btn_renderer = nullptr;
	SDL_Texture* btn_texture = nullptr; //button Image sheet
	SDL_Rect	  btn_positionSrc = { 0,0,0,0 }; //source rect for the player
	SDL_Rect	  btn_positionDest = { 0,0,0,0 }; //destination on that source to be viewed
	SDL_Surface* btn_surface = nullptr;

	std::unique_ptr<FontRendering> fontRenderer;

	std::string btn_filePath = nullptr; //button image location

	const int btn_screenWidth = 0,
		btn_screenHeight = 0; //screen width and height

	struct //struct for the mouse position
	{
		int x = 0,
			y = 0;
	}mousePos;

	// flags for checking mouse states
	bool clicked = false,
		hovered = false,
		playOnce = false;
};

