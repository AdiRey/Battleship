#include <SFML/Graphics.hpp>
#include "InitMap.h"
#include "StartWindow.h"
#include "GameMap.h"
#include "EndWindow.h"
#include "Ship.h"

using namespace sf;

enum AppStates { start, init, game, end };

int main()
{
	RenderWindow window(VideoMode(1200, 600), "Battle Ship", Style::Close);
	window.setActive(true);
	window.setVerticalSyncEnabled(true);

	AppStates appStates{ start };
	Event event;
	Vector2f position;

	auto startWindow = new StartWindow();
	auto initMap = new InitMap();
	auto gameMap = new GameMap();
	auto endWindow = new EndWindow();

	User** players;

	while (window.isOpen())
	{
		position = Vector2f(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}
		window.clear();
		switch (appStates)
		{
		case start:
			window.draw(*startWindow);
			if (startWindow->justUserClicked(window, event, position))
			{
				appStates = init;
			}
			break;
		case init:
			window.draw(*initMap);
			if (initMap->update(position, event))
			{
				appStates = game;
				players = initMap->getUsers();
				gameMap->initSets(players);
			}
			break;
		case game:
			window.draw(*gameMap);
			if (gameMap->update(position, event))
			{
				appStates = end;
				players = initMap->getUsers();
				endWindow->initSets(players);
			}
			break;
		case end:
			window.draw(*endWindow);
			if (endWindow->update(window, event, position))
			{
				appStates = start;
				delete initMap;
				delete gameMap;
				delete endWindow;
				initMap = new InitMap();
				gameMap = new GameMap();
				endWindow = new EndWindow();
			}
			break;
		default:
			break;
		}
		window.display();
	}
	return EXIT_SUCCESS;
}