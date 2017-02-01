#ifndef _WIDGET_
#define _WIDGET_
#pragma once
#include "GUI.h"
#include <SFML\Graphics.hpp>

struct Widget : public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states){}
	virtual bool check(int x,int y) {}
	virtual sf::String const* clicked(int x,int y){} //might get a pointer error 
	
};


#endif // !_WIDGET_



