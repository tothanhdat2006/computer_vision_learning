#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

class WorkingSpace
{
private:
public:
	WorkingSpace();
	~WorkingSpace();
	void drawWorkingSpace(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight);
};

