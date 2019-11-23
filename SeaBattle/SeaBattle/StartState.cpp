#include "StartState.h"

StartState::StartState()
{
	this->startButton = new Button(500, 425, 200, 50, "Start");
	this->exitButton = new Button(500, 495, 200, 50, "Exit");
}

StartState::~StartState()
{
	delete this->startButton;
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
		this->startButton->update(position, event);
		this->exitButton->update(position, event);

		if (event.type == Event::Closed)
			this->window->close();
		else if (this->manager.isShapeLeftClicked(this->startButton->getButton(), event, position))
			appStates = AppStates::INIT;
		else if (this->manager.isShapeLeftClicked(this->exitButton->getButton(), event, position))
			this->window->close();
	}
}

void StartState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	this->startButton->render(&target);
	this->exitButton->render(&target);
}