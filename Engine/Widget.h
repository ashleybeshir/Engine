#ifndef _WIDGET_
#define _WIDGET_
#pragma once
#include "GUI.h"
#include <SFML\Graphics.hpp>

enum class GUITYPE
{
	button,
	label,
	console
};

struct Widget : public sf::Drawable
{
	GUITYPE type;
	
	virtual bool check(int x, int y) { return false; }
	virtual sf::String const* clicked(int x, int y) { return nullptr; } //might get a pointer error 
	
};


#endif // !_WIDGET_



