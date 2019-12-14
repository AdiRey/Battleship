#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "GameState.h"
#include "Subtitle.h"
#include "Ship.h"
#include "Button.h"
#include "User.h"
#include "TextField.h"
#include "DEFINITIONS.h"
#include "State.h"
#include "EventManager.h"

class InitState : public State
{
private:
	Soundtrack* soundtrack;

	sf::RenderWindow* window;
	EventManager manager;

	User* players[2];

	Button* button;

	Subtitle* setShipsSubtitle;
	bool showWrongSubtitle{ false };

	Subtitle* playerName;

	RectangleShape tableForShips;

	Board* board;

	int allShip1{ 0 };
	int allShip2{ 0 };

	Ship* shipsOne[10];
	Ship* shipsTwo[10];

	bool isClickNext{ true };
	int whichUser{ 0 };

	// Private methods
	bool rightSetShip(int i) const;
	bool isAllSet();
	bool clickNext(Vector2f& posistion, Event& event);
public:
	// Constructor and destructor
	InitState();
	virtual ~InitState();

	// Public methods
	User** getUsers();

	// Inheritance
	void handleInput() override;
	void init(sf::RenderWindow* window) override;
	void initMusic(Soundtrack* soundtrack) override;
	void draw(RenderTarget& target, RenderStates states) const override;
};

