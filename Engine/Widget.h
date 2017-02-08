#ifndef _WIDGET_
#define _WIDGET_
#pragma once
#include "GUI.h"
#include <SFML\Graphics.hpp>

#define Button_X 100
#define Button_Y 25

enum class GUITYPE
{
	button,
	label,
	console,
	list,
	input
};

struct Widget : public sf::Drawable
{
	GUITYPE type;
	
	virtual bool check(int x, int y) { return false; }
	virtual bool clicked(int x, int y) { return false; } //might get a pointer error 
	virtual sf::String const& GetString() { return ""; }
};


#endif // !_WIDGET_



