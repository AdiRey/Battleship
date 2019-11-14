#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Board
{
private:
	RectangleShape board;
	const Texture texture;
public:
	//Constructor destructor
	Board() = delete;
	Board(int width, int height);
	Board(int width, int height, float x, float y);
	virtual ~Board() = default;

	// Methods
	RectangleShape getBoard() const;
	void setPosition(float x, float y);

	// Print
	void render(RenderTarget& target) const;
};