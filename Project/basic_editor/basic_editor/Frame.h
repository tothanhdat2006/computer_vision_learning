#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Textbox.h"
#include "Images.h"

namespace UI
{
	class Frame
	{
	private:
		sf::Vector2u framePos;
		sf::Vector2u frameSize;
		sf::Color frameColor;
		Button* buttons;
		Textbox* textboxes;
		Images* images;
		void initComponents();
	public:
		Frame(sf::Vector2u framePos, sf::Vector2u frameSize, sf::Color frameColor);
		~Frame();

		void drawFrame(sf::RenderWindow& window, unsigned int x, unsigned int y);
		Button* getAllButtons();
		Textbox* getAllTextboxes();
		Images* getAllImages();
	};
}