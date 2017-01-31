#ifndef _GUILABEL_
#define _GUILABEL_
#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Widget.h"
#include "AssetsManager.h"

struct Label : public Widget
{
	float x, y;
	int pos_x, pos_y;
	sf::Text text;
	Label(float x,float y,int pos_x,int pos_y,const std::string string,sf::Color color) 
	{
		text.setFont(*AssetsManager::GetInstance()->GetFont());
		text.setString(string);
		text.setCharacterSize(24); 
		text.setColor(color);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) override
	{
		target.draw(text);
	}
};

#endif // !_GUILABEL_

