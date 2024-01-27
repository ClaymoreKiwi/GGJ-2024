#pragma once
#include "Player.h"
#include "FontRendering.h"

class GolfClub;

class PlayerUI
{
public:
	//initialiser list determine from the player calss
	PlayerUI(SDL_Renderer* r, SDL_Rect* camera, const int& screenW, const int& screenH, int* playerStamina, int* swings)
		: UI_renderer(r), camera(camera), UI_screenWidth(screenW), UI_screenHeight(screenH), UI_staminaFillPercentage(playerStamina), UI_swings(swings)
	{
		init();
	}
	void init();
	void update();
	void draw(SDL_Rect, const int&); // dynamic UI elements get drwn here in the overloaded draw
	~PlayerUI()
	{
		SDL_DestroyTexture(UI_staminaBorderTexture);
		SDL_DestroyTexture(UI_staminaFillTexture);

	}

private:
	SDL_Renderer* UI_renderer = nullptr;
	SDL_Texture*  UI_staminaBorderTexture = nullptr; //UI for stamina
	SDL_Texture*  UI_staminaFillTexture = nullptr; //UI for stamina
	SDL_Rect	  UI_positionSrc = { 0,0,0,0 }; //source rect for the stamina
	SDL_Rect	  UI_positionDest = { 0,0,0,0 }; //destination on that source to be viewed
	SDL_Surface*  UI_surface = nullptr;
	SDL_Rect*	  camera;

	std::unique_ptr<FontRendering> fontRenderer;

	const int UI_screenWidth = 0,
			  UI_screenHeight = 0;

	int* UI_staminaFillPercentage;
	int* UI_swings;
};

