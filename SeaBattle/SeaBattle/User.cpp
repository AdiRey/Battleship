#include "User.h"

User::User(std::string name)
{
	this->name = name;
}

User::~User()
{
	//TODO
}

void User::setShips(Ship** ships)
{
	for (int i = 0; i < 10; i++)
	{
		this->ships[i] = ships[i];
	}
}

RectangleShape User::getShipRect(int which) const
{
	return this->ships[which]->getShip();
}

Ship* User::getShip(int which)
{
	return this->ships[which];
}

void User::setWinner(bool isWinner)
{
	this->isWinner = isWinner;
}

bool User::getWinner() const
{
	return this->isWinner;
}

Ship** User::getAllShips()
{
	return this->ships;
}
