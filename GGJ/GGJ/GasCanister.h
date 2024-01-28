#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Camera.h"
#include "AudioPlayer.h"
#include "Player.h"
#include "./deltaTime.h"

class GasCanister
{
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	Camera* camera = nullptr;
	deltaTime* time = nullptr;
	SDL_Rect destRect = {200, 200, 25, 75};
	SDL_Rect drawRect = { 0,0,0,0 };
	bool isFull = true;
	AudioPlayer* audioPlayer;
	Player* player = nullptr;
	int audioChannel = -1;

public:
	GasCanister(SDL_Renderer* r, const int& screenW, const int& screenH, Camera* camera, deltaTime* Time, int posX, int posY, int audioChannel)
		:renderer(r), camera(camera), time(Time), audioChannel(audioChannel) {
		this->init();
		this->destRect.x = posX;
		this->destRect.y = posY;
		this->audioPlayer = new AudioPlayer();
	};

	~GasCanister() {
		if (player != NULL)
		{
			//clear player from memory and set to NULL
			delete player;
			player = nullptr;
		}

		if (this->camera != NULL)
		{
			//clear player from memory and set to NULL
			delete camera;
			camera = nullptr;
		}

		if (this->audioPlayer != NULL)
		{
			//clear player from memory and set to NULL
			delete audioPlayer;
			audioPlayer = nullptr;
		}
	}

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

