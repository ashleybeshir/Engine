#ifndef _GUIINPUT_
#define _GUIINPUT_
#pragma once

#include <SFML\Graphics.hpp>
#include "Widget.h"
#include "AssetsManager.h"

struct TextInput : Widget
{

	float x, y;
	int size_x{300}, size_y{30};
	sf::RectangleShape shape;
	sf::Text text;
	TextInput(float x,float y) : x(x),y(y)
	{
		type = GUITYPE::input;
		text.setFont(AssetsManager::GetInstance()->GetFont());
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		shape.setSize(sf::Vector2f(size_x,size_y));
		shape.setFillColor(sf::Color::Black);
		shape.setOutlineThickness(5);
		shape.setOutlineColor(sf::Color(128,128,128));
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);
		target.draw(text);
	}
	sf::String const& GetString() override
	{
		return text.getString();
	}
	void AddToString(char chr)
	{
  		if (text.getString().getSize() < 20 && chr != ' ') {
			sf::String string{ text.getString() };
			string += chr;
			text.setString(string);
		}
	}
	~TextInput()
	{
		delete this;
	}
};

#endif // !_GUIINPUT_



