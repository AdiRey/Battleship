#include "StartState.h"

StartState::StartState()
{
	startButton = new Button(500, 425, 200, 50, "Start");
	exitButton = new Button(500, 495, 200, 50, "Exit");
}

StartState::~StartState()
{
	delete startButton;
	delete exitButton;
}

void StartState::init(sf::RenderWindow* window)
{
	this->window = window;
}

void StartState::handleInput()
{
	sf::Event event;
	sf::Vector2f position = Vector2f(Mouse::getPosition(*window));

	while (window->pollEvent(event))
	{
		startButton->update(position, event);
		exitButton->update(position, event);

		if (event.type == Event::Closed)
			window->close();
		else if (manager.isShapeLeftClicked(startButton->getButton(), event, position))
			appStates = INIT;
		else if (manager.isShapeLeftClicked(exitButton->getButton(), event, position))
			window->close();
	}
}

void StartState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	startButton->render(&target);
	exitButton->render(&target);
}