#include "./LaughterAtExit.h"

void LaughterAtExit::init()
{
	bool textureCreatedSucessfully = CreateTexture();
	if (!textureCreatedSucessfully)
		return;
	this->audioPlayer = new AudioPlayer();
	this->audioPlayer->PlaySound(AudioPlayer::exit, this->audioChannel, -1);
	this->audioPlayer->SetVolume(this->audioChannel, 128);
}

bool LaughterAtExit::CreateTexture()
{
	SDL_Surface* canisterSurface = IMG_Load("content/objects/entonox_can.png");
	if (canisterSurface == NULL)
	{
		//if image could not be initalised throw error and stop program
		std::cerr << "could not initialize picture!\n";
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	this->texture = SDL_CreateTextureFromSurface(this->renderer, canisterSurface);
	SDL_FreeSurface(canisterSurface);
	return true;
}

void LaughterAtExit::Render()
{
	OffsetObjectPositionUsingCameraPos();
	SDL_Point center{ this->destRect.x, this->destRect.y
	};

	SDL_RenderCopy(this->renderer, this->texture, NULL, &this->drawRect);
}

void LaughterAtExit::OffsetObjectPositionUsingCameraPos()
{
	this->drawRect = { this->destRect.x - this->camera->GetCamera().x, this->destRect.y - this->camera->GetCamera().y, this->destRect.w, this->destRect.h};
};

void LaughterAtExit::Update()
{
	float distanceToPlayerX = this->player->p_positionDest.x - this->destRect.x;
	float distanceToPlayerY = this->player->p_positionDest.y - this->destRect.y;

	float distanceSquared = (distanceToPlayerX * distanceToPlayerX) + (distanceToPlayerY * distanceToPlayerY);
	float distance = std::sqrt(distanceSquared);

	float finalVolume = 1000000 / distance * 0.1;
	if (finalVolume > 128) {
		finalVolume = 128;
	}
	this->audioPlayer->SetVolume(this->audioChannel, finalVolume);
}

void LaughterAtExit::setIsFull(bool value)
{
	this->isFull = value;
	if (value == false)
		this->audioPlayer->Stop(this->audioChannel);
}

bool LaughterAtExit::getIsFull()
{
	return this->isFull;
}

void LaughterAtExit::setPlayerRef(Player* player)
{
	this->player = player;
}

SDL_Rect LaughterAtExit::GetCanisterRect()
{
	return this->destRect;
}
