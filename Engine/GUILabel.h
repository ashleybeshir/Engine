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
	Label(float x,float y,const std::string string,sf::Color color) : x(x),y(y)
	{
		type = GUITYPE::label;
		text.setFont(AssetsManager::GetInstance()->GetFont());
		text.setString(string);
		text.setCharacterSize(24); 
		text.setFillColor(color);
		
	}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text);
	}
	void SetText(sf::String string)
	{
		text.setString(string);
	}
	
	~Label()
	{
		delete this;
	}
};

#endif // !_GUILABEL_

