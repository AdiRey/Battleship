#include "State.h"

State::State()
{
	this->texture.loadFromFile("images/statkiStart.png");
	this->sprite.setTexture(this->texture);
}