#include "Board.h"

//Contructors
Board::Board(int width, int height)
{
	const_cast<Texture&>(texture).loadFromFile("images/grid2.png");
	board.setSize(Vector2f(width, height));
	board.setTexture(&texture);
	board.setOutlineThickness(3);
	board.setOutlineColor(Color::Black);
}

Board::Board(int width, int height, float x, float y) : Board(width, height)
{
	this->board.setPosition(x, y);
}

//Methods
RectangleShape Board::getBoard() const
{
	return this->board;
}

void Board::setPosition(float x, float y)
{
	this->board.setPosition(x, y);
}


// Print
void Board::render(RenderTarget& target) const
{
	target.draw(this->board);
}
