#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using std::string;

class TextField : public Transformable
{
private:
	Font font;
	Text texts;
	string text;
	bool hasFocus;
	unsigned int size;
	RectangleShape rect;

public:
	TextField(unsigned int maxChars);
	const string getText();
	void setPosition(float x, float y);
	bool contains(Vector2f point);
	void setFocus(bool focus);
	void handleInput(Event event);

	void render(RenderTarget& target) const;
};