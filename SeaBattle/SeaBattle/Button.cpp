#include "Button.h"

Button::Button(float x, float y, float width, float height, std::string text, std::string fontName,
	Color bgColor, Color idColor, Color hoverColor, Color activeColor)
{
	shape.setPosition(Vector2f(x, y));
	shape.setSize(Vector2f(width, height));
	this->font.loadFromFile(fontName + ".ttf");

	this->idColor = idColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->bgColor = bgColor;

	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(this->idColor);
	this->text.setCharacterSize(50);
	this->text.setOutlineColor(Color::Black);
	this->text.setOutlineThickness(2);
	this->text.setPosition(
		shape.getPosition().x + (shape.getGlobalBounds().width - this->text.getGlobalBounds().width) / 2.f - 5,
		shape.getPosition().y + (shape.getGlobalBounds().height - this->text.getGlobalBounds().height) / 2.f - 5
	);

	this->shape.setFillColor(this->bgColor);
}

void Button::update(Vector2f& pos, Event& event)
{
	buttonState = BTN_ID;

	if (shape.getGlobalBounds().contains(pos.x, pos.y))
	{
		buttonState = BTN_HOV;

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			buttonState = BTN_ACTIVE;
		}
	}

	switch (buttonState)
	{
	case BTN_ID:
		text.setFillColor(idColor);
		break;
	case BTN_HOV:
		text.setFillColor(hoverColor);
		break;
	case BTN_ACTIVE:
		text.setFillColor(activeColor);
		break;
	default:
		text.setFillColor(Color::Cyan);
	}
}

void Button::setStyle(Uint32 style)
{
	this->text.setStyle(style);
}


RectangleShape Button::getButton() const
{
	return this->shape;
}

Text& Button::getTextButton()
{
	return this->text;
}


void Button::render(RenderTarget* target) const
{
	target->draw(shape);
	target->draw(text);
}