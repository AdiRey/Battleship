#include "Subtitle.h"

Subtitle::Subtitle(std::string str, Vector2f pos, Fonts fonts, Color fillColor, int characterSize, Uint32 style) // TODO
{
	switch (fonts)
	{
	case ARIAL:
		this->font.loadFromFile("arial.ttf");
		break;
	default:
		break; ////TODO exception
	}

	this->text.setString(str);
	this->text.setPosition(pos);
	this->text.setFont(this->font);
	this->text.setFillColor(fillColor);
	this->text.setCharacterSize(characterSize);
	this->text.setStyle(style);
}

void Subtitle::setOutlines(Color color, float thickness)
{
	this->text.setOutlineColor(color);
	this->text.setOutlineThickness(thickness);
}


void Subtitle::setText(std::string newText)
{
	this->text.setString(newText);
}

void Subtitle::setPosition(Vector2f pos)
{
	this->text.setPosition(pos);
}

void Subtitle::render(RenderTarget& target) const
{
	target.draw(this->text);
}