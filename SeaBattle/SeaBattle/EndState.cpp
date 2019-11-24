#include "EndState.h"
EndState::EndState()
{
	const_cast<Texture&>(texture).loadFromFile("images/statkiStart.png");
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	oneMoreTimeButton = new Button(400, 425, 400, 50, "One more time");
	exitButton = new Button(400, 505, 400, 50, "Exit");
}

EndState::~EndState()
{
	delete this->oneMoreTimeButton;
	delete this->exitButton;
	delete this->subtitle;
}

void EndState::handleInput()
{
	sf::Event event;
	sf::Vector2f position = Vector2f(Mouse::getPosition(*this->window));
	while (this->window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			window->close();
		oneMoreTimeButton->update(position, event);
		exitButton->update(position, event);
		this->spriteSettings->update(position, event);
		if (this->manager.isShapeLeftClicked(this->oneMoreTimeButton->getButton(), event, position))
			appStates = AppStates::NEW_START;
		else if (this->manager.isShapeLeftClicked(this->exitButton->getButton(), event, position))
			window->close();
		else if (this->manager.isSpriteLeftClicked(this->spriteSettings->getSprite(), event, position))
			appStates = AppStates::SETTINGS;
	}

}
void EndState::init(sf::RenderWindow* window)
{
	this->window = window;
}


void EndState::initSets(User** users)
{
	if (users[0]->getWinner())
		winner = "Player One!";
	else
		winner = "Player Two!";
	subtitle = new Subtitle("The winner is " + winner, Vector2f(250, 250),
		Fonts::ARIAL, Color::White, 60, Text::Italic);
	subtitle->setOutlines(Color::Magenta, 3);
}

void EndState::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(this->sprite, states);
	this->spriteSettings->render(&target);
	this->subtitle->render(target);
	this->oneMoreTimeButton->render(&target);
	this->exitButton->render(&target);
}