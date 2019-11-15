#pragma once
#include <SFML/Graphics.hpp>

class State : public sf::Drawable
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	State();
	virtual ~State() = default;
	virtual void init(sf::RenderWindow* window) = 0;
	virtual void handleInput() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

