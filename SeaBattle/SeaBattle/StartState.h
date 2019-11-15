#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Button.h"
#include "DEFINITIONS.h"
#include "EventManager.h"
class StartState : public State
{
private:
	sf::RenderWindow* window;
	EventManager manager;
	Button* startButton;
	Button* exitButton;
public:
	StartState();
	virtual ~StartState();
	void init(sf::RenderWindow* window) override;
	void handleInput() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

