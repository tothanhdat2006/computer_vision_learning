#include "Frame.h"

namespace UI
{
	Frame::Frame(sf::Vector2f framePos, sf::Vector2f frameSize, sf::Color frameColor)
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

    void Frame::draw(sf::RenderWindow& window)
    {
        sf::RectangleShape rectangle(sf::Vector2f(frameSize.x, frameSize.y));
        rectangle.setFillColor(frameColor);
		rectangle.setPosition(sf::Vector2f(framePos.x, framePos.y));
		rectangle.setOutlineThickness(1);
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