#pragma once
#include <SFML/Graphics.hpp>

#include "Images.h"
#include "Frame.h"
#include "Textbox.h"
#include "Button.h"

class App
{
private:
	sf::Vector2u windowSize;
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

	void initUI();
	void drawUI();

	void pollEvents();

	void updating();
	void rendering();
public:
	App();
	~App();
	void running();
};