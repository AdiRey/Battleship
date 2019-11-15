#pragma once
#include <SFML/Graphics.hpp>
class EventManager
{
public:
	bool isSpriteLeftClicked(const sf::Sprite sprite, sf::Event event, sf::Vector2f position);
	bool isShapeLeftClicked(const sf::RectangleShape shape, sf::Event event, sf::Vector2f position);
};

