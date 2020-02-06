#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Soundtrack.h"

using namespace sf;

enum SpriteStates { SP_ID = 0, SP_HOV = 1, SP_ACTIVE = 2 };

class SpriteClicker
{
private:
	Soundtrack* soundtrack;

	Texture texture[3];
	Sprite sprite[3];

	int spriteState{ SP_ID };
	int which {};

	bool hoverOnce{ true };
public:
	// Constructors
	SpriteClicker() = delete;
	SpriteClicker(float x, float y, std::string spriteName, std::string spriteName2 = "", std::string spriteName3 = "");
	~SpriteClicker() = default;

	// Methods
	int update(Vector2f & pos, Event & event);
	void setWhich(int which);
	Sprite getSprite();
	void initMusic(Soundtrack* soundtrack);

	// Print
	void render(RenderTarget * target) const;
};

