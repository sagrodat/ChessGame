#pragma once
#include "SFML/Audio.hpp"
#include "AssetsPath.h"
class SoundEffects
{
public :
	SoundEffects();
private :
	typedef struct SoundEffect {
		sf::SoundBuffer buff;
		sf::Sound s;
		std::string path;
	}soundEffect_t;

	soundEffect_t startOfGameSoundEffect;
	soundEffect_t captureSoundEffect;
	soundEffect_t checkSoundEffect;
	soundEffect_t endOfGameSoundEffect;
	soundEffect_t castlingSoundEffect;
	soundEffect_t placingSoundEffect;

public :
	void playCaptureSoundEffect();
	void playCheckSoundEffect();
	void playEndOfGameSoundEffect();
	void playCastlingSoundEffect();
	void playPlacingSoundEffect();
	void playStartOfGameSoundEffect();
};