#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "DEFINITIONS.h"
#include "Button.h"
#include "EventManager.h"
class SettingsState : public State
{
private:
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
	void init(sf::RenderWindow* window) override;
	void handleInput() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

