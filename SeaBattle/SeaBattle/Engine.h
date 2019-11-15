#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "DEFINITIONS.h"
#include "State.h"
#include "StartState.h"
class Engine
{
private:
	sf::RenderWindow* window;
	std::vector<State*> states;

	void run();
public:
	Engine() = delete;
	Engine(unsigned int width, unsigned int height, std::string title);
	~Engine();
};

