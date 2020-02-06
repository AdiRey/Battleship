#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Button.h"
#include "DEFINITIONS.h"
#include "EventManager.h"
class StartState : public State
{
private:
	Soundtrack* soundtrack;

	sf::RenderWindow* window;
	EventManager manager;

	Button* startButton;
	Button* settingsButton;
	Button* exitButton;
public:
	StartState();
	virtual ~StartState();
	void handleInput() override;
	void init(sf::RenderWindow* window) override;
	void initMusic(Soundtrack* soundtrack) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

