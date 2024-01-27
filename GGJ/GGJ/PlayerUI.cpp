#include "PlayerUI.h"

void PlayerUI::init()
{
	UI_surface = IMG_Load("content/UI/Stamina_border.png");
	if (UI_surface == NULL)
	{
		//if image could not be initalised throw error and stop program
		std::cerr << "could not initialize the stamina bar!\n";
		std::cerr << SDL_GetError() << std::endl;
		return;
	}
	//set the texture from the image on the surface
	this->UI_staminaBorderTexture = SDL_CreateTextureFromSurface(this->UI_renderer, UI_surface);

	//setting the start location of the player sprite + use the image width and height
	UI_positionSrc.x = 0;
	UI_positionSrc.y = 0;
	UI_positionSrc.w = 100;
	UI_positionSrc.h = 25;

	//this is the destination rect that is used on the screen instead of the source
	UI_positionDest.x = 0;
	UI_positionDest.y = 0;
	UI_positionDest.w = 100;
	UI_positionDest.h = 25;

	//free the surface once the image is on screen
	SDL_FreeSurface(UI_surface);
	UI_surface = IMG_Load("content/UI/Stamina_fill.png");
	if (UI_surface == NULL)
	{
		//if image could not be initalised throw error and stop program
		std::cerr << "could not initialize the stamina bar!\n";
		std::cerr << SDL_GetError() << std::endl;
		return;
	}
	this->UI_staminaFillTexture = SDL_CreateTextureFromSurface(this->UI_renderer, UI_surface);
	SDL_FreeSurface(UI_surface);

	fontRenderer = std::unique_ptr<FontRendering>(new FontRendering(UI_renderer, UI_screenWidth, UI_screenHeight));

}

void PlayerUI::update()
{
	std::string Par = "Par: " + std::to_string(*UI_swings);
	int White[4] = { 255,245,217,255 }; //specified white for the font
	fontRenderer->draw(Par, 400, 50, 100, 50, White);
}

void PlayerUI::draw(SDL_Rect posOffset, const int& playerW)
{

	//use this for dynamic UI that will be updated around the player
    posOffset.x -= camera->x + (playerW / 2);
	posOffset.y -= camera->y + UI_positionDest.h;
  	posOffset.w = UI_positionDest.w;
	posOffset.h = UI_positionDest.h;
	SDL_RenderCopy(this->UI_renderer, this->UI_staminaBorderTexture, &UI_positionSrc, &posOffset);
	posOffset.w = *UI_staminaFillPercentage;
	SDL_RenderCopy(this->UI_renderer, this->UI_staminaFillTexture, &UI_positionSrc, &posOffset);
}

