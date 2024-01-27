#pragma once
#include <SDL.h>

class Camera
{
public:
	Camera(SDL_Rect& cam)
		:cam_camera(cam)
	{}
	inline void UpdateCamera()
	{

	};
	~Camera() {};
private:
	SDL_Rect cam_camera = { 0,0,0,0 };
};

