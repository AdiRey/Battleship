#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "DEFINITIONS.h"
#include "Button.h"
#include "EventManager.h"
#include "Subtitle.h"

class SettingsState : public State
{
private:
	Soundtrack* soundtrack;

	sf::RenderWindow* window;
	EventManager manager;

	AppStates previous;

	Button* resumeButton;
	Button* volumeButton;
	Button* exitButton;

public:
	SettingsState();
	virtual ~SettingsState();
	void setPreviousState(AppStates previous);
	void handleInput() override;
	void init(sf::RenderWindow* window) override;
	void initMusic(Soundtrack* soundtrack) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

