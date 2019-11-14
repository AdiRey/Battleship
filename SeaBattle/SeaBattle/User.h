#pragma once
#include <SFML/Graphics.hpp>
#include  "Ship.h"

class User
{
private:
	std::string name;
	Ship* shipsy[10];
	bool isWinner{ false };

public:
	//Constructors and destructor
	User() = delete;
	User(std::string name);
	~User() = default;

	// Methods
	void setShips(Ship** ships);
	RectangleShape getShipRect(int which) const;
	Ship* getShip(int which);
	Ship** getAllShips();

	void setWinner(bool isWinner);
	bool getWinner() const;
};