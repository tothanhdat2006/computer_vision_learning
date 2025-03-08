#include "App.h"
#include "drawSkeleton.h"
#include "Images.h"

void App::initWindow()
{
	windowWidth = 1000;
	windowHeight = 1000;
	vm = sf::VideoMode({ windowWidth, windowHeight });
	window = new sf::RenderWindow(vm, "Basic editor app");
	window->setFramerateLimit(60);
}

void App::initImages()
{
	images = new Images({ windowWidth, windowHeight });
}

void App::initButtons()
{
	// Sample code to create a button
	buttons = new UI::Button({ 0, 0 }, { 100, 100 }, sf::Color::White);
}

void App::initTextboxs()
{
	// Sample code to create a textbox
	textboxes = new UI::Textbox({ 0, 0 }, { 100, 100 }, sf::Color::White);
}

void App::initFrames()
{
	// Sample code to create a frame
	frame = new UI::Frame({ 0, 0 }, { 100, 100 }, sf::Color::White, nullptr, nullptr, images);
}

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
	}
}

void App::updating()
{
	pollEvents();

	// Sample code to draw a checkerboard pattern
	for (unsigned int y = 0; y < windowHeight; y++)
	{
		for (unsigned int x = 0; x < windowWidth; x++)
		{
			std::uint8_t c = (x & y) ^ x; 
			c *= 255;
			sf::Color color = sf::Color(c, c, c);

			images->setPixel({ x, y }, color);
		}
	}
	images->updateTexture();
}

void App::rendering()
{
	window->clear();
	window->draw(images->getSprite());
	window->display();
}

void App::running()
{
	while (window->isOpen())
	{
		updating();
		rendering();
	}
}

App::App()
{
	initWindow();
	initImages();
}

App::~App()
{
	delete window;
	delete images;
}