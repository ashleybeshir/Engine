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
	int size_x{ Button_X }, size_y{ Button_Y };
	Button(const std::string string,float x,float y) :x(x),y(y)
	{
		type = GUITYPE::button;
		colortype = 0;
		text.setFont(AssetsManager::GetInstance()->GetFont());
		text.setString(string);
		text.setCharacterSize(24);
		//text.setColor(sf::Color::White);
		text.setFillColor(sf::Color::White);
		//text.setPosition();
		
		shape.setSize(sf::Vector2f(size_x, size_y));
		//shape.setPosition(400,400); 
		shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype).Normal);
		//shape.setFillColor(sf::Color::White);
		shape.setOutlineColor(sf::Color(139,139,139));
		shape.setOutlineThickness(3);
	}
	Button(const std::string string, float x, float y,int _type)
	{
		type = GUITYPE::button;
		colortype = _type;
		text.setFont(AssetsManager::GetInstance()->GetFont());
		text.setString(string);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype).Normal);
		shape.setSize(sf::Vector2f(size_x,size_y));
		shape.setOutlineColor(sf::Color(139, 139, 139));
		shape.setOutlineThickness(3);
	}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);
		target.draw(text);
	}
	bool check(int x,int y) override
	{
		if (x <= shape.getPosition().x + size_x && x >= shape.getPosition().x && y <= shape.getPosition().y + size_y && y >= shape.getPosition().y)
		{
			shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype).InView);
			return true;
		}
		else
		{
			shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype).Normal);
			return false;
		}
	}
	bool clicked(int x,int y) override
	{
		
		if (x <= shape.getPosition().x + size_x && x >= shape.getPosition().x && y <= shape.getPosition().y + size_y && y >= shape.getPosition().y)
		{
			shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype).Clicked);
			return true;
		}
		else
		{
			shape.setFillColor(AssetsManager::GetInstance()->GetColorSheet(colortype).Normal);
			return false;
		}
	}
	sf::String const& GetString() override
	{
		return text.getString();
	}
	void SetString(const std::string string) 
	{
		text.setString(string);
		//shape.setSize(sf::Vector2f(string.size() * 5 , shape.getSize().y));
	}
	void ReSize(int x,int y) 
	{
		size_x = x;
		size_y = y;
		shape.setSize(sf::Vector2f(x,y));
	}
	~Button()
	{
		delete this;
	}
};

#endif // !1


