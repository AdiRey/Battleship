#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Soundtrack.h"
using namespace sf;

enum buttonStates { BTN_ID = 0, BTN_HOV = 1, BTN_ACTIVE = 2 };

class Button
{
private:
	Soundtrack* soundtrack;

	int buttonState{ BTN_ID };

	RectangleShape shape;
	bool hoverOnce{ true };

	Font font{};
	Text text{};

	Color idColor;
	Color hoverColor;
	Color activeColor;
	Color bgColor;

public:
	// Constructors
	Button() = delete;
	Button(float x, float y, float width, float height, std::string text, std::string fontName = "arial",
		Color bgColor = Color::Transparent, Color idColor = Color(192, 192, 192), Color hoverColor = Color::Red,
		Color activeColor = Color::Yellow);
	~Button() = default;

	// Methods
	void update(Vector2f& pos, Event& event);
	RectangleShape getButton() const;
	Text& getTextButton();
	void setStyle(Uint32 style = Text::Regular);
	void initMusic(Soundtrack* soundtrack);

	// Print
	void render(RenderTarget* target) const;
};