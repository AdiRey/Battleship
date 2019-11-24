#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteClicker.h"
using namespace sf;
class State : public sf::Drawable
{
protected:
	SpriteClicker* spriteSettings;

	sf::Texture texture;
	sf::Sprite sprite;
public:
	State();
	virtual ~State();
	virtual void init(sf::RenderWindow* window) = 0;
	virtual void handleInput() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

