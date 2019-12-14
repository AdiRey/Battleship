#include "Slider.h"
Slider::Slider(int x, int y)
{
	xCord = x;
	yCord = y;

	axisHeight = 10;
	axisWidth = 200;

	sliderWidth = 10;
	sliderHeight = 30;

	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Error loading font\n";

	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);

	axis.setPosition(x, y);
	axis.setOrigin(0, axisHeight / 2);
	axis.setSize(sf::Vector2f(axisWidth, axisHeight));
	axis.setFillColor(sf::Color(63, 63, 63));

	slider.setPosition(x, y);
	slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
	slider.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	slider.setFillColor(sf::Color(192, 192, 192));
}

sf::Text Slider::returnText(int x, int y, std::string z, int fontSize) //TODO change it
{
	text.setCharacterSize(fontSize);
	text.setPosition(x, y);
	text.setString(z);
	return text;
}

void Slider::setRange(int min, int max)
{
	sliderValue = min;
	minValue = min;
	maxValue = max;
}

void Slider::update(sf::Vector2f& pos, sf::Event& event)
{
	if (manager.isShapeLeftClicked(slider, event, pos))
	{
		isMove = true;
		dx = pos.x - slider.getPosition().x;
	}
	else if (event.type == sf::Event::MouseButtonReleased)
		isMove = false;

	if (isMove)
	{
		if (pos.x - dx >= xCord && pos.x - dx <= xCord + axisWidth)
			slider.setPosition(pos.x - dx, yCord);
		sliderValue = (minValue + ((slider.getPosition().x - xCord) / axisWidth * (maxValue - minValue)));
	}
}

float Slider::getSliderValue()
{
	return this->sliderValue;
}

void Slider::setSliderValue(int sliderValue) // przerobic
{
	if (sliderValue >= minValue && sliderValue <= maxValue)
	{
		this->sliderValue = sliderValue;
		float diff = maxValue - minValue;
		float diff2 = sliderValue - minValue;
		float zzz = axisWidth / diff;
		float posX = zzz * diff2;
		posX += xCord;
		slider.setPosition(posX, yCord);
	}
}

void Slider::setSliderPercentValue(int newPercentValue)
{
	if (newPercentValue >= 0 && newPercentValue <= 100)
	{
		sliderValue = newPercentValue / 100 * maxValue;
		slider.setPosition(xCord + (axisWidth * newPercentValue / 100), yCord);
	}
}

void Slider::setColors(sf::Color sliderColor, sf::Color axisColor)
{
	this->slider.setFillColor(sliderColor);
	this->axis.setFillColor(axisColor);
}

void Slider::render(sf::RenderTarget& target)
{
	target.draw(this->axis);
	target.draw(this->slider);
	target.draw(returnText(xCord - 10, yCord + 5, std::to_string(minValue), 20));
	target.draw(returnText(xCord + axisWidth - 10, yCord + 5, std::to_string(maxValue), 20));
	target.draw(returnText(slider.getPosition().x - sliderWidth, slider.getPosition().y - sliderHeight,
		std::to_string((int)sliderValue), 15));
}