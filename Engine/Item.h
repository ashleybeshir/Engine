#ifndef _ITEM_
#define _ITEM_

#pragma once
#include <SFML\Graphics.hpp>

enum ItemType
{
	Item = 0,
	Potion,
	Weapon,
	Armor
};

struct Item
{
	sf::String name;
	ItemType Type;

};

struct Potion : public Item 
{
	int Heal,Damage;
};

struct Armor : public Item
{
	kjhkjj 
	Type{ ItemType::Armor };
};

struct Weapon : public Item
{
	
};

#endif // !_ITEM_


