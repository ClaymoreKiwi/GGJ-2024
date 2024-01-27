#include "FontRendering.h"

FontRendering::FontRendering(SDL_Renderer* r, const int& screenW, const int& screenH)
	: renderer(r), screenWidth(screenW), screenHeight(screenH)
{
	init();
}

void FontRendering::init()
{
	int init = TTF_Init();
	if (init != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
	}
	font = TTF_OpenFont("content/fonts/Static.ttf", 100);
	if (font == NULL)
	{
		std::cerr << SDL_GetError() << std::endl;
	}
}

void FontRendering::draw(std::string text)
{
	SDL_Color colour = SDL_Color();
	colour.r = 58; //red
	colour.g = 171; //green
	colour.b = 41; //blue
	colour.a = 255; // alpha 

	//create a surface for the font
	SDL_Surface* textImg = TTF_RenderText_Solid(font, text.c_str(), colour);
	//create a texture to display from the sureace
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textImg);
	//render copy
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	//free resources
	SDL_FreeSurface(textImg);
	SDL_DestroyTexture(texture);
}

void FontRendering::draw(std::string text, const int& posX, const int& posY, int&& width, int&& height, int rgba[4])
{
	SDL_Color colour = SDL_Color();
	colour.r = rgba[0]; //red
	colour.g = rgba[1]; //green
	colour.b = rgba[2]; //blue
	colour.a = rgba[3]; //alpha 

	//create a surface for the font
	SDL_Surface* textImg = TTF_RenderText_Solid(font, text.c_str(), colour);
	//create a texture to display from the sureace
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textImg);
	SDL_Rect fontSize;
	fontSize.w = width;
	fontSize.h = height;
	int middleX = ((0 + fontSize.w) / 2);
	int middleY = ((0 + fontSize.h) / 2);
	fontSize.x = posX - middleX;
	fontSize.y = posY - middleY;

	//render copy
	SDL_RenderCopy(renderer, texture, NULL, &fontSize);
	//free resources
	SDL_FreeSurface(textImg);
	SDL_DestroyTexture(texture);
}

void FontRendering::clean()
{
	TTF_CloseFont(font);
	TTF_Quit();
}
