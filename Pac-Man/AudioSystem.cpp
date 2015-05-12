#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
	channel = 0;
	extradriverdata = 0;
	m_Initialized = false;

	for (int i = 0; i < GAME_SOUND_NUM; i++)
	{
		sounds[i] = 0;
	}
}

bool AudioSystem::Init()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&fmod_system);
	if (result != FMOD_OK)
		return false;

	result = fmod_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	if (result != FMOD_OK)
	{
		fmod_system->close();
		fmod_system->release();
		return false;
	}

	m_Initialized = true;

	fmod_system->createSound("Sounds/pacman_song1.wav", FMOD_DEFAULT, 0, &sounds[GAME_SOUND_BEGINNING]);
	fmod_system->createSound("Sounds/pacman_getghost.wav", FMOD_DEFAULT, 0, &sounds[GAME_SOUND_EATGHOST]);
	fmod_system->createSound("Sounds/pacman_eatfruit.wav", FMOD_DEFAULT, 0, &sounds[GAME_SOUND_EATFRUIT]);
	fmod_system->createSound("Sounds/pacman_coinin.wav", FMOD_DEFAULT, 0, &sounds[GAME_SOUND_COININ]);
	fmod_system->createSound("Sounds/pacman_death.wav", FMOD_DEFAULT, 0, &sounds[GAME_SOUND_DEATH]);
	fmod_system->createSound("Sounds/pacman_song2.wav", FMOD_DEFAULT, 0, &sounds[GAME_SOUND_INTERMISSION]);

	return true;
}

void AudioSystem::Destroy()
{
	if (m_Initialized)
	{
		for (int i = 0; i < GAME_SOUND_NUM; i++)
		{
			if (sounds[i])
			{
				sounds[i]->release();
				sounds[i] = 0;
			}
		}
		fmod_system->close();
		fmod_system->release();

		m_Initialized = false;
	}
}

void AudioSystem::Play(GameSound sound_name)
{
	if (sounds[sound_name])
	{
		if (sound_name == GAME_SOUND_COININ)
		{
			bool playing;
			channel->isPlaying(&playing);
			if (channel && !playing)
				fmod_system->playSound(sounds[sound_name], 0, false, &channel);
		}
		else
			fmod_system->playSound(sounds[sound_name], 0, false, &channel);
	}
}
