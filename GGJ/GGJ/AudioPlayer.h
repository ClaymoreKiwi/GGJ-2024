#pragma once
#include <SDL_mixer.h>
#include <sstream>
#include <vector>
#include <SDL.h>

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

	void PlaySound(int sound, int audioChannel, int looping);
	void TrackSelect(const char* path);
	void Stop(int channel);
	void SetVolume(int channel, float volume);

private:
	Mix_Music* musicPlayer = nullptr;
	std::vector<Mix_Chunk*> soundFiles;

public:
	enum Sounds 
	{
		inhale,
		hiss
	};
};
