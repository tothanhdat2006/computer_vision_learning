#pragma once
#include <SFML/Graphics.hpp>

namespace UI
{
	class Button
	{
	private:
		sf::Vector2u buttonPos;
		sf::Vector2u buttonSize;
		sf::Color buttonColor;
		sf::Text buttonText;
		sf::Font buttonFont;
		void initContent();
	public:
		Button(sf::Vector2u buttonPos, sf::Vector2u buttonSize);
		~Button();
		void drawButton(sf::RenderWindow& window, unsigned int x, unsigned int y);
	};
}