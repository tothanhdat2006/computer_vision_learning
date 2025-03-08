#pragma once
#include <SFML/Graphics.hpp>

namespace UI
{
	class Textbox
	{
	private:
		sf::Vector2u textboxPos;
		sf::Vector2u textboxSize;
		sf::Color textboxColor;
		sf::Text textboxText;
		sf::Font textboxFont;
		void initContent();
	public:
		Textbox(sf::Vector2u textboxPos, sf::Vector2u textboxSize);
		~Textbox();
		void drawTextbox(sf::RenderWindow& window);
	};
}