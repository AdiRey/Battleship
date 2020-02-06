#pragma once
#include <SFML\Graphics.hpp>
#include "EventManager.h"
#include <iostream>

class Slider
{
	sf::RectangleShape slider;
	sf::RectangleShape axis;

	sf::Font font;
	sf::Text text;

	EventManager manager;
	bool isMove{ false };
	float dx;

	int minValue;
	int maxValue;

	float xCord;
	float yCord;

	int axisWidth;
	int axisHeight;

	int sliderWidth;
	int sliderHeight;

	int sliderValue;
public:
	Slider(int x, int y);

	sf::Text returnText(int x, int y, std::string z, int fontSize);

	void setRange(int min, int max);
	void update(sf::Vector2f& pos, sf::Event& event);

	float getSliderValue();
	void setSliderValue(int sliderValue);
	void setSliderPercentValue(int newPercentValue);
	void setColors(sf::Color sliderColor = sf::Color(192, 192, 192), sf::Color axisColor = sf::Color(63, 63, 63));

	void render(sf::RenderTarget& target);
};