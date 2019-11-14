#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
using namespace sf;

class Ship
{
private:
	int length;
	int width{ 1 };
	const Texture texture;

	int fieldToShoot{ 0 };

	RectangleShape ship;
	RectangleShape aroundShip;

	Vector2f areaSize;
	Vector2f shipSize;

	bool isMove{ false };
	bool isRotate{ false };
	bool isOk;
	bool isShow{ false };

	bool isSet{ false };

	float dx{};
	float dy{};

	Vector2f mainLocation;
	float mainRotation;

	Vector2f previousLocation;
	float previousRotation;

	bool checkIf(Board& board) const;
public:
	// Constructors and destructor
	Ship() = delete;
	Ship(int length, float x, float y, int counter = 0, int origin = 15);
	virtual ~Ship() = default;

	// Methods
	void update(Vector2f& pos, Event& event, Board& board);
	RectangleShape getShip() const;
	RectangleShape getAroundShip() const;
	void correctShip(bool isCorrect);
	void setPositionForUser();
	void shipRotate(bool isRotateCorrect);
	void setAdditionalPositionOfShip(float x, float y);

	void addFieldToShoot();
	void subtractFieldToShoot();
	int getFieldToShoot();

	bool getShipIsSetOrNot();
	void setShow(bool isShow);
	bool getShow() const;

	// Print
	void render(RenderTarget& target) const;
};