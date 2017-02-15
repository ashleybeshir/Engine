#ifndef _ITEMMANAGER_
#define _ITEMMANAGER_
#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include "Item.h"
#include "MapNode.h"

class ItemManager : public sf::Drawable
{
	MapNode* node;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(auto& c : node->GetItemForLvl())
		{
			target.draw(c);
		}
	}
	Item* GetItem(int x,int y) 
	{
		for (auto& c : node->GetItemForLvl())
		{
			if () 
			{

			}
		}
	}
}
#endif // !_ITEMMANAGER_


