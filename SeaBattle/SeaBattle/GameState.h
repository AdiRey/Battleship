#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include <Windows.h>
#include "Board.h"
#include "User.h"
#include "Field.h"
#include "Button.h"
#include "Subtitle.h"
#include "Ship.h"
#include "EventManager.h"
#include "DEFINITIONS.h"
class GameState : public State
{
private:
	sf::RenderWindow* window;
	EventManager manager;

	Texture textureToPointer;
	Sprite pointer;

	User* player[2];
	Ship** shipsOne;
	Ship** shipsTwo;

	Subtitle* playerOneName;
	Subtitle* playerTwoName;

	int currentPlayerMove{ 0 };

	// Coord Boards
	float x1a = 195.f, x2a = 705.f, y1a = 135.f, y2a = 135.f;
	float x1b = 195.f, x2b = 705.f, y1b = 135.f, y2b = 135.f;
	Board* boards[2];

	Field* fieldsOne[10][10];
	Field* fieldsTwo[10][10];


	void allShipsDown();

public:
	//Constructor and destructor
	GameState();
	virtual ~GameState();

	// Methods
	void initSets(User** users);

	// Inheritance
	void handleInput() override;
	void init(sf::RenderWindow* window) override;
	void draw(RenderTarget& target, RenderStates states) const override;
};

