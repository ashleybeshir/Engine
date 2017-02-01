#ifndef _WIDGET_
#define _WIDGET_
#pragma once
#include "GUI.h"
#include <SFML\Graphics.hpp>

struct Widget : public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states){}
	virtual bool check(int x,int y) {}
	virtual bool clicked(int x,int y){}
	guitype type;
};


#endif // !_WIDGET_



