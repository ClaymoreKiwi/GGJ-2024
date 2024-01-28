#pragma once
#include "Gameloop.h"
#include "Camera.h"
#include <memory>
#include "EnemypathFinding.h"

class Player;
class TileMap;

class Enemy
{
public:
	//player constructor and initalised variables
	Enemy(SDL_Renderer* r, const int& screenW, const int& screenH, Camera* camera, Player* player, int rand, deltaTime* Time, std::shared_ptr<TileMap> tilemap)
		:e_renderer(r), screenWidth(screenW), screenHeight(screenH), e_camera(camera), player(player), i(rand), Time(Time), e_tileMap(tilemap)
	{
		init();
	}
	//initialises the player created at the beginning of the program
	void init();
	//called once per frame
	void update();
	//called once per frame
	void draw();
	//collision
	void AStarUpdate(SDL_Rect PlayerPos, SDL_Rect EnemyPos);
	//collision
	bool CheckCollisionPlayer(SDL_Rect* other);
	//garbage collection
	void clean();

	SDL_Rect* GetEnemyPosition()
	{
		return &e_drawDest;
	}

	bool GetCollision() {
		return isInCollision;
	}

private:
	//SDL veriables
	SDL_Texture*  e_texture = nullptr; //players sprite
	SDL_Renderer* e_renderer = nullptr; //rendering capable from this class
	SDL_Surface*  e_surface = nullptr; // surface to brin ghte image in and add it as a texture to the rect
	Camera*	  e_camera = nullptr; //camera refrence from gameloop
	SDL_Rect	  e_positionDest = { 0,0,0,0 }; //destination on that source to be 
	SDL_Rect	  e_positionSrc = { 0,0,0,0 }; //source rect for the projectile
	SDL_Rect	  e_drawDest = { 0,0,0,0 };
	deltaTime*	  Time = nullptr;

	//A* Variables
	std::vector<Node> path;
	int moveToX = -1, moveToY = -1;

	int* enemyX = nullptr;
	int* enemyY = nullptr;

	std::shared_ptr<TileMap> e_tileMap;
	//others
	Player* player = nullptr;

	const int enemyWidth = 34,
			  enemyHeight = 52,
			  screenWidth = 0,
			  screenHeight = 0,
			  i = 0,
			  diffMultipleX = 400,
			  diffMultipleY = 200;

	int e_health = 5,
		e_speed = 15;

	float e_time = 0;

	bool e_knockedOut = false,
		 isInCollision = false,
		 runAStar = false;
};

