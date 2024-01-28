#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "deltaTime.h"
#include "TileMap.h"
#include "Camera.h"

class Player;
class GasCanister;
class Enemy;

class Gameloop
{
public:
	Gameloop(SDL_Renderer*, const int, const int);
	int init();
	void MakeCanisters();
	void GiveCanistersPlayerRef(Player* player);
	std::string LoadMap(const int);
	void update();
	void draw();
	bool processInput();
	bool gameRunning();
	int gameStateUpdate();
	void clean();
	~Gameloop()
	{
		clean();
	}

private:
	std::vector<GasCanister*> gasCanisters;
	//for creating the window and the renderer for whatever is on screen
	SDL_Renderer* g_renderer = nullptr;
	SDL_Texture* g_textureCRT = nullptr;
	Player* player = nullptr;

	//dont worry about this camera 
	Camera* CameraC = nullptr;

	deltaTime* Time = nullptr;
	std::shared_ptr<TileMap> g_tiledMap;

	std::vector<Enemy*> enemyList;
	//for the window width and height to be accessed elsewhere
	const int windowWidth,
		windowHeight;

	int g_state = 0,
		g_mapComplete = 0;

	bool g_usingClub = true;

	enum MapNumber
	{
		MapOne,
		MapTwo,
		TotalMaps,
	};

public:
	SDL_Rect camera = { 0,0, windowWidth, windowHeight }; // camera set position 0/0 and size of the screen

	struct //struct for the mouse position
	{
		int x = 0,
			y = 0;
	}mousePos;
};

