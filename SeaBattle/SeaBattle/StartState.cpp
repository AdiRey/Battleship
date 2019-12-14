#include "StartState.h"

StartState::StartState()
{
	this->startButton = new Button(500, 405, 200, 50, "Start");
	this->settingsButton = new Button(500, 455, 200, 50, "Settings");
	this->exitButton = new Button(500, 505, 200, 50, "Exit");
}

StartState::~StartState()
{
	delete this->startButton;
	delete this->settingsButton;
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
		this->settingsButton->update(position, event);
		this->exitButton->update(position, event);

		if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
		{
			this->soundtrack->getSoundClicked().play();
			appStates = AppStates::GOODBYE;
		}
		else if (this->manager.isShapeLeftClicked(this->startButton->getButton(), event, position))
			appStates = AppStates::CHOICE;
		else if (this->manager.isShapeLeftClicked(this->settingsButton->getButton(), event, position))
			appStates = AppStates::SETTINGS;
		else if (this->manager.isShapeLeftClicked(this->exitButton->getButton(), event, position))
		{
			appStates = AppStates::GOODBYE;
			return;
		}
	}
}

void StartState::initMusic(Soundtrack* soundtrack)
{
	this->soundtrack = soundtrack;
	this->startButton->initMusic(this->soundtrack);
	this->settingsButton->initMusic(this->soundtrack);
	this->exitButton->initMusic(this->soundtrack);
	this->spriteSettings->initMusic(this->soundtrack);
}


void StartState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
	this->startButton->render(&target);
	this->settingsButton->render(&target);
	this->exitButton->render(&target);
}