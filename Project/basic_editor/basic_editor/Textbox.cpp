#include <iostream>

#include "Textbox.h"

namespace UI
{
	Textbox::Textbox(sf::Vector2f textboxPos, sf::Vector2f textboxSize) : textboxText(textboxFont)
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

	void Textbox::draw(sf::RenderWindow& window)
	{
		sf::RectangleShape rectangle(sf::Vector2f(textboxSize.x, textboxSize.y));
		rectangle.setFillColor(textboxColor);
		rectangle.setPosition(sf::Vector2f(textboxPos.x, textboxPos.y));
		window.draw(rectangle);
		window.draw(textboxText);
	}
}