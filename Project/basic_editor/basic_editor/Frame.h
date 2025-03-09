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
		sf::Vector2f framePos;
		sf::Vector2f frameSize;
		sf::Color frameColor;
		Button* buttons;
		Textbox* textboxes;
		Images* images;
		void initComponents();
	public:
		Frame(sf::Vector2f framePos, sf::Vector2f frameSize, sf::Color frameColor);
		~Frame();

		void draw(sf::RenderWindow& window);
		Button* getAllButtons();
		Textbox* getAllTextboxes();
		Images* getAllImages();
	};
}