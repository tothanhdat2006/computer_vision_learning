#pragma once
#include <SFML/Graphics.hpp>

namespace UI
{
	class Button
	{
	private:
		sf::Vector2f buttonPos;
		sf::Vector2f buttonSize;
		sf::Color buttonColor;
		sf::Text buttonText;
		sf::Font buttonFont;
		void initContent();
	public:
		Button(sf::Vector2f buttonPos, sf::Vector2f buttonSize);
		~Button();
		void draw(sf::RenderWindow& window);
		std::string getText();
		void setColor(sf::Color color);
		void setText(std::string text);
		void setFont(sf::Font font);
	};
}