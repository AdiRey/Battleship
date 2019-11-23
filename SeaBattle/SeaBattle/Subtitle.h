#pragma once
#include <SFML/Graphics.hpp>

enum Fonts { ARIAL };

using namespace sf;
class Subtitle
{
private:
	Text text;
	Font font{};
public:
	//Constructors and destructor
	Subtitle() = delete;
	Subtitle(std::string str, Vector2f pos = Vector2f(0, 0), Fonts = Fonts::ARIAL,
		Color fillColor = Color::White, int characterSize = 30, Uint32 style = Text::Regular);
	virtual ~Subtitle() = default;

	// Methods
	void setText(std::string newText);
	void setPosition(Vector2f pos);
	void setOutlines(Color color = Color::Black, float thickness = 1);

	// Print
	void render(RenderTarget& target) const;
};