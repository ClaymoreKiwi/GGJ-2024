#include "MainMenu.h"
#include "StateMachine.h"

MainMenu::MainMenu(SDL_Renderer* r,const int& screenW, const int& screenH)
	:m_renderer(r), screenWidth(screenW), screenHeight(screenH)
{}

int MainMenu::init()
{
	//start game button
	startGame = new Button(this->m_renderer, "content/buttons/buttons.png", screenWidth, screenHeight);
	exitGame = new Button(this->m_renderer, "content/buttons/buttons.png", screenWidth, screenHeight);

	startGame->init();
	exitGame->init();

	return 0;
}

void MainMenu::update()
{
	SDL_RenderClear(m_renderer);
	draw();
	SDL_RenderPresent(m_renderer);
}

void MainMenu::draw()
{
	int green[4] = {16,74,21,255}; //specified green for the font
	startGame->draw("Play", screenWidth / 2, screenHeight / 2);
	exitGame->draw("Exit", screenWidth / 2, ((screenHeight / 2) + 100));
}

bool MainMenu::processInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			m_state = 5;
			return false; //break out of loop and switch the case exit
		}
		if (startGame->processInput(e))
		{
			//SDL_Delay(300);
			m_state = 1;
			return false; //break out the loop and switch the case to start
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

bool MainMenu::menuRunning()
{
	return processInput();
}

void MainMenu::clean()
{
	if (startGame)
	{
		startGame->clean();
		delete startGame;
		startGame = nullptr;
	}
	if (exitGame)
	{
		exitGame->clean();
		delete exitGame;
		exitGame = nullptr;
	}

}

int MainMenu::menuStateUpdate()
{
	return m_state;
}
