#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
using namespace sf;
class StartWindow : public Drawable
{
private:
	Button* startButton;
	Button* exitButton;
	const Texture texture;
	Sprite sprite;
public:
	StartWindow();
	~StartWindow() = default;
	bool justUserClicked(Window& window, Event& event, Vector2f& pos) const;
	void draw(RenderTarget& target, RenderStates states) const override;
};