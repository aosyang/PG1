#ifndef _AUDIOSYSTEM_H
#define _AUDIOSYSTEM_H

#include <fmod.hpp>

enum GameSound
{
	GAME_SOUND_BEGINNING,
	GAME_SOUND_EATGHOST,
	GAME_SOUND_EATFRUIT,
	GAME_SOUND_COININ,
	GAME_SOUND_DEATH,
	GAME_SOUND_INTERMISSION,

	GAME_SOUND_NUM
};

class AudioSystem
{
public:
	static AudioSystem* GetInstance()
	{
		static AudioSystem inst;
		return &inst;
	}

	bool Init();
	void Destroy();

	void Play(GameSound sound_name);
	bool IsPlaying(GameSound sound_name);

private:
	AudioSystem();
	FMOD::System	*fmod_system;
	FMOD::Sound		*sounds[GAME_SOUND_NUM];
	FMOD::Channel	*channel;
	void			*extradriverdata;
	bool			m_Initialized;
};

#endif
