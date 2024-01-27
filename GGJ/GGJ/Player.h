#pragma once
#include <iostream>
#include <memory>
#include "Gameloop.h"
#include "GasCanister.h"
#include <vector>

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
	//player swinging club to interact with the ball
	void swingClub(const int&, const int&);
	//throwing the club at the enemy
	void throwProjectile(const int&, const int&, const int&);

	void Update();
	//called once per frame
	void draw();
	//used for isolating the UI elements from other draw calls
	void drawUI();
	//player collision
	bool checkCollision(SDL_Rect other);
	//garbage collection
	void clean();

	SDL_Rect* GetGolfClub();
	void SetGolfClubState();
	GolfClub* GetClub()
	{
		return playerClub;
	}
	void SetTerrainCheck(int val)
	{
		terrainCheck = val;
	}
	void SetSwings()
	{
		swings++;
	}
	int GetSwings()
	{
		return swings;
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
	SDL_Rect	  p_drawDest = { 0,0,0,0 }; // destination rect for the player position based on the camera
	SDL_Rect	  p_previousPos = { 0,0,0,0 };

	float insanityAmount;

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
		swings = 0,
		strokePower = 0,
		terrainCheck = 0;

	enum clubOrBall
	{
		club = 0,
		ball,
	};

public:
	//movement flags bool
	bool movingUp = false,
		movingDown = false,
		movingLeft = false,
		movingRight = false,
		usingStamina = false,
		hasThrownClub = false,
		enemyIntersect = false,
		canMove = true;

	std::vector<BallAmmo*> AmmoTotal;
	SDL_Rect p_positionDest = { 0,0,0,0 }; //destination of the player sprite on the screen
};

