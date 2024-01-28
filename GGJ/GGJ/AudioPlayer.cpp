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
	Mix_Chunk* sound1 = Mix_LoadWAV("./content/sounds/HissingGas.wav");
	soundFiles.push_back(sound1);
	Mix_Chunk* sound2 = Mix_LoadWAV("./content/sounds/L6.wav");
	soundFiles.push_back(sound2);
	Mix_Chunk* sound3 = Mix_LoadWAV("./content/sounds/Exit.wav");
	soundFiles.push_back(sound3);
	Mix_Chunk* sound4 = Mix_LoadWAV("./content/sounds/ChannelChange.wav");
	soundFiles.push_back(sound4);
	Mix_Chunk* sound5 = Mix_LoadWAV("./content/sounds/Footstep.wav");
	soundFiles.push_back(sound5);

	//set the volume of the sound files
	for (int i = 0; i < soundFiles.size(); ++i)
	{
		soundFiles[i]->volume = 50;
	}
}

int AudioPlayer::PlaySound(int sound, int audioChannel, int looping)
{
	int channelGroup = audioChannel;
	if (sound == inhale) {
		channelGroup = Mix_GroupAvailable(-1);
		Mix_Volume(channelGroup, 50);
		return Mix_PlayChannel(channelGroup, soundFiles[sound], looping);
	}
	return Mix_PlayChannel(audioChannel, soundFiles[sound], looping);
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

void AudioPlayer::Stop(int channel)
{
	Mix_HaltChannel(channel);
}

void AudioPlayer::SetVolume(int channel, float volume)
{
	Mix_Volume(channel, volume);
}
