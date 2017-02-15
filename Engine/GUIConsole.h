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
	Console(float x,float y,int loglimit):x(x),y(y),LogLimit(loglimit)
	{
		type = GUITYPE::console;
		size_y = 24 * loglimit;
		shape.setSize(sf::Vector2f(size_x,size_y));
		shape.setFillColor(sf::Color(156,156,156,35));
		log.resize(LogLimit);
		for (size_t i = 0; i < log.size(); i++)
		{
			log[i].setFont(AssetsManager::GetInstance()->GetFont());
			log[i].setCharacterSize(24);
			log[i].setFillColor(sf::Color::White);
		}
		size_y = 24 * loglimit;
	}
	void AddLog(const std::string string)
	{
		for (int i = 0; i <log.size();i++) 
		{
			if (i+1 != log.size()) 
			{
				log[i].setString(log[i + 1].getString());
			}
			else
			{
				log[log.size() - 1].setString(string);
			}
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
	~Console()
	{
		delete this;
	}
};

#endif // !_GUICONSOLE_


