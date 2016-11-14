#ifndef _ITEM_
#define _ITEM_

#pragma once
#include <SFML\Graphics.hpp>

namespace ITEM {
	enum ItemType
	{
		Item = 0,
		Potion,
		Weapon,
		Armor
	};
	enum PotionType
	{
		Health = 0,
		Damage,
		Mana,
		Health_Mana
	};
}

struct Item
{
	sf::String name;
	ITEM::ItemType Type;
};

struct Potion : public Item 
{
	ITEM::PotionType PotionType;
	int value;
	Potion(const sf::String& name, ITEM::PotionType type, int value)
	{
		this->name = name;
		PotionType = type;
		this->value = value;
	}
};

struct Armor : public Item
{
	int protection;
	Armor(const sf::String& name, ITEM::ItemType type,int protection)
	{
		Type = type;
		this->protection = protection;
		this->name = name;
	}
};

struct Weapon : public Item
{
	int damage;
	Weapon(const sf::String& name, ITEM::ItemType type, int damage)
	{
		Type = type;
		this->damage = damage;
		this->name = name;
	}

};

#endif // !_ITEM_


