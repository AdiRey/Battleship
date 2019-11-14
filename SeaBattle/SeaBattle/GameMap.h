#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Board.h"
#include "User.h"
#include "Field.h"
#include "Button.h"
#include "Subtitle.h"
#include "Ship.h"

class GameMap : public Drawable
{
private:
	Sprite sprite;
	Texture texture;

	Texture textureToPointer;
	Sprite pointer;

	Button* button; // to go next when someone wins
	Font font; // same as above

	User* players[2];

	Subtitle* playerOneName;
	Subtitle* playerTwoName;

	int currentPlayerMove{ 0 };

	float x1a = 195.f, x2a = 705.f, y1a = 135.f, y2a = 135.f;
	float x1b = 195.f, x2b = 705.f, y1b = 135.f, y2b = 135.f;

	Board* boards[2];

	Field* fieldsOne[10][10];
	Field* fieldsTwo[10][10];

	Ship** shipsOne;
	Ship** shipsTwo;

	bool allShipsDown();

public:
	//Constructor and destructor
	GameMap();
	~GameMap() = default;

	// Methods
	bool update(Vector2f& pos, Event& event);
	void initSets(User** users);

	//Print
	void draw(RenderTarget& target, RenderStates states) const override;
};