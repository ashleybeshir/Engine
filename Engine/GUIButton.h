#ifndef _GUIBUTTON_
#define _GUIBUTTON_
#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Widget.h"
#include "AssetsManager.h"
struct Button : public Widget
{
	sf::Text text;
	sf::RectangleShape shape;
	sf::Color Normal, InView, Clicked;

	float x, y;
	int size_x, size_y;
	Button(const std::string string,float x,float y,sf::Color normal,sf::Color inview,sf::Color clicked)
	{
		text.setFont(*AssetsManager::GetInstance()->GetFont());
		text.setString(string);
		text.setCharacterSize(24);
		text.setColor(sf::Color::White);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) override
	{
		target.draw(shape);
		target.draw(text);
	}
	bool check(int x,int y) override
	{
		if (x <= x *size_x && x >= size_x * x -size_x && y <= y *size_y && y >= size_y * y - size_y)
		{
			shape.setFillColor(InView);
			return true;
		}
		else
		{
			shape.setFillColor(Normal);
			return false;
		}
	}
	bool clicked(int x,int y) override
	{
		if (x <= x *size_x && x >= size_x * x - size_x && y <= y *size_y && y >= size_y * y - size_y)
		{
			shape.setFillColor(Clicked);
			return true;
		}
		else
		{
			shape.setFillColor(Normal);
			return false;
		}
	}
};

#endif // !1


