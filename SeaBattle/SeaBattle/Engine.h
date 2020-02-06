#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "DEFINITIONS.h"
#include "State.h"
#include "StartState.h"
#include "InitState.h"
#include "GameState.h"
#include "EndState.h"
#include "ChoiceState.h"
#include "SettingsState.h"
#include "VolumeState.h"
#include "Soundtrack.h"
#include "GoodbyeState.h"

class Engine
{
private:
	sf::RenderWindow* window;

	Soundtrack* soundtrack;

	std::vector<State*> states;

	bool isOk = true;

	AppStates helper;

	void run();
	void init();
	void switchState();
public:
	Engine() = delete;
	Engine(unsigned int width, unsigned int height, std::string title);
	virtual ~Engine();
};

