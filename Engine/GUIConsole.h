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
	int LogLimit;
	float x, y;
	int size_x, size_y;
	void AddLog(const std::string string)
	{
		if (log.size() > LogLimit)
		{
			log.erase(log.begin() + log.size() - 1);
			sf::Text text;
			text.setFont(*AssetsManager::GetInstance()->GetFont());
			text.setString(string);
			text.setCharacterSize(24);
			text.setColor(sf::Color::White);
			log.push_back(text);
		}
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) override
	{
		target.draw(shape);
		for (auto& a : log) 
		{
			target.draw(a);
		}
	}
};

#endif // !_GUICONSOLE_


