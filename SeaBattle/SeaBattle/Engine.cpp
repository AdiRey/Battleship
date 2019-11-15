#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height, std::string title)
{
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close);
	this->window->setActive(true);
	this->window->setVerticalSyncEnabled(true);
	appStates = START;
	this->states.push_back(new StartState());
	states[0]->init(window);

	this->run();
}

void Engine::run()
{
	while (this->window->isOpen())
	{
		window->clear();
		switch (appStates)
		{
		case AppStates::START:
			this->window->draw(*states[0]);
			states[0]->handleInput();
			break;
		case AppStates::INIT:
			break;
		case AppStates::GAME:
			break;
		case AppStates::END:
			break;
		default:
			break;
		}
		window->display();
	}
}

Engine::~Engine()
{
	delete this->window;
}