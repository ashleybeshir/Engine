#ifndef _GUILIST_
#define _GUILIST_
#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include "GUIButton.h"
#include "Widget.h"
#include "Item.h"
#include <iostream>

struct MenuList : public Widget
{
	std::vector<sf::String> list;
	std::vector<Button*> buttons;
	std::vector<bool> Bbuttons;
	sf::RectangleShape shape;
	Button* left, *right;
	float x, y;
	int size_x{300}, size_y;
	int limit_y{0}, currentpage{ 0 };
	int selected_button{ 0 };
	MenuList(float x,float y,int limit_y) :x(x),y(y),limit_y(limit_y)
	{
		type = GUITYPE::list;
		size_y = (limit_y+1 )* Button_Y;
		shape.setSize(sf::Vector2f(size_x,size_y));
		//shape.setPosition(size_x,size_y);
		shape.setFillColor(sf::Color::Black);
		left = new Button("Prev",0,0);
		right = new Button("Next",0,0);
		buttons.resize(limit_y);
		Bbuttons.resize(limit_y);
		for (size_t i = 0; i < buttons.size(); i++)
		{
			buttons[i] = new Button("",0,0);
			buttons[i]->ReSize(size_x-10,Button_Y);
		}
		for (size_t i = 0; i < limit_y; i++)
		{
			Bbuttons[i] = false;
		}
	}
	void AddButton(Item& item) 
	{
		list.push_back(item.name);
		RefreshGraphics();
	}
	void AddButton(const sf::String name)
	{
		list.push_back(name);
		RefreshGraphics();
	}
	void RefreshGraphics()
	{
		int temp{ currentpage*limit_y };
		for (int i=0;i < buttons.size();i++) 
		{
			if (temp + i < list.size())
			{
				buttons[i]->SetString(list[temp + i]);
				Bbuttons[i] = true;
				
			}
			else Bbuttons[i] = false;
		}

	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		target.draw(shape);
		left->draw(target,states);
		right->draw(target,states);
		
		for (size_t i = 0; i < buttons.size(); i++)
		{
			if (Bbuttons[i] == true)
			{
				buttons[i]->draw(target,states);
			}
		}

	}
	bool check(int x, int y) override
	{
		left->check(x,y);
		right->check(x,y);
		bool test{ false };
		for (size_t i = 0; i < buttons.size(); i++)
		{
			if (Bbuttons[i] == true)
			{
				if(buttons[i]->check(x,y)) test = true;
			}
		}

		return test;
	}
	bool clicked(int x, int y) override
	{
		if (left->clicked(x,y)) 
		{
			if (currentpage != 0)currentpage -= 1;
			RefreshGraphics();
		}
		else if (right->clicked(x,y)) 
		{
			currentpage += 1;
			RefreshGraphics();
		}
		
		for (size_t i = 0; i < buttons.size(); i++)
		{
			if (Bbuttons[i] == true)
			{
				if (buttons[i]->check(x, y)) { 
					selected_button = i;
					return true; 
				}
			}
		}

		return false;
	}
	sf::String const& GetString() override
	{
		return list[selected_button];
	}
};

#endif // !_GUILIST_


