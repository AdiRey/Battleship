#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Subtitle.h"
#include "Ship.h"
#include "Button.h"
#include "User.h"
#include "TextField.h"

using namespace sf;

class InitMap : public Drawable
{
private:
	Sprite sprite;
	Texture texture;

	//TextField textField{20};

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
	InitMap();
	virtual ~InitMap();

	bool update(Vector2f& pos, Event& event);
	bool clickNext(Vector2f& pos, Event& event);
	User** getUsers();

	void draw(RenderTarget& target, RenderStates states) const override;
};