#include "ChoiceState.h"
ChoiceState::ChoiceState()
{
	this->spriteClicker[0] = new SpriteClicker(150, 200, "friends", "friends2", "friends3");
	this->spriteClicker2[0] = new SpriteClicker(500, 200, "ai", "ai2", "ai3");
	this->spriteClicker3[0] = new SpriteClicker(850, 200, "swiat", "swiat2", "swiat3");

	this->spriteClicker[1] = new SpriteClicker(150, 410, "znajomy", "znajomy2", "znajomy3");
	this->spriteClicker2[1] = new SpriteClicker(500, 410, "offline", "offline2", "offline3");
	this->spriteClicker3[1] = new SpriteClicker(850, 410, "online", "online2", "online3");
}
ChoiceState::~ChoiceState()
{
	for (auto &sprite : this->spriteClicker)
		delete sprite;
	for (auto& sprite : this->spriteClicker2)
		delete sprite;
	for (auto& sprite : this->spriteClicker3)
		delete sprite;
}
void ChoiceState::init(sf::RenderWindow* window)
{
	this->window = window;
}
void ChoiceState::handleInput()
{
	bool be = true;
	sf::Event event;
	sf::Vector2f position = Vector2f(Mouse::getPosition(*this->window));
	while (this->window->pollEvent(event))
	{
		if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
		{
			this->soundtrack->getSoundClicked().play();
			appStates = AppStates::GOODBYE;
		}
		this->spriteSettings->update(position, event);
		for (int i = 0; i < 2; i++)
		{
			if (be)
			{
				switch (this->spriteClicker[i]->update(position, event))
				{
				case 0:
					break;
				case 1:
					if (i)
						this->spriteClicker[0]->setWhich(1);
					else
						this->spriteClicker[1]->setWhich(1);
					be = false;
					break;
				case 2:
					if (i)
						this->spriteClicker[0]->setWhich(2);
					else
						this->spriteClicker[1]->setWhich(2);
					be = false;
					break;
				default:
					break;
				}
				switch (this->spriteClicker2[i]->update(position, event))
				{
				case 0:
					break;
				case 1:
					if (i)
						this->spriteClicker2[0]->setWhich(1);
					else
						this->spriteClicker2[1]->setWhich(1);
					be = false;
					break;
				case 2:
					if (i)
						this->spriteClicker2[0]->setWhich(2);
					else
						this->spriteClicker2[1]->setWhich(2);
					be = false;
					break;
				default:
					break;
				}
				switch (this->spriteClicker3[i]->update(position, event))
				{
				case 0:
					break;
				case 1:
					if (i)
						this->spriteClicker3[0]->setWhich(1);
					else
						this->spriteClicker3[1]->setWhich(1);
					be = false;
					break;
				case 2:
					if (i)
						this->spriteClicker3[0]->setWhich(2);
					else
						this->spriteClicker3[1]->setWhich(2);
					be = false;
					break;
				default:
					break;
				}
			}
			if (this->manager.isSpriteLeftClicked(this->spriteClicker[i]->getSprite(), event, position))
				appStates = AppStates::FRIEND_INIT;
			else if (this->manager.isSpriteLeftClicked(this->spriteClicker2[i]->getSprite(), event, position))
				appStates = AppStates::AI_INIT;
			else if (this->manager.isSpriteLeftClicked(this->spriteClicker3[i]->getSprite(), event, position))
				appStates = AppStates::ONLINE_INIT;
			else if (this->manager.isSpriteLeftClicked(this->spriteSettings->getSprite(), event, position))
				appStates = AppStates::SETTINGS;
		}
	}

}

void ChoiceState::initMusic(Soundtrack* soundtrack)
{
	this->soundtrack = soundtrack;
	for (int i = 0; i < 2; i++)
	{
		this->spriteClicker[i]->initMusic(this->soundtrack);
		this->spriteClicker2[i]->initMusic(this->soundtrack);
		this->spriteClicker3[i]->initMusic(this->soundtrack);
	}
	this->spriteSettings->initMusic(this->soundtrack);
}

void ChoiceState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	this->spriteSettings->render(&target);
	for (int i = 0; i < 2; i++)
	{
		this->spriteClicker[i]->render(&target);
		this->spriteClicker2[i]->render(&target);
		this->spriteClicker3[i]->render(&target);
	}
}