#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Button.h"
#include "Subtitle.h"
#include "User.h"
#include "EventManager.h"
#include "DEFINITIONS.h"
class EndState : public State
{
private:
	Soundtrack* soundtrack;

	sf::RenderWindow* window;
	EventManager manager;

	Subtitle* subtitle;
	Button* oneMoreTimeButton;
	Button* exitButton;
	std::string winner;
public:
	// Constructor and destructor
	EndState();
	virtual ~EndState();

	void handleInput() override;
	void init(sf::RenderWindow* window) override;
	void initMusic(Soundtrack* soundtrack) override;
	void draw(RenderTarget& target, RenderStates states) const override;

	// Methods
	void initSets(User** users);
};

