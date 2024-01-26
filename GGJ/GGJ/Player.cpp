#include "Player.h"

void Player::init()
{
	//load the surface with image in the content
	//use this area later to initalise the sprite sheet for animations
	p_surface = IMG_Load("content/player_sheet.png");
	if (p_surface == NULL)
	{
		//if image could not be initalised throw error and stop program
		std::cerr << "could not initialize picture!\n";
		std::cerr << SDL_GetError() << std::endl;
		return;
	}
	//set the texture from the image on the surface
	this->p_texture = SDL_CreateTextureFromSurface(this->p_renderer, p_surface);

	//setting the start location of the player sprite + use the image width and height
	p_positionSrc.x = 0;
	p_positionSrc.y = 0;
	p_positionSrc.w = playerWidth;
	p_positionSrc.h = playerHeight;

	//this is the destination rect that is used on the screen instead of the source
	p_positionDest.x = 400;
	p_positionDest.y = 800;
	p_positionDest.w = playerWidth * 2;
	p_positionDest.h = playerHeight * 2;

	//free the surface once the image is on screen
	SDL_FreeSurface(p_surface);
}

void Player::processInput(SDL_Event e)
{
	//method to handle the directional movement of the player
	directionalMovement();
}

void Player::directionalMovement()
{
	bool topCollision = p_positionDest.y > 0;
	bool bottomCollision = (p_positionDest.y + p_positionDest.h) < (screenHeight / 10) * mapHeight;
	bool rightCollison = (p_positionDest.x + p_positionDest.w) < (screenWidth / 10) * mapWidth;
	bool leftCollison = p_positionDest.x > 0;
	//move the character up the screen and set relevant animation frames
	if (movingUp && topCollision)
	{
		p_positionSrc.x += playerWidth + 4;
		if (p_positionSrc.x > 76)
		{
			p_positionSrc.x = 0;
		}
		p_positionSrc.y = (playerHeight * 3) + 12;
		p_positionDest.y -= speed;
	}
	//move the character down the screen and set relevant animation frames
	if (movingDown && bottomCollision)
	{
		p_positionSrc.x += playerWidth + 4;
		if (p_positionSrc.x > 76)
		{
			p_positionSrc.x = 0;
		}
		p_positionSrc.y = 0;
		p_positionDest.y += speed;
	}

	//move the character left across the screen and set relevant animation frames
	if (movingLeft && leftCollison)
	{
		p_positionSrc.x += playerWidth + 4;
		if (p_positionSrc.x > 76)
		{
			p_positionSrc.x = 0;
		}
		p_positionSrc.y = playerHeight + 4;
		p_positionDest.x -= speed;
	}

	//move the character right across the screen and set relevant animation frames
	if (movingRight && rightCollison)
	{
		p_positionSrc.x += playerWidth + 4;
		if (p_positionSrc.x > 76)
		{
			p_positionSrc.x = 0;
		}
		p_positionSrc.y = (playerHeight * 2) + 8;
		p_positionDest.x += speed;
	}
}


void Player::throwProjectile(const int& mouseX, const int& mouseY, const int& ammoType)
{
	if (ammoType == club)
	{
		if (hasThrownClub)
		{
			std::cerr << "No club to throw\n";
			return;
		}
		hasThrownClub = true;
	}
	else if (ammoType == ball)
	{
		if (ballCount == 0)
		{
			std::cerr << "No ball to throw\n";
			return;
		}
	}
}

void Player::swingClub(const int& mouseX, const int& mouseY)
{
	swings++;
}

void Player::draw()
{
	p_drawDest = { p_positionDest.x - p_camera->x, p_positionDest.y - p_camera->y, p_positionDest.w, p_positionDest.h };
	SDL_RenderCopy(this->p_renderer, this->p_texture, &p_positionSrc, &p_drawDest);
	drawUI();
}

void Player::drawUI()
{
}

bool Player::checkCollision(SDL_Rect* other)
{
	return false;
}


void Player::clean()
{
	//destroys the created texture when the player is destroyed
	SDL_DestroyTexture(this->p_texture);
	if (playerUI)
	{
		//clear UI from memory and set to NULL
		delete playerUI;
		playerUI = nullptr;
	}
	if (playerClub)
	{
		delete playerClub;
		playerClub = nullptr;
	}
	if (AmmoTotal.size() > 0)
	{
		for (auto& aBall : AmmoTotal)
		{
			if (aBall != NULL)
			{
				delete aBall;
				aBall = nullptr;
			}
		}
	}
	AmmoTotal.clear();
}
