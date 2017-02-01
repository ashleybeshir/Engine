#ifndef _GUILIST_
#define _GUILIST_
#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include "GUIButton.h"
#include "Widget.h"

struct MenuList : public Widget
{
	std::vector<Button*> list;
	sf::RectangleShape shape;
	Button* left, *right;
	float x, y;
	int size_x, size_y;
	int limit_y,currentpage;
	MenuList(float x,float y,int limit_y) 
	{

	}
	void AddButton(Button* button) 
	{
		list.push_back(button);
	}
	void RefreshGraphics()
	{
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) override
	{
		target.draw(shape);
		for (auto& e : list) 
		{
			e->draw(target,states);
		}
	}
	sf::String const* clicked(int x, int y) override
	{
		for (auto& e : list)
		{
			if (e->clicked(x,y) != nullptr) 
			{
				return e->clicked(x,y);
			}
		}
	}
};

#endif // !_GUILIST_


