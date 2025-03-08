#include <iostream>

#include "Button.h"

namespace UI
{
	Button::Button(sf::Vector2u buttonPos, sf::Vector2u buttonSize) : buttonText(buttonFont)
	{
		this->buttonPos = buttonPos;
		this->buttonSize = buttonSize;
		initContent();
	}

	Button::~Button()
	{

	}

	void Button::initContent()
	{
		buttonColor = sf::Color::White;
		buttonText.setString("");
		buttonText.setFont(buttonFont);
		buttonText.setCharacterSize(24);
		buttonText.setFillColor(sf::Color::Black);
	}

	void Button::drawButton(sf::RenderWindow& window, unsigned int x, unsigned int y)
	{
		sf::RectangleShape rectangle(sf::Vector2f(buttonSize.x, buttonSize.y));
		rectangle.setFillColor(buttonColor);
		rectangle.setPosition({ x + buttonPos.x, y + buttonPos.y });
		window.draw(rectangle);
		buttonText.setPosition({ x + buttonPos.x + 10, y + buttonPos.y + 10 });
		window.draw(buttonText);
	}
}

