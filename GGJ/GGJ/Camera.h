#pragma once
#include <iostream>
#include <SDL.h>

class Camera
{
public:
	Camera(SDL_Rect& cam)
		:cam_camera(cam)
	{}
	inline void UpdateCamera(const int x, const int y)
	{
		cam_camera.x += x;
		cam_camera.y += y;
	};
	SDL_Rect GetCamera()
	{
		return cam_camera;
	}
	~Camera() {};
private:
	//bool isStop = false;
	SDL_Rect cam_camera = { 0,0,0,0 };
};

