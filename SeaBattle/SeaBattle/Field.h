#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"
using namespace sf;

enum FieldStates { FIELD_ID = 0, FIELD_HOV = 1, FIELD_ACTIVE = 2 };

class Field
{
private:
	int fieldState{ FIELD_ID };

	bool shutdown{ false };
	bool marked{ false };
	bool beOnce{ true };

	RectangleShape field;
	int value;
	bool isPrint;
public:
	//Constructors
	Field();
	Field(float x, float y, bool isPrint = false, float width = 30, float height = 30, int value = 0);
	~Field() = default;

	//Methods
	int update(Vector2f& pos, Event& event, Ship** ship);
	void setValue(int value);
	int getValue() const;
	void setMarked();
	void setPosition(float x, float y);
	RectangleShape getShape() const;

	//Print
	void render(RenderTarget& target) const;
};