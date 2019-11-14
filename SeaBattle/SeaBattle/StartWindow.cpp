#include "StartWindow.h"

StartWindow::StartWindow()
{
	startButton = new Button(500, 425, 200, 50, "Start");
	exitButton = new Button(500, 495, 200, 50, "Exit");
	const_cast<Texture&>(texture).loadFromFile("images/statkiStart.png");
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
}

bool StartWindow::justUserClicked(Window& window, Event& event, Vector2f& pos) const
{
	startButton->update(pos, event);
	exitButton->update(pos, event);
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if (startButton->getButton().getGlobalBounds().contains(pos.x, pos.y))
		{
			return true;
		}
		else if (exitButton->getButton().getGlobalBounds().contains(pos.x, pos.y))
		{
			window.close();
		}
	}
	return false;
}


void StartWindow::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sprite, states);
	startButton->render(&target);
	exitButton->render(&target);
}
