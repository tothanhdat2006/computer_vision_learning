#include "Frame.h"

namespace UI
{
	Frame::Frame(sf::Vector2u framePos, sf::Vector2u frameSize, sf::Color frameColor)
	{
		this->framePos = framePos;
		this->frameSize = frameSize;
		this->frameColor = frameColor;
		initComponents();
	}

	Frame::~Frame()
	{
		delete[] buttons;
		delete[] textboxes;
		delete[] images;
	}

	void Frame::initComponents()
	{
		buttons = nullptr;
		textboxes = nullptr;
		images = nullptr;
	}

    void Frame::drawFrame(sf::RenderWindow& window, unsigned int x, unsigned int y)
    {
        sf::RectangleShape rectangle(sf::Vector2f(frameSize.x, frameSize.y));
        rectangle.setFillColor(frameColor);
		rectangle.setPosition({ x + framePos.x, y + framePos.y });
        window.draw(rectangle);
    }

	Button* Frame::getAllButtons()
	{
		return buttons;
	}

	Textbox* Frame::getAllTextboxes()
	{
		return textboxes;
	}

	Images* Frame::getAllImages()
	{
		return images;
	}
}