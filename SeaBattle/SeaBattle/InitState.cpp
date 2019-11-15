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
	sf::Vector2f position = Vector2f(Mouse::getPosition(*window));

	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			window->close();

		for (int i = 0; i < 10; i++)
		{
			if (whichUser == 0)
				shipsOne[i]->update(position, event, *board);
			else
				shipsTwo[i]->update(position, event, *board);
		}
	}

	if (isAllSet())
		showWrongSubtitle = true;
	else
		showWrongSubtitle = false;

	try
	{
		for (i = 0; i < 10; i++)
		{
			if (whichUser == 0)
				shipsOne[i]->update(pos, event, *board);
			else
				shipsTwo[i]->update(pos, event, *board);
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
	button->update(pos, event);
	return clickNext(pos, event);
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