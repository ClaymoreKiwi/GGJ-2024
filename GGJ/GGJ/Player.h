#pragma once
#include <iostream>
#include <memory>
#include "Gameloop.h"

#include "Camera.h"
#include <vector>
#include "AudioPlayer.h"

//class refrences
class GasCanister;
class PlayerUI;
class deltaTime;

class Player
{
public:
	//player constructor and initalised variables
	Player(SDL_Renderer* r, const int& screenW, const int& screenH, Camera* camera, deltaTime* Time, std::vector<GasCanister*>* canisters)
		:p_renderer(r), screenWidth(screenW), screenHeight(screenH), p_camera(camera), Time(Time), gasCanisters(canisters)
	{
		init();;
	}
	//initialises the player created at the beginning of the program
	void init();
	//processes the event to the player per frame
	void processInput(SDL_Event e);
	//called once per frame
	//used for all the directional movement
	void directionalMovement();

	void Update();
	void AahhhhThatsBetter();
	void GoSaneAgain();
	void DecreaseSanity();
	void GoInsane();
	//called once per frame
	void draw();
	//used for isolating the UI elements from other draw calls
	void drawUI();
	//player collision
	bool checkCollision(SDL_Rect other, GasCanister* canister);
	//garbage collection
	void clean();

	void SetTerrainCheck(int val)
	{
		terrainCheck = val;
	}

private:
	//SDL veriables
	SDL_Texture* p_texture = nullptr; //players sprite
	SDL_Renderer* p_renderer = nullptr; //rendering capable from this class
	SDL_Surface* p_surface = nullptr; // surface to brin ghte image in and add it as a texture to the rect
	Camera* p_camera = nullptr;
	PlayerUI* playerUI = nullptr;
	deltaTime* Time = nullptr;
	SDL_Rect	  p_positionSrc = { 0,0,0,0 }; //source rect for the player
	SDL_Rect	  p_previousPos = { 0,0,0,0 };
	SDL_Rect p_drawRect = { 0,0,0,0 };
	AudioPlayer* audioPlayer;

	float insanityAmount = 100;
	bool insane = false;

	std::vector<GasCanister*>* gasCanisters;
	//int variables
	//34px * 52px - fixed variables for the sprite sheet accuracy
	const int playerWidth = 34,
		playerHeight = 52,
		screenWidth = 0,
		screenHeight = 0;

	int ballCount = 3,
		speed = 20,
		stamina = 100,
		terrainCheck = 0;

public:
	//movement flags bool
	bool movingUp = false,
		movingDown = false,
		movingLeft = false,
		movingRight = false,
		usingStamina = false,
		enemyIntersect = false,
		DoorTransition = false;

	SDL_Rect p_positionDest = { 0,0,0,0 }; //destination of the player sprite on the screen
};

