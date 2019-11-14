#include "Field.h"

Field::Field()
{
	field.setSize(Vector2f(30, 30));
	field.setOutlineThickness(1);
	field.setOutlineColor(Color::Black);
}

Field::Field(float x, float y, bool isPrint, float width, float height, int value)
{
	this->field.setPosition(x, y);
	this->field.setSize(Vector2f(width, height));
	this->field.setFillColor(Color::White);
	this->value = value;
	this->isPrint = isPrint;
}

int Field::update(Vector2f& pos, Event& event, Ship** ship)
{
	if (beOnce)
	{
		if (!(marked || shutdown))
		{
			fieldState = FIELD_ID;

			if (field.getGlobalBounds().contains(pos.x, pos.y))
			{
				fieldState = FIELD_HOV;

				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				{
					fieldState = FIELD_ACTIVE;
					if (value == 1)
						shutdown = true;
					else if (value == 0)
						marked = true;
				}
			}

			switch (fieldState)
			{
			case FIELD_ID:
				field.setFillColor(Color::White);
				break;
			case FIELD_HOV:
				field.setFillColor(Color(162, 162, 162));
				break;
			case FIELD_ACTIVE:
				field.setFillColor(Color::Red);
				break;
			default:
				field.setFillColor(Color::Magenta);
			}
		}
		if (shutdown)
		{
			field.setFillColor(Color::Cyan);
			for (int i = 0; i < 10; i++)
				if (ship[i]->getShip().getGlobalBounds().intersects(this->field.getGlobalBounds()))
					ship[i]->subtractFieldToShoot();
			value = 2;
			beOnce = false;
			return 2;
		}
		else if (marked)
		{
			field.setFillColor(Color(162, 162, 162));
			value = 3;
			beOnce = false;
			return 1;
		}
	}
	return 0;
}

void Field::setMarked()
{
	beOnce = false;
	field.setFillColor(Color(162, 162, 162));
	value = 3;
}


void Field::setPosition(float x, float y)
{
	field.setPosition(x, y);
}

void Field::setValue(int value)
{
	this->value = value;
}

RectangleShape Field::getShape() const
{
	return field;
}

int Field::getValue() const
{
	return this->value;
}

void Field::render(RenderTarget& target) const
{
	if (this->isPrint)
		target.draw(this->field);
}