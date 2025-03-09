#pragma once
#include <SFML/Graphics.hpp>

namespace UI
{
	class Textbox
	{
	private:
		sf::Vector2f textboxPos;
		sf::Vector2f textboxSize;
		sf::Color textboxColor;
		sf::Text textboxText;
		sf::Font textboxFont;
		void initContent();
	public:
		Textbox(sf::Vector2f textboxPos, sf::Vector2f textboxSize);
		~Textbox();
		void draw(sf::RenderWindow& window);
	};
}