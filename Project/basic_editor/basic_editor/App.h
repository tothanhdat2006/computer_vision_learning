#pragma once
#include <SFML/Graphics.hpp>

#include "drawSkeleton.h"
#include "Images.h"

class App
{
private:
	unsigned int windowWidth;
	unsigned int windowHeight;
	sf::VideoMode vm;
	sf::RenderWindow* window;
	
	Images* images;

	void initWindow();
	void initImages();

	void pollEvents();

	void updating();
	void rendering();
public:
	App();
	~App();
	void running();
};