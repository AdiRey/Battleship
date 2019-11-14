#pragma once
#include "Subtitle.h"
#include "Button.h"
#include "User.h"
class EndWindow : public Drawable
{
private:
	const Texture texture;
	Sprite sprite;

	Subtitle* subtitle;
	Button* oneMoreTimeButton;
	Button* exitButton;
	std::string winner;
public:
	// Constructor and destructor
	EndWindow();
	~EndWindow() = default;

	// Methods
	bool update(Window& window, Event& event, Vector2f& pos);
	void initSets(User** users);

	// Print
	void draw(RenderTarget& target, RenderStates states) const override;
};