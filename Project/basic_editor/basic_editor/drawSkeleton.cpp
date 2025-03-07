#include "drawSkeleton.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

void drawWorkingSpace(sf::RenderWindow& window, unsigned int& windowWidth, unsigned int& windowHeight)
{
	sf::RectangleShape workingSpaceShape(sf::Vector2f(windowWidth / 2.0, windowHeight - 250));
	workingSpaceShape.setFillColor(sf::Color::White);
	workingSpaceShape.setPosition({ static_cast<float>(windowWidth) / 4.0f, static_cast<float>(windowHeight - 250) });
	window.draw(workingSpaceShape);
}