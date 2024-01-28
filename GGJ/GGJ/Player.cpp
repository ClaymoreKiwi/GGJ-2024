#include "Player.h"
#include "PlayerUI.h"
#include "GasCanister.h"

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
	p_positionDest.y = 300;
	p_positionDest.w = playerWidth * 2;
	p_positionDest.h = playerHeight * 2;

	//free the surface once the image is on screen
	SDL_FreeSurface(p_surface);

	playerUI = new PlayerUI(this->p_renderer, &p_camera->GetCamera(), screenWidth, screenHeight, &stamina);
	this->audioPlayer = new AudioPlayer();
	int track = this->audioPlayer->PlaySound(AudioPlayer::laugh, -1, -1);
	this->audioPlayer->SetVolume(track, 128);
	this->audioPlayer->TrackSelect("./content/sounds/BackgroundSounds.wav");
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

	bool moving = movingDown || movingLeft || movingRight || movingUp;
	if (moving == true && this->ReadyToStartMoving == true) {
		this->ReadyToStartMoving = false;
		this->footstepChannel = this->audioPlayer->PlaySound(AudioPlayer::footstep, -1, -1);
	}
	else if (moving == false && this->ReadyToStartMoving == false) {
		this->ReadyToStartMoving = true;
		this->audioPlayer->Stop(footstepChannel);
	}
}


void Player::Update()
{
	if (canMove)
	{
		p_previousPos.x = p_positionDest.x;
		p_previousPos.y = p_positionDest.y;
		p_previousPos.w = p_positionDest.w;
		p_previousPos.h = p_positionDest.h;
	}

	switch (terrainCheck)
	{
	case Wall:
		p_positionDest = p_previousPos;
		//update movement bool
		break;
	case Door:
		canMove = true;
		if (!DoorTransition)
		{
			int distRight = screenWidth - p_drawRect.x;
			int distBottom = screenHeight - p_drawRect.y;

			int distances[4]= {distRight, p_drawRect.x, distBottom, p_drawRect.y};

			int smallestDistance = 9999999;
			char direction;
			for (int i = 0; i < 4; ++i) {
				if (distances[i] < smallestDistance) {
					smallestDistance = distances[i];
					switch (i) {
					case 0:
						direction = 'R';
						break;
					case 1:
						direction = 'L';
						break;
					case 2:
						direction = 'D';
						break;
					case 3:
						direction = 'U';
						break;
					}
				}
			}

			switch (direction) {
			case 'R':
				p_camera->UpdateCamera(1000, 0);
				DoorTransition = true;
				this->audioPlayer->PlaySound(AudioPlayer::roomChange, -1, 0);;
				break;
			case 'L':
				p_camera->UpdateCamera(-1000, 0);
				DoorTransition = true;
				this->audioPlayer->PlaySound(AudioPlayer::roomChange, -1, 0);
				break;
			case 'D':
				p_camera->UpdateCamera(0, 600);
				DoorTransition = true;
				this->audioPlayer->PlaySound(AudioPlayer::roomChange, -1, 0);
				break;
			case 'U':
				p_camera->UpdateCamera(0, -600);
				DoorTransition = true;
				this->audioPlayer->PlaySound(AudioPlayer::roomChange, -1, 0);
				break;
			}			
		}
		//update camera
		break;
	case Exit:
		canMove = true;
		HasWon = true;
		break;
	default:
		canMove = true;
		DoorTransition = false;
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
	if (insanityAmount > 75)
		GoSaneAgain();
	this->canistersCollected++;
	std::cout << "canister collected" << std::endl;
}
void Player::GoSaneAgain()
{
	this->insane = false;
	std::cout << "Sane again" << std::endl;
}
void Player::DecreaseSanity()
{
	this->insanityAmount -= 1;
	if (this->insanityAmount < 75)
	{
		if (this->insane == false)
			this->GoInsane();
	}
	//std::cout << this->insanityAmount << std::endl;
}

void Player::GoInsane()
{
	this->insane = true;
	std::cout << "You have gone insane" << std::endl;
}


void Player::draw()
{
	p_drawRect = { p_positionDest.x - p_camera->GetCamera().x, p_positionDest.y - p_camera->GetCamera().y, p_positionDest.w, p_positionDest.h };
	//draw player pos
	SDL_RenderCopy(this->p_renderer, this->p_texture, &p_positionSrc, &p_drawRect);
	drawUI();
}

void Player::drawUI()
{
}

bool Player::checkCollision(SDL_Rect other, GasCanister* canister)
{
	
	if (SDL_HasIntersection(&this->p_positionDest, &other) && canister->getIsFull()) {
		canister->setIsFull(false);
		this->audioPlayer->PlaySound(AudioPlayer::inhale, -1, 0);
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
