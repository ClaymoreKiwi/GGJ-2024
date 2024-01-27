#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "./deltaTime.h"
class GasCanister
{
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect* camera = nullptr;
	deltaTime* time = nullptr;
	SDL_Rect destRect = {200, 200, 75, 25};
	SDL_Rect drawRect = { 0,0,0,0 };

public:
	GasCanister(SDL_Renderer* r, const int& screenW, const int& screenH, SDL_Rect* camera, deltaTime* Time, int posX, int posY)
		:renderer(r), camera(camera), time(Time) {
		this->init();
		this->destRect.x = posX;
		this->destRect.y = posY;
	};

	void init();
	bool CreateTexture();
	void Render();
	void OffsetObjectPositionUsingCameraPos();
	void Update();;

	SDL_Rect GetCanisterRect();
};

