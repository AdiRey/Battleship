#include "TextField.h"

const string TextField::getText()
{
	return this->text;
}

void TextField::setPosition(float x, float y)
{
	Transformable::setPosition(x, y);
	rect.setPosition(x, y);
}


bool TextField::contains(Vector2f point)
{
	return rect.getGlobalBounds().contains(point);
}

void TextField::setFocus(bool focus)
{
	this->hasFocus = focus;
	if (hasFocus)
		rect.setOutlineColor(Color::Blue);
	else
		rect.setOutlineColor(Color(127, 127, 127));
}

void TextField::handleInput(Event event)
{
	if (!hasFocus || event.type != Event::TextEntered)
		return;

	if (event.text.unicode == 8)
	{
		this->text = this->text.substr(0, this->text.size() - 1);
	}
	else if (text.size() < size) {
		text += event.text.unicode;
		texts.setString(text);
	}
}

void TextField::render(RenderTarget& target) const
{
	target.draw(this->rect);
	target.draw(this->texts);
}
