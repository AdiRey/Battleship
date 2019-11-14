#include "GameMap.h"
#include <iostream>

GameMap::GameMap()
{
	texture.loadFromFile("images/statkiStart.png");
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	textureToPointer.loadFromFile("images/strzalka2.png");
	pointer.setTexture(textureToPointer);
	pointer.setPosition(595, 285);
	pointer.setOrigin(45, 45);

	playerOneName = new Subtitle("Player One", Vector2f(200, 60), Fonts::ARIAL, Color::White, 40, Text::Italic);
	playerTwoName = new Subtitle("Player Two", Vector2f(710, 60), Fonts::ARIAL, Color::White, 40, Text::Italic);

	playerOneName->setOutlines(Color::Black, 2);
	playerTwoName->setOutlines(Color::Black, 2);

	boards[0] = new Board(300, 300, x1a, y1a);
	boards[1] = new Board(300, 300, x2a, y2a);
}

bool GameMap::update(Vector2f& pos, Event& event)
{
	bool endLoops = false;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int x;
			if (currentPlayerMove == 0)
			{
				x = fieldsTwo[i][j]->update(pos, event, shipsTwo);
				if (x == 2)
				{
					players[0]->setWinner(allShipsDown());
				}
				else if (x == 1)
				{
					currentPlayerMove = 1;
					endLoops = true;
					this->pointer.rotate(180);
					break;
				}
			}
			else if (currentPlayerMove == 1)
			{
				x = fieldsOne[i][j]->update(pos, event, shipsOne);
				if (x == 2)
				{
					players[1]->setWinner(allShipsDown());
				}
				else if (x == 1)
				{
					currentPlayerMove = 0;
					endLoops = true;
					this->pointer.rotate(180);
					break;
				}
			}
		}
		if (endLoops)
			break;
	}

	if (players[0]->getWinner() || players[1]->getWinner())
		return true;

	for (int k = 0; k < 10; k++)
	{
		if (shipsOne[k]->getFieldToShoot() == 0)
		{
			shipsOne[k]->setShow(true);
			for (int x = 0; x < 10; x++)
			{
				for (int y = 0; y < 10; y++)
				{
					if (shipsOne[k]->getAroundShip().getGlobalBounds()
						.intersects(fieldsOne[x][y]->getShape().getGlobalBounds())
						&& !shipsOne[k]->getShip().getGlobalBounds().intersects(fieldsOne[x][y]->getShape().getGlobalBounds()))
					{
						fieldsOne[x][y]->setMarked();
					}
				}
			}
		}
	}
	for (int k = 0; k < 10; k++)
	{
		if (shipsTwo[k]->getFieldToShoot() == 0)
		{
			shipsTwo[k]->setShow(true);
			for (int x = 0; x < 10; x++)
			{
				for (int y = 0; y < 10; y++)
				{
					if (shipsTwo[k]->getAroundShip().getGlobalBounds()
						.intersects(fieldsTwo[x][y]->getShape().getGlobalBounds())
						&& !shipsTwo[k]->getShip().getGlobalBounds().intersects(fieldsTwo[x][y]->getShape().getGlobalBounds()))
					{
						fieldsTwo[x][y]->setMarked();
					}
				}
			}
		}
	}
	return false;
}

void GameMap::initSets(User** users)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fieldsOne[i][j] = new Field(x1a, y1a, true, 29.5, 29.5);
			fieldsTwo[i][j] = new Field(x2a, y2a, true, 29.5, 29.5);
			x1a += 30;
			x2a += 30;
		}
		x1a = x1b;
		x2a = x2b;
		y2a += 30;
		y1a += 30;
	}
	players[0] = users[0];
	players[1] = users[1];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (players[0]->getShipRect(i).getGlobalBounds().intersects(fieldsOne[j][k]->getShape().getGlobalBounds()))
				{
					fieldsOne[j][k]->setValue(1);
					players[0]->getShip(i)->addFieldToShoot();
				}
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (players[1]->getShipRect(i).getGlobalBounds().intersects(fieldsTwo[j][k]->getShape().getGlobalBounds()))
				{
					fieldsTwo[j][k]->setValue(1);
					players[1]->getShip(i)->addFieldToShoot();
				}
			}
		}
	}
	this->shipsOne = players[0]->getAllShips();
	this->shipsTwo = players[1]->getAllShips();
}

bool GameMap::allShipsDown()
{
	int counter = 0;
	if (currentPlayerMove == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (shipsTwo[i]->getFieldToShoot() == 0)
				counter++;
		}
	}
	else if (currentPlayerMove == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			if (shipsOne[i]->getFieldToShoot() == 0)
				counter++;
		}
	}
	std::cout << "counter: " << counter << std::endl;
	if (counter == 10)
	{
		Sleep(2000);
		return true;
	}
	return false;
}


void GameMap::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sprite, states);
	boards[0]->render(target);
	boards[1]->render(target);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			fieldsOne[i][j]->render(target);
			fieldsTwo[i][j]->render(target);
		}
	for (int i = 0; i < 10; i++)
	{
		if (shipsOne[i]->getShow())
			shipsOne[i]->render(target);
		if (shipsTwo[i]->getShow())
			shipsTwo[i]->render(target);
	}
	playerOneName->render(target);
	playerTwoName->render(target);

	target.draw(this->pointer, states);
}