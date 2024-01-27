#include "AudioPlayer.h"


AudioPlayer::AudioPlayer()
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
	{
		printf("audio mixer could not be created! SDL_Error %s\n", SDL_GetError());
	}
	//hard coded for now 
	Mix_Chunk* sound = Mix_LoadWAV("./content/sounds/button_hover_sound.wav");
	soundFiles.push_back(sound);
	Mix_Chunk* sound2 = Mix_LoadWAV("./content/sounds/button_select_sound.wav");
	soundFiles.push_back(sound2);
	Mix_Chunk* sound3 = Mix_LoadWAV("./content/sounds/swing_club.wav");
	soundFiles.push_back(sound3);
	Mix_Chunk* sound4 = Mix_LoadWAV("./content/sounds/score_ball.wav");
	soundFiles.push_back(sound4);
	Mix_Chunk* sound5 = Mix_LoadWAV("./content/sounds/ball_hit.wav");
	soundFiles.push_back(sound5);

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
