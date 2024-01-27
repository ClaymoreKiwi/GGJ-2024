#pragma once
#include <SDL_mixer.h>
#include <sstream>
#include <vector>

class AudioPlayer
{
public:
	AudioPlayer();
	virtual ~AudioPlayer()
	{
		for (auto& sound : soundFiles)
		{
			Mix_FreeChunk(sound);
		}
		if (musicPlayer != nullptr)
		{
			Mix_FreeMusic(musicPlayer);
		}
		Mix_CloseAudio();
	}

	void PlaySound(int sound);
	void TrackSelect(const char* path);

private:
	Mix_Music* musicPlayer = nullptr;
	std::vector<Mix_Chunk*> soundFiles;

public:
	enum Sounds 
	{
		button_hover_sound,
		button_select_sound,
		swing_club,
		score_ball,
		ball_hit,
		TOTAL_sounds,
	};
};
