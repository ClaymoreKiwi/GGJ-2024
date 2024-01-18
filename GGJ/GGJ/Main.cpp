#define SDL_MAIN_HANDLED
#include "StateMachine.h"

int main()
{
	StateMachine* StartGame = new StateMachine();
	StartGame->updateState();
	return 0;
}