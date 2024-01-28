#include "Enemy.h"
#include "Player.h"
#include "TileMap.h"
#include <random>


void Enemy::init()
{
	//load the surface with image in the content
	e_surface = IMG_Load("content/enemy_sheet.png");
	if (e_surface == NULL)
	{
		//if image could not be initalised throw error and stop program
		std::cerr << "could not initialize picture!\n";
		std::cerr << SDL_GetError() << std::endl;
		return;
	}
	//set the texture from the image on the surface
	this->e_texture = SDL_CreateTextureFromSurface(this->e_renderer, e_surface);

	std::random_device rd;

	// Use two different Mersenne Twister engines for different distributions
	std::mt19937 gen1(rd());
	std::mt19937 gen2(rd());

	// Define distributions for the two random variables
	std::uniform_int_distribution<int> distribution1(800, ((screenWidth / 10) * mapWidth));
	std::uniform_int_distribution<int> distribution2(400, ((screenHeight / 10) * mapHeight));

	// Generate two random numbers
	int randomXPos = distribution1(gen1);
	int randomYpos = distribution2(gen2);

	//setting the start location of the player sprite + use the image width and height
	e_positionSrc.x = 0;
	e_positionSrc.y = 0;
	e_positionSrc.w = enemyWidth;
	e_positionSrc.h = enemyHeight;

	//this is the destination rect that is used on the screen instead of the source
	e_positionDest.x = randomXPos;
	e_positionDest.y = randomYpos;
	e_positionDest.w = enemyWidth * 2;
	e_positionDest.h = enemyHeight * 2;

	enemyX = &e_positionDest.x;
	enemyY = &e_positionDest.y;
	//free the surface once the image is on screen
	SDL_FreeSurface(e_surface);
	runAStar = false;
}

void Enemy::update()
{
	e_time += Time->GetDeltaTime();
	if (e_time != 0.0f && e_time >= 5.0f + i && !e_knockedOut)
	{
		runAStar = true;
		e_time -= 5.0f + i;
	}
	if (runAStar && !e_knockedOut)
	{
		AStarUpdate(player->p_positionDest, e_positionDest);
	}

	CheckCollisionPlayer(&player->p_positionDest);

	if (e_health <= 0)
	{
		e_knockedOut = true;
	}
	if (e_knockedOut && e_time != 0.0f && e_time >= 10.0f)
	{
		e_knockedOut = false;
		e_health = 5;
		e_time -= 5.0f + i;
	}
}

void Enemy::draw()
{
	e_drawDest = { e_positionDest.x - e_camera->GetCamera().x, e_positionDest.y - e_camera->GetCamera().y, e_positionDest.w, e_positionDest.h};
	if (e_knockedOut)
	{
		e_positionSrc.x = 115;
		e_positionSrc.y = 0;
		e_positionSrc.w = 46;
		e_positionSrc.h = 37;
		e_drawDest.w = e_positionSrc.w * 2;
		e_drawDest.h = e_positionSrc.h * 2;
		SDL_RenderCopy(this->e_renderer, this->e_texture, &e_positionSrc, &e_drawDest);
	}
	else
	{
		e_positionSrc.x = 0;
		e_positionSrc.y = 0;
		e_positionSrc.w = enemyWidth;
		e_positionSrc.h = enemyHeight;
	}

	//std::cout << e_positionDest.x << " : " << e_positionDest.y << std::endl;
	SDL_RenderCopy(this->e_renderer, this->e_texture, &e_positionSrc, &e_drawDest);

	if (path.size() > 1) {
		*enemyX = path[1].x * 66;
		*enemyY = path[1].y * 60;

		path.erase(path.begin());
	}
}

void Enemy::AStarUpdate(SDL_Rect PlayerPos, SDL_Rect EnemyPos)
{
	moveToX = PlayerPos.x / 66;
	moveToY = PlayerPos.y / 60;
	*enemyX = (EnemyPos.x) / 66;
	*enemyY = (EnemyPos.y) / 60;

	// Ensure enemyX and enemyY are within valid range
	*enemyX = std::max(0, std::min(*enemyX, mapWidth -1));
	*enemyY = std::max(0, std::min(*enemyY, mapHeight-1));

	Node Enemy;
	Enemy.x = *enemyX;
	Enemy.y = *enemyY;
	Node dest;
	dest.x = moveToX;
	dest.y = moveToY;

	path = aStar(*e_tileMap, Enemy, dest);
	runAStar = false;
	//std::cout << e_positionDest.x << " : " << e_positionDest.y << std::endl;
}

bool Enemy::CheckCollisionPlayer(SDL_Rect* other)
{
	if (!e_knockedOut)
	{
		SDL_Rect check = { other->x - e_camera->GetCamera().x, other->y - e_camera->GetCamera().y, other->w, other->h };
		if (SDL_HasIntersection(&check, &e_drawDest))
		{
			player->enemyIntersect = true;
			return true;
		}
		player->enemyIntersect = false;
	}
	return false;
}

void Enemy::clean()
{
	SDL_DestroyTexture(e_texture);
	enemyX = nullptr;
	enemyY = nullptr;
}
