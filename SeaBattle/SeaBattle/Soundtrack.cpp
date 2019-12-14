#include "Soundtrack.h"

Soundtrack::Soundtrack()
{
	this->bufferOne.loadFromFile("music/Click2-Sebastian-759472264.ogg");
	this->bufferTwo.loadFromFile("music/Click-On-SoundBible.com-1697535117.ogg");
	this->soundHov.setBuffer(bufferOne);
	this->soundClicked.setBuffer(bufferTwo);

	this->soundHov.setLoop(false);
	this->soundClicked.setLoop(false);

	this->music.openFromFile("music/Battleship-_OST_-1-First-Transmission.ogg");
	this->music.setLoop(true);
	this->music.play();
}

Soundtrack::~Soundtrack()
{
}

void Soundtrack::setEffectVolume(float volume)
{
	this->soundHov.setVolume(volume);
	this->soundClicked.setVolume(volume);
}

void Soundtrack::setGameVolume(float volume)
{
	this->music.setVolume(volume);
}

sf::Sound& Soundtrack::getSoundHov()
{
	return this->soundHov;
}
sf::Sound& Soundtrack::getSoundClicked()
{
	return this->soundClicked;
}

sf::Music& Soundtrack::getMusic()
{
	return this->music;
}