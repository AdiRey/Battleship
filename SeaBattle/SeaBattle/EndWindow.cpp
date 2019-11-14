#include "EndWindow.h"

EndWindow::EndWindow()
{
	const_cast<Texture&>(texture).loadFromFile("images/statkiStart.png");
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	oneMoreTimeButton = new Button(400, 425, 400, 50, "One more time");
	exitButton = new Button(400, 505, 400, 50, "Exit");
}


void EndWindow::initSets(User** users)
{
	if (users[0]->getWinner())
		winner = "Player One!";
	else
		winner = "Player Two!";
	subtitle = new Subtitle("The winner is " + winner, Vector2f(250, 250),
		Fonts::ARIAL, Color::White, 60, Text::Italic);
	subtitle->setOutlines(Color::Magenta, 3);
}

bool EndWindow::update(Window& window, Event& event, Vector2f& pos)
{
	oneMoreTimeButton->update(pos, event);
	exitButton->update(pos, event);
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if (oneMoreTimeButton->getButton().getGlobalBounds().contains(pos.x, pos.y))
		{
			return true;
		}
		else if (exitButton->getButton().getGlobalBounds().contains(pos.x, pos.y))
		{
			window.close();
			return true;
		}
	}
	return false;
}


void EndWindow::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sprite, states);
	this->subtitle->render(target);
	this->oneMoreTimeButton->render(&target);
	this->exitButton->render(&target);
}
