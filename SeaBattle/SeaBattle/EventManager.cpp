#include "EventManager.h"

bool EventManager::isSpriteLeftClicked(const sf::Sprite sprite, sf::Event event, sf::Vector2f position)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (sprite.getGlobalBounds().contains(position))
			return true;
	}
	return false;
}

bool EventManager::isShapeLeftClicked(const sf::RectangleShape shape, sf::Event event, sf::Vector2f position)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (shape.getGlobalBounds().contains(position))
		{
			return true;
		}
	}

	return false;
}