#include "State.h"

State::State()
{
	this->spriteSettings = new SpriteClicker(1150, 0, "settings", "settings2", "settings3");
	this->texture.loadFromFile("images/statkiStart.png");
	this->sprite.setTexture(this->texture);
}

State::~State()
{
	delete spriteSettings;
}