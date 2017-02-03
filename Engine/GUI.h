#ifndef _GUI_
#define _GUI_

#pragma once
#include <map>
#include <SFML\Graphics.hpp>
#include <string>
#include "Widget.h"
#include "GUIButton.h"

class GUI
{
	std::map<std::string, Widget*> widgets;
	
	int Res_x, Res_y;
public:
	void AddWidget(const std::string string, Widget* widget);
	template<typename T>
	T* GetWidget(const std::string string)
	{
		return std::dynamic_pointer_cast<T>(widgets[string]);
	}
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
	GUI(int x,int y):Res_x(x),Res_y(y){}
	~GUI();
};

#endif // _GUI_




