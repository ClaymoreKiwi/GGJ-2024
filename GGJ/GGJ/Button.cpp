#include "Button.h"

Button::Button(SDL_Renderer* r, std::string fPath, const int& screenW, const int& screenH)
	:btn_renderer(r), btn_filePath(fPath), btn_screenWidth(screenW), btn_screenHeight(screenH)
{}

//private
int Button::init()
{
	btn_surface = IMG_Load(btn_filePath.c_str());
	if (btn_surface == NULL)
	{
		//if image could not be initalised throw error and stop program
		std::cerr << "could not initialize button image!\n";
		std::cerr << SDL_GetError() << std::endl;
		return 1;
	}
	this->btn_texture = SDL_CreateTextureFromSurface(this->btn_renderer, btn_surface);

	btn_positionSrc.x = 0;
	btn_positionSrc.y = 50;
	btn_positionSrc.w = 200;
	btn_positionSrc.h = 50;

	//this is the destination rect that is used on the screen instead of the source
	btn_positionDest.x = 0;
	btn_positionDest.y = 0;
	btn_positionDest.w = 200 * 2;
	btn_positionDest.h = 50 * 2;

	SDL_FreeSurface(btn_surface);

	fontRenderer = std::unique_ptr<FontRendering>(new FontRendering(btn_renderer, btn_positionDest.x, btn_positionDest.y));

	//audioPlayer = new AudioPlayer();
	return 0;
}

bool Button::processInput(SDL_Event e)
{
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	bool top = mousePos.y > btn_positionDest.y;
	bool bottom = mousePos.y < (btn_positionDest.y + btn_positionDest.h);
	bool left = mousePos.x > btn_positionDest.x;
	bool right = mousePos.x < (btn_positionDest.x + btn_positionDest.w);

	if (e.type == SDL_MOUSEBUTTONDOWN && hovered)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			clicked = true;
			return false;
		}
	}
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT && top && bottom && left && right)
		{
			clicked = false;
			return true;
		}
		clicked = false;
	}
	if (top && bottom && left && right)
	{
		playOnce = true;
		if (playOnce && !hovered)
		hovered = true;
		return false;
	}
	playOnce = false;
	hovered = false;
	return false;
}

void Button::draw(std::string text, const int& posX, const int& posY)
{
	int middleX = btn_positionDest.w / 2;
	int middleY = btn_positionDest.h / 2;
	btn_positionDest.x = posX - middleX;
	btn_positionDest.y = posY - middleY;
	if (!clicked && !hovered)
	{
		btn_positionSrc.y = 50;
		SDL_RenderCopy(this->btn_renderer, this->btn_texture, &btn_positionSrc, &btn_positionDest);
	}

	if (clicked)
	{
		btn_positionSrc.y = 100;
		SDL_RenderCopy(this->btn_renderer, this->btn_texture, &btn_positionSrc, &btn_positionDest);
	}
	if (hovered && !clicked)
	{
		btn_positionSrc.y = 0;
		SDL_RenderCopy(this->btn_renderer, this->btn_texture, &btn_positionSrc, &btn_positionDest);
	}

	int black[4] = { 0,0,0,255 };
	fontRenderer->draw(text, posX, posY, 90, 40, black);
}

void Button::clean()
{
	fontRenderer->clean();
	SDL_DestroyTexture(btn_texture);
}
