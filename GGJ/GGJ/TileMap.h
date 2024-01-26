#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <fstream>

class Player;
const int mapWidth = 40, mapHeight = 20;
struct Circle_Col
{
	int x, y;
	int radius;
};

class TileMap
{
public:
	TileMap(SDL_Renderer* r, std::string fileName, Player* player, const int screenWidth, const int screenHeight);

	int init(std::string);
	void draw(SDL_Rect Camera);
	void loadMapFromFile(const char* filename);
	bool CheckTileCollision(SDL_Rect tile, SDL_Rect* player, const int&, SDL_Rect camera);
	void UpdateMap(std::string mapName);
	~TileMap()
	{
		SDL_DestroyTexture(tm_texture);
	}
	const int* operator[] (int row) const {
		return gameMap[row];
	}

private:
	SDL_Renderer* tm_renderer;
	const std::string tm_fileName = "content/background/background_sheet.png";
	std::string		  tm_mapName;
	SDL_Texture* tm_texture;
	Player* player = nullptr;
	SDL_Rect		  t_drawDest = { 0,0,0,0 };

	const int tm_tileSizeSrc = 25;

	int	tm_tileWidth,
		tm_tileHeight; //adjust for the screen resolution

public:

	int gameMap[mapHeight][mapWidth];
};

enum terrain
{
	SAND = 4,
	HIGHGRASS = 5,
	WATER = 6,
	FLAG = 7,
};

