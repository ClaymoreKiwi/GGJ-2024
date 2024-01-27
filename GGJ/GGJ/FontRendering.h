#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <iostream>

class FontRendering
{
public:
	FontRendering(SDL_Renderer*, const int&, const int&);
	void init();
	/// <summary>
	/// Leave all parameters blank for text to occupy the whole screen
	/// </summary>
	/// <param name="">Text</param>
	void draw(std::string);
	/// <summary>
	/// Overridden renderer to accept the position (X, Y) and the width and height of the rendered text and position based off the center and what colour is passed into it
	/// </summary>
	/// <param name="">Text</param>
	/// <param name="">posX</param>
	/// <param name="">posY</param>
	/// <param name="">Width</param>
	/// <param name="">height</param>
	/// <param name="">RGBA</param>
	void draw(std::string text, const int& posX, const int& posY, int&& width, int&& height, int[4]);
	void clean();

private:
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr;

	const int screenWidth,
		screenHeight;
};

