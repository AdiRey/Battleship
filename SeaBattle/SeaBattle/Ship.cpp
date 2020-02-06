#include "Ship.h"
using namespace std;

Ship::Ship(int length, float x, float y, int counter, int origin)
{
	this->length = length;
	{
		std::string fileName = "images/ship" + std::to_string(length) + ".png";
		const_cast<Texture&>(texture).loadFromFile(fileName);
		ship.setSize(sf::Vector2f(30 * this->length, 30 * width));

		areaSize = Vector2f(30 * (length + 2), 90);
		shipSize = Vector2f(30 * length, 30);

		aroundShip.setSize(areaSize);
		ship.setTexture(&texture);
	}
	previousLocation = mainLocation = Vector2f(x, y + counter * 30);

	ship.setPosition(mainLocation);
	aroundShip.setPosition(mainLocation);
	previousRotation = mainRotation = ship.getRotation();

	ship.setOrigin(origin, origin);
	aroundShip.setOrigin(3 * origin, 3 * origin);
}

void Ship::update(Vector2f& pos, Event& event, Board& board)
{
	if (ship.getGlobalBounds().contains(pos))
	{
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				isMove = true;
				dx = pos.x - ship.getPosition().x;
				dy = pos.y - ship.getPosition().y;
			}
			if (event.mouseButton.button == Mouse::Right)
			{
				if (isRotate)
				{
					isOk = !(ship.getPosition() == mainLocation);
					if (isOk)
					{
						ship.rotate(90);
						aroundShip.rotate(90);
					}
					while (checkIf(board))
					{
						if (!isOk) break;
						ship.rotate(90);
						aroundShip.rotate(90);
					}
					isRotate = false;
					previousRotation = ship.getRotation();
					throw range_error("Enable rotation through the ships");
				}
			}
		}
		else if (event.type == Event::MouseButtonReleased)
		{
			isMove = false;
			isRotate = true;
			Vector2f p = ship.getPosition() + Vector2f(15, 15);
			Vector2f newPos = Vector2f(30 * int(p.x / 30), 30 * int(p.y / 30));
			ship.setPosition(newPos);
			aroundShip.setPosition(newPos);

			if (checkIf(board))
			{
				ship.setRotation(mainRotation);
				ship.setPosition(mainLocation);
				aroundShip.setPosition(mainLocation);
				aroundShip.setRotation(mainRotation);
			}
			else throw invalid_argument("Check valid");
		}
	}

	if (isMove)
	{
		ship.setPosition(pos.x - dx, pos.y - dy);
		aroundShip.setPosition(pos.x - dx, pos.y - dy);
	}
}


bool Ship::checkIf(Board& board) const
{
	return (board.getBoard().getGlobalBounds().left > ship.getGlobalBounds().left) ||
		(board.getBoard().getGlobalBounds().top > ship.getGlobalBounds().top) ||
		((board.getBoard().getGlobalBounds().top + board.getBoard().getGlobalBounds().height) <
		(ship.getGlobalBounds().top + ship.getGlobalBounds().height)) ||
			((board.getBoard().getGlobalBounds().left + board.getBoard().getGlobalBounds().width) <
		(ship.getGlobalBounds().left + ship.getGlobalBounds().width));
}

RectangleShape Ship::getShip() const
{
	return this->ship;
}

RectangleShape Ship::getAroundShip() const
{
	return this->aroundShip;
}

void Ship::correctShip(bool isCorrect)
{
	if (isCorrect)
	{
		ship.setPosition(previousLocation);
		aroundShip.setPosition(previousLocation);

		ship.setRotation(previousRotation);
		aroundShip.setRotation(previousRotation);
	}
	else
	{
		previousLocation = ship.getPosition();
		previousRotation = ship.getRotation();
	}
}

void Ship::setPositionForUser()
{
	this->ship.setPosition(mainLocation);
	this->aroundShip.setPosition(mainLocation);

	this->ship.setRotation(mainRotation);
	this->aroundShip.setRotation(mainRotation);

	previousLocation = mainLocation;
	previousRotation = mainRotation;
}

void Ship::shipRotate(bool isRotateCorrect)
{
	if (isRotateCorrect)
	{
		ship.rotate(90);
		aroundShip.rotate(90);
		previousRotation = ship.getRotation();
	}
}

void Ship::setAdditionalPositionOfShip(float x, float y)
{
	ship.setPosition(previousLocation.x + x, previousLocation.y + y);
	aroundShip.setPosition(previousLocation.x + x, previousLocation.y + y);
}

void Ship::addFieldToShoot()
{
	this->fieldToShoot++;
}

void Ship::subtractFieldToShoot()
{
	this->fieldToShoot--;
}


int Ship::getFieldToShoot()
{
	return this->fieldToShoot;
}

void Ship::setShow(bool isShow)
{
	this->isShow = isShow;
}

bool Ship::getShow() const
{
	return this->isShow;
}

bool Ship::getShipIsSetOrNot()
{
	if (this->ship.getPosition() != this->mainLocation)
		return true;
	else
		return false;
}

void Ship::render(RenderTarget& target) const
{
	//target.draw(this->aroundShip);
	target.draw(this->ship);
}