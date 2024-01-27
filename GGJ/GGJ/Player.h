#pragma once
#include <iostream>
#include <memory>
#include "Gameloop.h"
#include "GasCanister.h"
#include <vector>
#include "AudioPlayer.h"

//class refrences
class GolfClub;
class GolfBall;
class BallAmmo;
class PlayerUI;
class deltaTime;

class Player
{
public:
	//player constructor and initalised variables
	Player(SDL_Renderer* r, const int& screenW, const int& screenH, SDL_Rect* camera, deltaTime* Time, std::vector<GasCanister*>* canisters)
		:p_renderer(r), screenWidth(screenW), screenHeight(screenH), p_camera(camera), Time(Time), gasCanisters(canisters)
	{
		init();
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
	void DecreaseSanity();
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
	SDL_Rect* p_camera = nullptr; //camera refrence from gameloop
	PlayerUI* playerUI = nullptr;
	GolfClub* playerClub = nullptr;
	GolfBall* golfBall = nullptr;
	deltaTime* Time = nullptr;
	SDL_Rect	  p_positionSrc = { 0,0,0,0 }; //source rect for the player
	SDL_Rect	  p_previousPos = { 0,0,0,0 };
	AudioPlayer* audioPlayer;

	float insanityAmount = 100;

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
		hasThrownClub = false,
		enemyIntersect = false,
		canMoveRight = true,
		canMoveLeft = true,
		canMoveUp = true,
		canMoveDown = true;

	std::vector<BallAmmo*> AmmoTotal;
	SDL_Rect p_positionDest = { 0,0,0,0 }; //destination of the player sprite on the screen
};

