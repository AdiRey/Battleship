#include "SpriteClicker.h"

SpriteClicker::SpriteClicker(float x, float y, std::string spriteName, std::string spriteName2, std::string spriteName3)
{
	this->texture[0].loadFromFile("images/" + spriteName + ".png");
	this->sprite[0].setTexture(this->texture[0]);
	this->sprite[0].setPosition(x, y);
	if (spriteName2 != "")
	{
		this->texture[1].loadFromFile("images/" + spriteName2 + ".png");
		this->sprite[1].setTexture(this->texture[1]);
		this->sprite[1].setPosition(x, y);
		if (spriteName3 != "")
		{
			this->texture[2].loadFromFile("images/" + spriteName3 + ".png");
			this->sprite[2].setTexture(this->texture[2]);
			this->sprite[2].setPosition(x, y);
		}
	}

	this->bufferOne.loadFromFile("music/Click2-Sebastian-759472264.ogg");
	this->bufferTwo.loadFromFile("music/Click-On-SoundBible.com-1697535117.ogg");
	this->soundOne.setBuffer(this->bufferOne);
	this->soundTwo.setBuffer(this->bufferTwo);
	this->soundOne.setLoop(false);
	this->soundTwo.setLoop(false);
}

int SpriteClicker::update(Vector2f& pos, Event& event)
{
	this->spriteState = SP_ID;

	if (this->sprite[0].getGlobalBounds().contains(pos.x, pos.y))
	{
		this->spriteState = SP_HOV;
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			this->spriteState = SP_ACTIVE;
	}
	else
		this->hoverOnce = true;

	switch (this->spriteState)
	{
	case SpriteStates::SP_ID:
		this->which = 0;
		break;
	case SP_HOV:
		this->which = 1;
		if (this->hoverOnce)
		{
			this->soundOne.play();
			this->hoverOnce = false;
		}
		break;
	case SP_ACTIVE:
		this->which = 2;
		this->soundTwo.play();
		break;
	default:
		break;
	}
	return this->which;
}

Sprite SpriteClicker::getSprite()
{
	return this->sprite[0];
}

void SpriteClicker::setWhich(int which)
{
	this->which = which;
}

// Print
void SpriteClicker::render(RenderTarget* target) const
{
	switch (this->which)
	{
	case 0:
		target->draw(sprite[0]);
		break;
	case 1:
		target->draw(sprite[1]);
		break;
	case 2:
		target->draw(sprite[2]);
		break;
	default:
		break;
	}
}