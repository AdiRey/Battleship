#pragma once
#include <SFML/Audio.hpp>
class Soundtrack
{
private:
	sf::SoundBuffer bufferOne;
	sf::SoundBuffer bufferTwo;
	sf::Sound soundHov;
	sf::Sound soundClicked;
	sf::Music music;
public:
	Soundtrack();
	~Soundtrack();

	void setEffectVolume(float volume);
	void setGameVolume(float volume);

	sf::Sound& getSoundHov();
	sf::Sound& getSoundClicked();
	sf::Music& getMusic();
};

