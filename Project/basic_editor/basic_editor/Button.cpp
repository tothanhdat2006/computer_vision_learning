#include <iostream>

#include "Button.h"

namespace UI
{
	Button::Button(sf::Vector2f buttonPos, sf::Vector2f buttonSize) : buttonText(buttonFont)
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

	std::string Button::getText()
	{
		return buttonText.getString();
	}

	void Button::setColor(sf::Color color)
	{
		buttonColor = color;
	}

	void Button::setText(std::string text)
	{
		buttonText.setString(text);
	}

	void Button::setFont(sf::Font font)
	{
		buttonFont = font;
	}

	void Button::draw(sf::RenderWindow& window)
	{
		sf::RectangleShape rectangle(sf::Vector2f(buttonSize.x, buttonSize.y));
		rectangle.setFillColor(buttonColor);
		rectangle.setPosition(sf::Vector2f(buttonPos.x, buttonPos.y));
		window.draw(rectangle);
		buttonText.setPosition(sf::Vector2f(buttonPos.x + 10, buttonPos.y + 10));
		window.draw(buttonText);
	}
}

