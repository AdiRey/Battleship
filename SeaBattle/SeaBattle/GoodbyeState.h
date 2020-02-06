#pragma once
#include "State.h"
#include "DEFINITIONS.h"
#include "Subtitle.h"
#include "Button.h"
#include "EventManager.h"

class GoodbyeState : public State
{
private:
	Soundtrack* soundtrack;

	AppStates previous;

	sf::RenderWindow* window;

	EventManager manager;
	Subtitle* endText;
	Button* backExit;
	Button* confirmExit;
public:
	GoodbyeState();
	virtual ~GoodbyeState();

	void handleInput() override;
	void init(sf::RenderWindow* window) override;
	void initMusic(Soundtrack* soundtrack) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setPreviousState(AppStates previous);
};
