#include "VolumeState.h"

VolumeState::VolumeState()
{
	this->backButton = new Button(400, 450, 150, 50, "Back");
	this->backButton->setStyle(Text::Italic);

	this->confirmButton = new Button(600, 450, 200, 50, "Confirm");
	this->confirmButton->setStyle(Text::Italic);

	table.setPosition(300, 200);
	table.setSize(Vector2f(640, 230));
	table.setFillColor(Color(120, 120, 120, 168));

	this->gameSlider = new Slider(600, 250);
	this->gameSlider->setRange(0, 100);
	this->gameSlider->setSliderValue(100);
	this->gameSlider->setColors(Color(254, 248, 55), Color(237, 147, 55));

	this->effectSlider = new Slider(600, 340);
	this->effectSlider->setRange(0, 100);
	this->effectSlider->setSliderValue(100);
	this->effectSlider->setColors(Color(254, 248, 55), Color(237, 147, 55));

	this->gameSubtitle = new Subtitle("Game sound:", Vector2f(350, 230));
	this->gameSubtitle->setOutlines(Color::Black, 2);
	this->gameSubtitle->setStyle(Text::Italic);

	this->effectSubtitle = new Subtitle("Effects sound:", Vector2f(350, 320));
	this->effectSubtitle->setOutlines(Color::Black, 2);
	this->effectSubtitle->setStyle(Text::Italic);

}

VolumeState::~VolumeState()
{
	delete this->backButton;
	delete this->confirmButton;
	delete this->gameSlider;
	delete this->effectSlider;
	delete this->gameSubtitle;
	delete this->effectSubtitle;
}

void VolumeState::handleInput()
{
	sf::Event event;
	sf::Vector2f position = Vector2f(Mouse::getPosition(*this->window));

	while (this->window->pollEvent(event))
	{
		if (this->isCheck)
		{
			this->previousSound = this->effectSlider->getSliderValue();
			this->previousMusic = this->gameSlider->getSliderValue();
			this->isCheck = false;
		}
		this->gameSlider->update(position, event);
		this->effectSlider->update(position, event);
		this->confirmButton->update(position, event);
		this->backButton->update(position, event);

		this->soundtrack->getSoundHov().setVolume(this->effectSlider->getSliderValue());
		this->soundtrack->getSoundClicked().setVolume(this->effectSlider->getSliderValue());
		this->soundtrack->getMusic().setVolume(this->gameSlider->getSliderValue());

		if (event.type == Event::Closed)
		{
			this->soundtrack->getSoundClicked().play();
			appStates = AppStates::GOODBYE;
		}
		else if (this->manager.isShapeLeftClicked(this->confirmButton->getButton(), event, position))
		{
			appStates = AppStates::SETTINGS;
			this->isCheck = true;
		}
		else if (this->manager.isShapeLeftClicked(this->backButton->getButton(), event, position) 
			|| Keyboard::isKeyPressed(Keyboard::Escape))
		{
			this->effectSlider->setSliderValue((int)this->previousSound);
			this->gameSlider->setSliderValue((int)this->previousMusic);
			this->soundtrack->getSoundHov().setVolume(this->previousSound);
			this->soundtrack->getSoundClicked().setVolume(this->previousSound);
			this->soundtrack->getMusic().setVolume(this->previousMusic);
			this->isCheck = true;

			appStates = AppStates::SETTINGS;
		}
	}
}

void VolumeState::init(sf::RenderWindow* window)
{
	this->window = window;
}

void VolumeState::initMusic(Soundtrack* soundtrack)
{
	this->soundtrack = soundtrack;
	this->backButton->initMusic(this->soundtrack);
	this->confirmButton->initMusic(this->soundtrack);
	this->spriteSettings->initMusic(this->soundtrack);
}

void VolumeState::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(table, states);
	this->gameSlider->render(*this->window);
	this->effectSlider->render(*this->window);
	this->gameSubtitle->render(*this->window);
	this->effectSubtitle->render(*this->window);
	this->confirmButton->render(&target);
	this->backButton->render(&target);
}