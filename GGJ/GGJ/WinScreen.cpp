#include "WinScreen.h"
#include "StateMachine.h"

int WinScreen::init()
{
	//title card
	fontRenderer = std::unique_ptr<FontRendering>(new FontRendering(ws_renderer, screenWidth, screenHeight));
	ws_audioPlayer = new AudioPlayer();
	//start game button
	mainMenu = new Button(this->ws_renderer, "content/buttons/buttons.png", screenWidth, screenHeight);
	retry = new Button(this->ws_renderer, "content/buttons/buttons.png", screenWidth, screenHeight);
	exitGame = new Button(this->ws_renderer, "content/buttons/buttons.png", screenWidth, screenHeight);

	mainMenu->init();
	retry->init();
	exitGame->init();

	ws_audioPlayer->TrackSelect("./content/sounds/EndGame_win.wav");

	std::fstream file("./content/data/data.bin", std::ios::binary | std::ios::in);

	if (file.is_open()) {
		// Read the binary data
		file.read(reinterpret_cast<char*>(&ws_score), sizeof(int));

		// Check if reading was successful
		if (!file) {
			std::cerr << "Error reading data from file." << std::endl;
			file.close();
		}

		file.close();
	}
	else {
		std::cerr << "Error opening the file for reading." << std::endl;
	}
	return 0;
}

void WinScreen::update()
{
	SDL_RenderClear(ws_renderer);
	draw();
	SDL_RenderPresent(ws_renderer);
}

void WinScreen::draw()
{
	int black[4] = { 255,255,255,255 }; //specified green for the font
	std::string score = "You Made It!";
	fontRenderer->draw(score, screenWidth / 2, screenHeight / 4, 600, 150, black);
	mainMenu->draw("Main Menu", screenWidth / 2, screenHeight / 2);
	retry->draw("Retry", screenWidth / 2, (screenHeight / 2) + 100);
	exitGame->draw("Exit", screenWidth / 2, ((screenHeight / 2) + 200));
}

bool WinScreen::processInput()
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

bool WinScreen::WinScreenRunning()
{
	return processInput();
}

void WinScreen::clean()
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
	if (ws_audioPlayer)
	{
		delete ws_audioPlayer;
		ws_audioPlayer = nullptr;
	}
}

int WinScreen::WinScreenStateUpdate()
{
	return m_state;
}
