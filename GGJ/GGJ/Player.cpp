#include "Player.h"
#include "PlayerUI.h"

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
	p_positionDest.x = 200;
	p_positionDest.y = 200;
	p_positionDest.w = playerWidth * 2;
	p_positionDest.h = playerHeight * 2;

	//free the surface once the image is on screen
	SDL_FreeSurface(p_surface);

	playerUI = new PlayerUI(this->p_renderer, p_camera, screenWidth, screenHeight, &stamina);
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


void Player::Update()
{

	switch (terrainCheck)
	{
	case Wall:
		//update movement bool
		break;
	case Door:
		
		//update camera
		break;
	default:
		//no special implementation
		break;
	}

	for (GasCanister* canister : *this->gasCanisters) {
		if (this->checkCollision(canister->GetCanisterRect(), canister))
			AahhhhThatsBetter();
	}

	DecreaseSanity();
}


void Player::AahhhhThatsBetter()
{
	this->insanityAmount = this->insanityAmount + 50 > 100 ? 100 : this->insanityAmount + 50;
	std::cout << "canister collected" << std::endl;
}
void Player::DecreaseSanity()
{
	this->insanityAmount -= 1;
	std::cout << this->insanityAmount << std::endl;
}


void Player::draw()
{
	//draw player pos
	SDL_RenderCopy(this->p_renderer, this->p_texture, &p_positionSrc, &p_positionDest);
	drawUI();
}

void Player::drawUI()
{
}

bool Player::checkCollision(SDL_Rect other, GasCanister* canister)
{
	
	if (SDL_HasIntersection(&this->p_positionDest, &other) && canister->getIsFull()) {
		canister->setIsFull(false);
		return true;
	}

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
}
