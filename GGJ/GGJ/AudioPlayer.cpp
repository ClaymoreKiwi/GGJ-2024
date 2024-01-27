#include "AudioPlayer.h"


AudioPlayer::AudioPlayer()
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
	{
		printf("audio mixer could not be created! SDL_Error %s\n", SDL_GetError());
	}
	//hard coded for now 
	Mix_Chunk* sound = Mix_LoadWAV("./content/sounds/Inhale.wav");
	soundFiles.push_back(sound);

	//set the volume of the sound files
	for (int i = 0; i < soundFiles.size(); ++i)
	{
		soundFiles[i]->volume = 50;
	}
}

void AudioPlayer::PlaySound(int sound)
{
	Mix_PlayChannel(-1, soundFiles[sound], 0);
}

void AudioPlayer::TrackSelect(const char* path)
{
	//small memory management for clearing old music out and reloading new track
	if (musicPlayer != nullptr)
	{
		Mix_FreeMusic(musicPlayer);
	}

	musicPlayer = Mix_LoadMUS(path);
	if (musicPlayer == NULL)
	{
		printf("Music track not loaded: SDL_Error %s\n", SDL_GetError());
	}
	Mix_VolumeMusic(15);
	Mix_PlayMusic(musicPlayer, -1);
}
