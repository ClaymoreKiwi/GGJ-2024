#include "GasCanister.h"

void GasCanister::init()
{
	bool textureCreatedSucessfully = CreateTexture();
	if (!textureCreatedSucessfully)
		return;
}

bool GasCanister::CreateTexture()
{
	SDL_Surface* canisterSurface = IMG_Load("content/objects/entonox_can.png");
	if (canisterSurface == NULL)
	{
		//if image could not be initalised throw error and stop program
		std::cerr << "could not initialize picture!\n";
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	this->texture = SDL_CreateTextureFromSurface(this->renderer, canisterSurface);
	SDL_FreeSurface(canisterSurface);
	return true;
}

void GasCanister::Render()
{
	OffsetObjectPositionUsingCameraPos();
	SDL_Point center{ this->destRect.x / 2, this->destRect.y / 2 };

	SDL_RenderCopyEx(this->renderer, this->texture, NULL, &this->drawRect, -90, &center, SDL_FLIP_NONE);
}

void GasCanister::OffsetObjectPositionUsingCameraPos()
{
	this->drawRect = { this->destRect.x - this->camera->x, this->destRect.y - this->camera->y, this->destRect.w, this->destRect.h };
};

void GasCanister::Update()
{

}
