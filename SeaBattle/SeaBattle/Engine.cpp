#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height, std::string title)
{
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close);
	this->music.openFromFile("music/Battleship-_OST_-1-First-Transmission.ogg");
	this->music.setLoop(true);
	this->music.play();
	this->window->setActive(true);
	this->window->setVerticalSyncEnabled(true);
	appStates = AppStates::START;
	this->states.push_back(new StartState());
	this->states.push_back(new InitState());
	this->states.push_back(new GameState());
	this->states.push_back(new EndState());
	for (auto &state : states)
		state->init(window);

	this->run();
}

void Engine::run()
{
	while (this->window->isOpen())
	{
		if (isOk && appStates == AppStates::GAME)
		{
			reinterpret_cast<GameState*>(this->states[2])->initSets(reinterpret_cast<InitState*>(this->states[1])->getUsers());
			reinterpret_cast<EndState*>(this->states[3])->initSets(reinterpret_cast<InitState*>(this->states[1])->getUsers());
			isOk = false;
		}
		window->clear();
		switch (appStates)
		{
		case AppStates::NEW_START:
			this->init();
			isOk = true;
			appStates = AppStates::START;
			break;
		case AppStates::START:
			this->window->draw(*this->states[0]);
			this->states[0]->handleInput();
			break;
		case AppStates::INIT:
			this->window->draw(*this->states[1]);
			this->states[1]->handleInput();
			break;
		case AppStates::GAME:
			this->window->draw(*this->states[2]);
			this->states[2]->handleInput();
			break;
		case AppStates::END:
			this->window->draw(*this->states[3]);
			this->states[3]->handleInput();
			break;
		default:
			this->window->close();
			break;
		}
		window->display();
	}
}

void Engine::init()
{
	for (auto& state : states)
		delete state;
	this->states[0] = new StartState();
	this->states[1] = new InitState();
	this->states[2] = new GameState();
	this->states[3] = new EndState();
	for (auto& state : states)
		state->init(window);
}

Engine::~Engine()
{
	for (auto state : this->states)
		delete state;
	delete this->window;
}