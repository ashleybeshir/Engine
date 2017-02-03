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
	int colortype;
	float x, y;
	int size_x{ 100 }, size_y{100};
	Button(const std::string string,float x,float y)
	{
		type = GUITYPE::button;
		text.setFont(*AssetsManager::GetInstance()->GetFont());
		text.setString(string);
		text.setCharacterSize(24);
		//text.setColor(sf::Color::White);
		text.setFillColor(sf::Color::White);
		//text.setPosition();
		shape.setSize(sf::Vector2f(size_x, size_y));
		shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype)->Normal);
	}
	Button(const std::string string, float x, float y,int _type)
	{
		type = GUITYPE::button;
		colortype = _type;
		text.setFont(*AssetsManager::GetInstance()->GetFont());
		text.setString(string);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		shape.setSize(sf::Vector2f(size_x,size_y));
		shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype)->Normal);
	}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);
		target.draw(text);
	}
	bool check(int x,int y) override
	{
		if (x <= x *size_x && x >= size_x * x -size_x && y <= y *size_y && y >= size_y * y - size_y)
		{
			shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype)->InView);
			return true;
		}
		else
		{
			shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype)->Normal);
			return false;
		}
	}
	sf::String const* clicked(int x,int y) override
	{
		
		if (x <= shape.getPosition().x + size_x && x >= shape.getPosition().x && y <= shape.getPosition().y + size_y && y >= shape.getPosition().y)
		{
			shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype)->Clicked);
			return & text.getString();
		}
		else
		{
			shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype)->Normal);
			return nullptr;
		}
	}
};

#endif // !1


