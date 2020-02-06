#include "GoodbyeState.h"

GoodbyeState::GoodbyeState()
{
	this->backExit = new Button(500, 500, 200, 50, "No");
	this->backExit->setStyle(Text::Italic);

	this->confirmExit = new Button(500, 430, 200, 50, "Yes");
	this->confirmExit->setStyle(Text::Italic);

	this->endText = new Subtitle("Are you sure?", Vector2f(350, 300), Fonts::ARIAL, Color::White, 80);
	this->endText->setStyle(Text::Italic);
	this->endText->setOutlines(Color::Black, 4);
}

GoodbyeState::~GoodbyeState()
{
	delete this->backExit;
	delete this->confirmExit;
	delete this->endText;
}

void GoodbyeState::handleInput()
{
	sf::Event event;
	sf::Vector2f position = Vector2f(Mouse::getPosition(*this->window));

	while (this->window->pollEvent(event))
	{
		this->backExit->update(position, event);
		this->confirmExit->update(position, event);

		if (this->manager.isShapeLeftClicked(this->backExit->getButton(), event, position))
			appStates = this->previous;
		else if (this->manager.isShapeLeftClicked(this->confirmExit->getButton(), event, position))
		{
			appStates = AppStates::CLOSE;
			return;
		}
	}
}

void GoodbyeState::init(sf::RenderWindow* window)
{
	this->window = window;
}

void GoodbyeState::initMusic(Soundtrack* soundtrack)
{
	this->soundtrack = soundtrack;
	this->backExit->initMusic(soundtrack);
	this->confirmExit->initMusic(soundtrack);
	this->spriteSettings->initMusic(this->soundtrack);
}

void GoodbyeState::setPreviousState(AppStates previous)
{
	this->previous = previous;
}

void GoodbyeState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
	this->endText->render(target);
	this->confirmExit->render(&target);
	this->backExit->render(&target);
}