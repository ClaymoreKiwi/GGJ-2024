#pragma once
#include <SDL.h>

class deltaTime
{
public:

	deltaTime();

	inline void Update()
	{
		unsigned int currentFrameTime = SDL_GetTicks();
		dTime = (currentFrameTime - lastFrameTime) / 1000.0f; // Convert to seconds
		lastFrameTime = currentFrameTime;
	}

	inline float GetDeltaTime() const
	{
		return dTime;
	}
private:
	float		 dTime = 0;
	unsigned int lastFrameTime = 0;
};

