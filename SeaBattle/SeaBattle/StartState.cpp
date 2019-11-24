#include "StartState.h"

StartState::StartState()
{
	this->startButton = new Button(500, 405, 200, 50, "Start");
	this->volumeButton = new Button(500, 455, 200, 50, "Volume");
	this->exitButton = new Button(500, 505, 200, 50, "Exit");
}

StartState::~StartState()
{
	delete this->startButton;
	delete this->volumeButton;
	delete this->exitButton;
}

void StartState::init(sf::RenderWindow* window)
{
	this->window = window;
}

void StartState::handleInput()
{
	sf::Event event;
	sf::Vector2f position = Vector2f(Mouse::getPosition(*this->window));

	while (this->window->pollEvent(event))
	{
		this->spriteSettings->update(position, event);
		this->startButton->update(position, event);
		this->volumeButton->update(position, event);
		this->exitButton->update(position, event);

		if (event.type == Event::Closed)
			this->window->close();
		else if (this->manager.isShapeLeftClicked(this->startButton->getButton(), event, position))
			appStates = AppStates::CHOICE;
		else if (this->manager.isShapeLeftClicked(this->exitButton->getButton(), event, position))
		{
			appStates = AppStates::CLOSE;
			return;
		}
		else if (this->manager.isSpriteLeftClicked(this->spriteSettings->getSprite(), event, position))
			appStates = AppStates::SETTINGS;
	}
}

void StartState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	this->spriteSettings->render(&target);
	this->startButton->render(&target);
	this->volumeButton->render(&target);
	this->exitButton->render(&target);
}