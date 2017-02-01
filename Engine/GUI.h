#ifndef _GUI_
#define _GUI_

#pragma once
#include <map>
#include <SFML\Graphics.hpp>
#include <string>
#include "Widget.h"


class GUI
{
	std::map<std::string, Widget*> widgets;
	int Res_x, Res_y;
public:
	void AddWidget(const std::string string, Widget* widget);
	Widget* GetWidget(const std::string string);
	//Widget* GetButtom
	void draw(sf::RenderWindow * window) 
	{
		for (auto& e : widgets) 
		{
			window->draw(*e.second);
		}
	}
	void check(int x,int y) 
	{
		for (auto& e : widgets) 
		{
			e.second->check(x,y);
		}
	}
	sf::String const* clicked(int x,int y) 
	{
		for (auto& e : widgets) 
		{
			if(e.second->clicked(x,y) != nullptr)
			{
				return e.second->clicked(x, y);
			}
		}
	}
	GUI();
	~GUI();
};

#endif // _GUI_




