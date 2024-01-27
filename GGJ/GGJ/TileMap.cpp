#include "TileMap.h"
#include "Player.h"

TileMap::TileMap(SDL_Renderer* r, std::string fileName, Player* player, const int screenWidth, const int screenHeight)
	:tm_renderer(r), tm_mapName(fileName), player(player), tm_tileWidth(screenWidth), tm_tileHeight(screenHeight)
{
	init(fileName);
}

int TileMap::init(std::string fileName)
{
	loadMapFromFile(fileName.c_str());
	SDL_Surface* image = IMG_Load(tm_fileName.c_str());
	tm_texture = SDL_CreateTextureFromSurface(tm_renderer, image);
	SDL_FreeSurface(image);
	tm_tileWidth /= 15;
	tm_tileHeight /= 10;

	return 0;
}

void TileMap::loadMapFromFile(const char* filename)
{
	std::ifstream file(filename);
	//cehck if file is open or not
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}
	//work through each number in the file to form the array
	for (int i = 0; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapWidth; ++j)
		{
			//push the numbers into the gameMap array
			if (!(file >> gameMap[i][j]))
			{
				//for any reason it was unsuccessful throw error
				std::cerr << "Error reading data from file." << std::endl;
				file.close();
				return;
			}
		}
	}

	file.close();
}


void TileMap::draw(SDL_Rect camera)
{
	for (int i = 0; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapWidth; ++j)
		{
			SDL_Rect sourceRect;
			sourceRect.x = (gameMap[i][j] % 4) * tm_tileSizeSrc;
			sourceRect.y = (gameMap[i][j] / 4) * tm_tileSizeSrc;
			sourceRect.h = tm_tileSizeSrc;
			sourceRect.w = tm_tileSizeSrc;

			SDL_Rect DestRect;
			DestRect.x = (j * tm_tileWidth) - camera.x;
			DestRect.y = (i * tm_tileHeight) - camera.y;
			DestRect.w = tm_tileWidth;
			DestRect.h = tm_tileHeight;

			SDL_RenderCopy(this->tm_renderer, this->tm_texture, &sourceRect, &DestRect);
			CheckTileCollision(DestRect, &player->p_positionDest, gameMap[i][j], camera);
			if (gameMap[i][j] == 3)
			{

			}
		}
	}
}

bool TileMap::CheckTileCollision(SDL_Rect tileRect, SDL_Rect* playerRect, const int& tile, SDL_Rect camera)
{
	t_drawDest = { playerRect->x - camera.x, playerRect->y - camera.y, playerRect->w, playerRect->h };
	// store the sides of the Rect
	int leftTile, leftPlayer;
	int rightTile, rightPlayer;
	int topTile, topPlayer;
	int bottomTile, bottomPlayer;

	//define the sides tiles
	leftTile = tileRect.x;
	rightTile = tileRect.x + tileRect.w;
	topTile = tileRect.y;
	bottomTile = tileRect.y + tileRect.h;

	//define sides Player
	leftPlayer = t_drawDest.x;
	rightPlayer = t_drawDest.x + t_drawDest.w;
	//we want the area around the feet
	topPlayer = static_cast<int>((playerRect->y + (playerRect->h * 0.75f)) - camera.y);
	bottomPlayer = t_drawDest.y + t_drawDest.h;


	if (bottomPlayer <= topTile || topPlayer >= bottomTile || rightPlayer <= leftTile || leftPlayer >= rightTile)
	{
		return false;
	}
	switch (tile)
	{
	case Wall:

		player->SetTerrainCheck(Wall);
		return true;
	case Door:
		player->SetTerrainCheck(Door);
		return true;
	default:
		player->SetTerrainCheck(0);
		// No special behavior for other tile types
		return false;
	}
}

void TileMap::UpdateMap(std::string mapName)
{
	loadMapFromFile(mapName.c_str());
}
