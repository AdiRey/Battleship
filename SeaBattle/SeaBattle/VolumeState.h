#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "State.h"
#include "Button.h"
#include "EventManager.h"
#include "Slider.h"
#include "Subtitle.h"

class VolumeState : public State
{
private:
	Soundtrack* soundtrack;

	float previousSound;
	float previousMusic;
	bool isCheck{ true };

	sf::RenderWindow* window;
	EventManager manager;

	Button* confirmButton;
	Button* backButton;

	Slider* gameSlider;
	Slider* effectSlider;

	Subtitle* gameSubtitle;
	Subtitle* effectSubtitle;

	RectangleShape table;

public:
	VolumeState();
	~VolumeState();

	void handleInput() override;
	void init(sf::RenderWindow* window) override;
	void initMusic(Soundtrack* soundtrack) override;
	void draw(RenderTarget& target, RenderStates states) const override;

	sf::Sound* getSoundHov();
	sf::Sound* getSoundClicked();
};

