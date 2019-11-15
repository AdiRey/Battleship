#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Subtitle.h"
#include "Ship.h"
#include "Button.h"
#include "User.h"
#include "TextField.h"
#include "DEFINITIONS.h"
#include "State.h"

class InitState : public State
{
private:
	sf::RenderWindow* window;


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

	bool rightSetShip(int i) const;
	bool isAllSet();
public:
	InitState();
	virtual ~InitState();

	bool update(Vector2f& pos, Event& event);
	bool clickNext(Vector2f& pos, Event& event);
	User** getUsers();

	void init(sf::RenderWindow* window) override;
	void handleInput() override;

	void draw(RenderTarget& target, RenderStates states) const override;
};

