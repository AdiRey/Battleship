#include "SettingsState.h"

SettingsState::SettingsState()
{
	this->resumeButton = new Button(500, 205, 200, 50, "Resume");
	this->volumeButton = new Button(500, 255, 200, 50, "Volume");
	this->exitButton = new Button(500, 305, 200, 50, "Exit");
}

SettingsState::~SettingsState()
{
	delete this->resumeButton;
	delete this->volumeButton;
	delete this->exitButton;
}

void SettingsState::init(sf::RenderWindow* window)
{
	this->window = window;
}

void SettingsState::handleInput()
{
	sf::Event event;
	sf::Vector2f position = Vector2f(Mouse::getPosition(*this->window));

	while (this->window->pollEvent(event))
	{
		this->resumeButton->update(position, event);
		this->volumeButton->update(position, event);
		this->exitButton->update(position, event);

		if (event.type == Event::Closed)
			this->window->close();
		else if (this->manager.isShapeLeftClicked(this->resumeButton->getButton(), event, position))
			appStates = this->previous;
		else if (this->manager.isShapeLeftClicked(this->volumeButton->getButton(), event, position))
			appStates = AppStates::VOLUME;
		else if (this->manager.isShapeLeftClicked(this->exitButton->getButton(), event, position))
		{
			appStates = AppStates::CLOSE;
			return;
		}
	}
}

void SettingsState::setPreviousState(AppStates previous)
{
	this->previous = previous;
}

void SettingsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	this->resumeButton->render(&target);
	this->volumeButton->render(&target);
	this->exitButton->render(&target);
}