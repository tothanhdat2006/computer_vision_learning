#include <iostream>

#include "App.h"
#include "Images.h"

/*------------------------------Init------------------------------*/
void App::initWindow()
{
	this->windowSize = { 1280, 720 };
	this->vm = sf::VideoMode(this->windowSize);
	window = new sf::RenderWindow(this->vm, "Basic editor app");
	window->setFramerateLimit(24);
}

void App::initImages()
{
	this->images = new Images(this->windowSize);
}

void App::initButtons()
{
	this->buttons = new UI::Button[5]{
		UI::Button({0, 0}, {100, 50}),
		UI::Button({0, 60}, {100, 50}),
		UI::Button({0, 120}, {100, 50}),
		UI::Button({0, 180}, {100, 50}),
		UI::Button({0, 240}, {100, 50})
	};

	sf::Font font;
	font.openFromFile("./fonts/consolas/CONSOLA.TTF");

	for (int i = 0; i < 5; ++i)
	{
		buttons[i].setColor(sf::Color::White);
		buttons[i].setText("Button " + std::to_string(i));
		buttons[i].setFont(font);
	}
}

void App::initTextboxs()
{
	this->textboxes = new UI::Textbox[5]{
		UI::Textbox({0, 300}, {100, 50}),
		UI::Textbox({0, 360}, {100, 50}),
		UI::Textbox({0, 420}, {100, 50}),
		UI::Textbox({0, 480}, {100, 50}),
		UI::Textbox({0, 540}, {100, 50})
	};
}

void App::initFrames()
{
	/*
	UI::Frame 0: Upper bar
	UI::Frame 1: Left tools bar
	UI::Frame 2: Middle working space
	UI::Frame 3: Right properties bar
	UI::Frame 4: Bottom status bar
	*/
	
	this->frames = new UI::Frame[5]{
		UI::Frame({0, 0},
				 {static_cast<float>(this->windowSize.x), static_cast<float>(0.1 * this->windowSize.y)},
				 { 0, 24, 143 }),

		UI::Frame({0, static_cast<float>(0.1 * this->windowSize.y)},
				 {static_cast<float>(0.2 * this->windowSize.x), static_cast<float>(0.8 * this->windowSize.y)},
				 { 0, 24, 143 }),

		UI::Frame({static_cast<float>(0.2 * this->windowSize.x), static_cast<float>(0.1 * this->windowSize.y)},
				 {static_cast<float>(0.6 * this->windowSize.x), static_cast<float>(0.8 * this->windowSize.y)},
				 { 0, 24, 143 }),

		UI::Frame({static_cast<float>(0.8 * this->windowSize.x), static_cast<float>(0.1 * this->windowSize.y)},
				 {static_cast<float>(0.2 * this->windowSize.x), static_cast<float>(0.8 * this->windowSize.y)},
				 { 0, 24, 143 }),

		UI::Frame({0, static_cast<float>(0.9 * this->windowSize.y)},
				 {static_cast<float>(this->windowSize.x), static_cast<float>(0.1 * this->windowSize.y)},
				 { 0, 24, 143 })
	};
}

void App::initUI()
{
	initButtons();
	initTextboxs();
	initFrames();
}

void App::drawUI()
{
	for (int i = 0; i < 5; i++)
	{
		this->frames[i].draw(*(this->window));
		//this->buttons[i].draw(*(this->window));
		//this->textboxes[i].draw(*(this->window));
	}
}


/*------------------------------Events------------------------------*/
void App::pollEvents()
{
	while (const std::optional event = window->pollEvent())
	{
		if(event->is<sf::Event::Closed>())
			window->close();
		else if(const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				window->close();
		}
		else if (const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>())
		{
			std::cout << "Mouse clicked at: " << mouseClicked->position.x << ", " << mouseClicked->position.y << std::endl;
		}

	}
}

void App::updating()
{
	pollEvents();

}

void App::rendering()
{
	this->window->clear();
	drawUI();
	this->window->display();
}

void App::running()
{
	while (this->window->isOpen())
	{
		updating();
		rendering();
	}
}


/*------------------------------Constructor & Destructor------------------------------*/
App::App()
{
	initWindow();
	initImages();
	initUI();
}

App::~App()
{
	delete this->window;
	delete this->images;
	delete[] this->buttons;
	delete[] this->textboxes;
	delete[] this->frames;
}