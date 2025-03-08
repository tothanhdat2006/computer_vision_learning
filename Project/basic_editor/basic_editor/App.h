#pragma once
#include <SFML/Graphics.hpp>

#include "drawSkeleton.h"
#include "Images.h"
#include "Frame.h"
#include "Textbox.h"
#include "Button.h"

class App
{
private:
	unsigned int windowWidth;
	unsigned int windowHeight;
	sf::VideoMode vm;
	sf::RenderWindow* window;
	
	Images* images;
	UI::Frame* frames;
	UI::Button* buttons;
	UI::Textbox* textboxes;

	void initWindow();
	void initImages();
	void initButtons();
	void initTextboxs();
	void initFrames();

	void pollEvents();

	void updating();
	void rendering();
public:
	App();
	~App();
	void running();
};