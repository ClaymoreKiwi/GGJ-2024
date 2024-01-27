#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "AudioPlayer.h"
#include "Player.h"
#include "./deltaTime.h"

class GasCanister
{
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect* camera = nullptr;
	deltaTime* time = nullptr;
	SDL_Rect destRect = {200, 200, 25, 75};
	SDL_Rect drawRect = { 0,0,0,0 };
	bool isFull = true;
	AudioPlayer* audioPlayer;
	Player* player = nullptr;
	int audioChannel = -1;

public:
	GasCanister(SDL_Renderer* r, const int& screenW, const int& screenH, SDL_Rect* camera, deltaTime* Time, int posX, int posY, int audioChannel)
		:renderer(r), camera(camera), time(Time), audioChannel(audioChannel) {
		this->init();
		this->destRect.x = posX;
		this->destRect.y = posY;
		this->audioPlayer = new AudioPlayer();
	};

	void init();
	bool CreateTexture();
	void Render();
	void OffsetObjectPositionUsingCameraPos();
	void Update();;
	void setIsFull(bool value);
	bool getIsFull();
	void setPlayerRef(Player* player);

	SDL_Rect GetCanisterRect();
};

