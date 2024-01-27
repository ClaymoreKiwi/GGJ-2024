#include "GasCanister.h"

void GasCanister::init()
{
	bool textureCreatedSucessfully = CreateTexture();
	if (!textureCreatedSucessfully)
		return;
	this->audioPlayer = new AudioPlayer();
	//this->audioPlayer->PlaySound(1);
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
	SDL_Point center{ this->destRect.x, this->destRect.y
};

	SDL_RenderCopy(this->renderer, this->texture, NULL, &this->drawRect);
}

void GasCanister::OffsetObjectPositionUsingCameraPos()
{
	this->drawRect = { this->destRect.x, this->destRect.y, this->destRect.w, this->destRect.h };
};

void GasCanister::Update()
{

}

void GasCanister::setIsFull(bool value)
{
	this->isFull = value;
}

bool GasCanister::getIsFull()
{
	return this->isFull;
}

SDL_Rect GasCanister::GetCanisterRect()
{
	return this->destRect;
}
