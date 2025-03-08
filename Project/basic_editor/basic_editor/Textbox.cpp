#include <iostream>

#include "Textbox.h"

namespace UI
{
	Textbox::Textbox(sf::Vector2u textboxPos, sf::Vector2u textboxSize) : textboxText(textboxFont)
	{
		this->textboxPos = textboxPos;
		this->textboxSize = textboxSize;
		initContent();
	}

	Textbox::~Textbox()
	{
	}

	void Textbox::initContent()
	{
		textboxColor = sf::Color::White;
		textboxFont.openFromFile("./fonts/consolas/CONSOLA.ttf");
		textboxText.setFont(textboxFont);
		textboxText.setCharacterSize(24);
		textboxText.setFillColor(sf::Color::Black);
		textboxText.setString("Test button");
	}

	void Textbox::drawTextbox(sf::RenderWindow& window)
	{
		sf::RectangleShape rectangle(sf::Vector2f(textboxSize.x, textboxSize.y));
		rectangle.setFillColor(textboxColor);
		rectangle.setPosition({ textboxPos.x, textboxPos.y });
		window.draw(rectangle);
		window.draw(textboxText);
	}
}