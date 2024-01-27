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

		//stop camera from going too far left
		if (cam_camera.x < 0)
			cam_camera.x = 0;
		//stop camera from going too far up
		if (cam_camera.y < 0)
			cam_camera.y = 0;
		//stop camera from going too far right
		if (cam_camera.x > ((1000 / 10) * 40) - 1000)
			cam_camera.x = ((1000 / 10) * 40) - 1000;
		//stop camera from going too far down
		if (cam_camera.y > ((600 / 10) * 20) - 600)
			cam_camera.y = ((600 / 10) * 20) - 600;
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

