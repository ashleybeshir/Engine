#ifndef _GUICONSOLE_
#define _GUICONSOLE_
#pragma once
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
#include "AssetsManager.h"
#include "Widget.h"

struct Console : public Widget
{
	std::vector<sf::Text> log;
	sf::Color color;
	sf::RectangleShape shape;
	float opacity;
	int LogLimit{5};
	float x, y;
	int size_x{300}, size_y{ 100 };
	Console(float x,float y):x(x),y(y)
	{
		type = GUITYPE::console;
		shape.setSize(sf::Vector2f(size_x,size_y));
		shape.setFillColor(sf::Color(156,156,156,20));
	}
	void AddLog(const std::string string)
	{
		if (log.size() > LogLimit)
		{
			log.erase(log.begin() + 0);
			sf::Text text;
			text.setFont(AssetsManager::GetInstance()->GetFont());
			text.setString(string);
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			text.setPosition(shape.getPosition().x + 5, 3 + (shape.getPosition().y + size_y - 24) - log.size() * 14);
			log.push_back(text);
		}
		else
		{
			sf::Text text;
			text.setFont(AssetsManager::GetInstance()->GetFont());
			text.setString(string);
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			text.setPosition(shape.getPosition().x + 5, 3 + (shape.getPosition().y + size_y - 24) - log.size() * 14);
			log.push_back(text);
		}
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);
		for (auto& a : log) 
		{
			target.draw(a);
		}
	}
};

#endif // !_GUICONSOLE_


