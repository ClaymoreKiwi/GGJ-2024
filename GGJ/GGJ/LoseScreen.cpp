#include "LoseScreen.h"
#include "StateMachine.h"

int LoseScreen::init()
{
	//title card
	fontRenderer = std::unique_ptr<FontRendering>(new FontRendering(ls_renderer, screenWidth, screenHeight));
	ls_audioPlayer = new AudioPlayer();
	//start game button
	mainMenu = new Button(this->ls_renderer, "content/buttons/buttons.png", screenWidth, screenHeight);
	retry = new Button(this->ls_renderer, "content/buttons/buttons.png", screenWidth, screenHeight);
	exitGame = new Button(this->ls_renderer, "content/buttons/buttons.png", screenWidth, screenHeight);

	mainMenu->init();
	retry->init();
	exitGame->init();

	ls_audioPlayer->TrackSelect("./content/sounds/EndGame_lose.wav");
	return 0;
}

void LoseScreen::update()
{
	SDL_RenderClear(ls_renderer);
	draw();
	SDL_RenderPresent(ls_renderer);
}

void LoseScreen::draw()
{
	int black[4] = { 255,255,255,255 }; //specified green for the font
	fontRenderer->draw("You Lose", screenWidth / 2, screenHeight / 4, 600, 150, black);
	mainMenu->draw("Main Menu", screenWidth / 2, screenHeight / 2);
	retry->draw("Retry", screenWidth / 2, (screenHeight / 2) + 100);
	exitGame->draw("Exit", screenWidth / 2, ((screenHeight / 2) + 200));
}

bool LoseScreen::processInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			m_state = 5;
			return false; //break out of loop and switch the case exit
		}
		if (mainMenu->processInput(e))
		{
			m_state = 0;
			return false; //break out the loop and switch the case to start
		}
		if (retry->processInput(e))
		{
			//just to listen to the button sound
			SDL_Delay(500);
			m_state = 1;
			return false; //break out of loop and switch the case exit
		}
		if (exitGame->processInput(e))
		{
			//just to listen to the button sound
			SDL_Delay(500);
			m_state = 5;
			return false; //break out of loop and switch the case exit
		}

	}
	return true;
}

bool LoseScreen::LoseScreenRunning()
{
    return processInput();
}

void LoseScreen::clean()
{
	fontRenderer->clean();
	if (mainMenu)
	{
		mainMenu->clean();
		delete mainMenu;
		mainMenu = nullptr;
	}
	if (retry)
	{
		retry->clean();
		delete retry;
		retry = nullptr;
	}
	if (exitGame)
	{
		exitGame->clean();
		delete exitGame;
		exitGame = nullptr;
	}
	if (ls_audioPlayer)
	{
		delete ls_audioPlayer;
		ls_audioPlayer = nullptr;
	}
}

int LoseScreen::LoseScreenStateUpdate()
{
	return m_state;
}
