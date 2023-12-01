#include "SoundEffects.h"

SoundEffects::SoundEffects()
{
	startOfGameSoundEffect.path = assetsPath.concatenate("sounds\\startSound.wav");
	captureSoundEffect.path = assetsPath.concatenate("sounds\\captureSound.wav");
	checkSoundEffect.path = assetsPath.concatenate("sounds\\checkSound.wav");
	endOfGameSoundEffect.path = assetsPath.concatenate("sounds\\endOfGameSound.wav");
	castlingSoundEffect.path = assetsPath.concatenate("sounds\\castlingSound.wav");
	placingSoundEffect.path = assetsPath.concatenate("sounds\\placingSound.wav");

	startOfGameSoundEffect.buff.loadFromFile(startOfGameSoundEffect.path);
	captureSoundEffect.buff.loadFromFile(captureSoundEffect.path);
	checkSoundEffect.buff.loadFromFile(checkSoundEffect.path);
	endOfGameSoundEffect.buff.loadFromFile(endOfGameSoundEffect.path);
	castlingSoundEffect.buff.loadFromFile(castlingSoundEffect.path);
	placingSoundEffect.buff.loadFromFile(placingSoundEffect.path);

	startOfGameSoundEffect.s.setBuffer(startOfGameSoundEffect.buff);
	captureSoundEffect.s.setBuffer(captureSoundEffect.buff);
	checkSoundEffect.s.setBuffer(checkSoundEffect.buff);
	endOfGameSoundEffect.s.setBuffer(endOfGameSoundEffect.buff);
	castlingSoundEffect.s.setBuffer(castlingSoundEffect.buff);
	placingSoundEffect.s.setBuffer(placingSoundEffect.buff);
}


void SoundEffects::playCaptureSoundEffect()
{
	captureSoundEffect.s.play();
}
void SoundEffects::playCheckSoundEffect()
{
	checkSoundEffect.s.play();
}
void SoundEffects::playEndOfGameSoundEffect()
{
	endOfGameSoundEffect.s.play();
}
void SoundEffects::playStartOfGameSoundEffect()
{
	startOfGameSoundEffect.s.play();
}
void SoundEffects::playCastlingSoundEffect()
{
	castlingSoundEffect.s.play();
}
void SoundEffects::playPlacingSoundEffect()
{
	placingSoundEffect.s.play();
}