#include "GameState.h"
#include <iostream>

GameState::GameState()
{
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

GameState::~GameState()
{
	delete this->playerOneName;
	delete this->playerTwoName;
	for (auto& board : this->boards)
		delete board;
	for (auto& fields : this->fieldsOne)
		for (auto& field : fields)
			delete field;
	for (auto& fields : this->fieldsTwo)
		for (auto& field : fields)
			delete field;
}

void GameState::handleInput()
{
	sf::Event event;
	sf::Vector2f position = Vector2f(Mouse::getPosition(*this->window));
	bool endLoops = false;

	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			window->close();

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				int x = 0;
				if (!currentPlayerMove)
				{
					x = fieldsTwo[i][j]->update(position, event, shipsTwo);
					if (x == 1)
					{
						currentPlayerMove = 1;
						endLoops = true;
						this->pointer.rotate(180);
						break;
					}
				}
				else if (currentPlayerMove)
				{
					x = fieldsOne[i][j]->update(position, event, shipsOne);
					if (x == 1)
					{
						currentPlayerMove = 0;
						endLoops = true;
						this->pointer.rotate(180);
						break;
					}
				}
				if (endLoops)
					break;
				if (!x)
					allShipsDown();
			}
		}
	}

	for (int k = 0; k < 10; k++)
	{
		if (this->shipsOne[k]->getFieldToShoot() == 0 && !this->shipsOne[k]->getShow())
		{
			this->shipsOne[k]->setShow(true);
			for (int x = 0; x < 10; x++)
			{
				for (int y = 0; y < 10; y++)
				{
					if (this->shipsOne[k]->getAroundShip().getGlobalBounds()
						.intersects(fieldsOne[x][y]->getShape().getGlobalBounds())
						&& !this->shipsOne[k]->getShip().getGlobalBounds().intersects(this->fieldsOne[x][y]->getShape().getGlobalBounds()))
					{
						this->fieldsOne[x][y]->setMarked();
					}
				}
			}
		}
	}
	for (int k = 0; k < 10; k++)
	{
		if (this->shipsTwo[k]->getFieldToShoot() == 0 && !this->shipsTwo[k]->getShow())
		{
			this->shipsTwo[k]->setShow(true);
			for (int x = 0; x < 10; x++)
			{
				for (int y = 0; y < 10; y++)
				{
					if (this->shipsTwo[k]->getAroundShip().getGlobalBounds()
						.intersects(fieldsTwo[x][y]->getShape().getGlobalBounds())
						&& !this->shipsTwo[k]->getShip().getGlobalBounds().intersects(this->fieldsTwo[x][y]->getShape().getGlobalBounds()))
					{
						this->fieldsTwo[x][y]->setMarked();
					}
				}
			}
		}
	}
	if (this->player[0]->getWinner() || this->player[1]->getWinner())
		appStates = AppStates::END;
}

void GameState::initSets(User** users)
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
	player[0] = users[0];
	player[1] = users[1];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (player[0]->getShipRect(i).getGlobalBounds().intersects(fieldsOne[j][k]->getShape().getGlobalBounds()))
				{
					fieldsOne[j][k]->setValue(1);
					player[0]->getShip(i)->addFieldToShoot();
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
				if (player[1]->getShipRect(i).getGlobalBounds().intersects(fieldsTwo[j][k]->getShape().getGlobalBounds()))
				{
					fieldsTwo[j][k]->setValue(1);
					player[1]->getShip(i)->addFieldToShoot();
				}
			}
		}
	}
	this->shipsOne = player[0]->getAllShips();
	this->shipsTwo = player[1]->getAllShips();
}

void GameState::allShipsDown()
{
	int counter = 0;
	if (currentPlayerMove == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (shipsTwo[i]->getFieldToShoot() == 0)
				counter++;
		}
		if (counter == 10)
			this->player[0]->setWinner(true);
	}
	else if (currentPlayerMove == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			if (shipsOne[i]->getFieldToShoot() == 0)
				counter++;
		}
		if (counter == 10)
			this->player[1]->setWinner(true);
	}
}

void GameState::init(sf::RenderWindow* window)
{
	this->window = window;
}

void GameState::draw(RenderTarget& target, RenderStates states) const
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