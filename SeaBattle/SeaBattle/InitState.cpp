#include "InitState.h"

InitState::InitState()
{
	float x1 = 195.f, x2 = 195.f, y1 = 135.f, y2 = 135.f;
	board = new Board(300, 300, x1, y1);

	tableForShips.setPosition(570, 130);
	tableForShips.setSize(Vector2f(125, 310));
	tableForShips.setFillColor(Color::Red);

	for (int i = 0; i < 10; i++)
	{
		if (i < 4)
		{
			shipsOne[i] = new Ship(1, 590, 150, i);
			shipsTwo[i] = new Ship(1, 590, 150, i);
		}
		else if (i < 7)
		{
			shipsOne[i] = new Ship(2, 590, 150, i);
			shipsTwo[i] = new Ship(2, 590, 150, i);
		}
		else if (i < 9)
		{
			shipsOne[i] = new Ship(3, 590, 150, i);
			shipsTwo[i] = new Ship(3, 590, 150, i);
		}
		else
		{
			shipsOne[i] = new Ship(4, 590, 150, i);
			shipsTwo[i] = new Ship(4, 590, 150, i);
		}
	}

	button = new Button(1000, 500, 200, 50, "Next");
	button->setStyle(Text::Italic);
	setShipsSubtitle = new Subtitle("Ustaw wszystkie statki!", Vector2f(400, 510), Fonts::ARIAL, Color::Red, 30, Text::Italic);
	playerName = new Subtitle("Player One", Vector2f(200, 60), Fonts::ARIAL, Color::White, 40, Text::Italic);

	setShipsSubtitle->setOutlines(Color::Black, 2);
	playerName->setOutlines(Color::Black, 2);
}
InitState::~InitState()
{
	delete button;
	delete board;
}

void InitState::init(sf::RenderWindow* window)
{
	this->window = window;
}

void InitState::handleInput()
{
	sf::Event event;
	sf::Vector2f position = Vector2f(Mouse::getPosition(*this->window));
	int i;

	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			window->close();

		if (isAllSet())
			showWrongSubtitle = true;
		else
			showWrongSubtitle = false;

		try
		{
			for (i = 0; i < 10; i++)
			{
				if (whichUser == 0)
					shipsOne[i]->update(position, event, *board);
				else
					shipsTwo[i]->update(position, event, *board);
			}
		}
		catch (std::invalid_argument & ia)
		{
			if (whichUser == 0)
				shipsOne[i]->correctShip(rightSetShip(i));
			else
				shipsTwo[i]->correctShip(rightSetShip(i));
		}
		catch (std::range_error & ia)
		{
			if (whichUser == 0)
				shipsOne[i]->shipRotate(rightSetShip(i));
			else
				shipsTwo[i]->shipRotate(rightSetShip(i));
		}
		button->update(position, event);
		clickNext(position, event);
	}
}

bool InitState::clickNext(Vector2f& pos, Event& event)
{
	if (button->getButton().getGlobalBounds().contains(pos))
	{
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && isClickNext)
		{
			isClickNext = false;
			if (whichUser == 0)
			{
				if (isAllSet())
				{
					players[0] = new User("Player One");
					players[0]->setShips(shipsOne);
					button->getTextButton().setString("Play");
					whichUser++;
					playerName->setText("Player Two");
					showWrongSubtitle = false;
				}
				else
				{
					showWrongSubtitle = true;
				}
			}
			else if (whichUser == 1)
			{
				if (isAllSet())
				{
					players[1] = new User("Player Two");
					for (int i = 0; i < 10; i++)
					{
						shipsTwo[i]->setAdditionalPositionOfShip(510, 0);
					}
					players[1]->setShips(shipsTwo);
					return true;
				}
				else
				{
					showWrongSubtitle = true;
				}
			}
		}
		else if (event.type == Event::MouseButtonReleased)
		{
			isClickNext = true;
		}
	}
	return false;
}

bool InitState::rightSetShip(int i) const
{
	for (int j = 0; j < 10; j++)
	{
		if (whichUser == 0)
		{
			if (i == j)
				continue;
			if (shipsOne[i]->getShip().getGlobalBounds().intersects(shipsOne[j]->getAroundShip().getGlobalBounds()))
				return true;
		}
		else
		{
			if (i == j)
				continue;
			if (shipsTwo[i]->getShip().getGlobalBounds().intersects(shipsTwo[j]->getAroundShip().getGlobalBounds()))
				return true;
		}
	}
	return false;
}

User** InitState::getUsers()
{
	return this->players;
}

bool InitState::isAllSet()
{
	if (!whichUser)
	{
		allShip1 = 0;
		for (int i = 0; i < 10; i++)
		{
			if (shipsOne[i]->getShipIsSetOrNot())
				allShip1++;
		}
		if (allShip1 == 10)
			return true;
	}
	else
	{
		allShip2 = 0;
		for (int i = 0; i < 10; i++)
		{
			if (shipsTwo[i]->getShipIsSetOrNot())
				allShip2++;
		}
		if (allShip2 == 10)
			return true;
	}
	return false;
}

void InitState::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sprite, states);
	if (!showWrongSubtitle)
	{
		setShipsSubtitle->render(target);
		target.draw(tableForShips, states);
	}
	board->render(target);
	for (int i = 0; i < 10; i++)
	{
		if (whichUser == 0)
			this->shipsOne[i]->render(target);
		else
			this->shipsTwo[i]->render(target);
	}
	button->render(&target);
	this->playerName->render(target);
	/*this->textField.render(target);*/
}