#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "EventManager.h"
#include "DEFINITIONS.h"
#include "SpriteClicker.h"
class ChoiceState : public State
{
private:

	SpriteClicker* spriteClicker[2];
	SpriteClicker* spriteClicker2[2];
	SpriteClicker* spriteClicker3[2];

	sf::RenderWindow* window;
	EventManager manager;
public:
	ChoiceState();
	virtual ~ChoiceState();
	void init(sf::RenderWindow* window) override;
	void handleInput() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

