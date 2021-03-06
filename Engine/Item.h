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
	sf::Sprite sprite;
	ITEM::ItemType Type;
	Item(){}
};

struct Potion : public Item
{
	ITEM::PotionType PotionType;
	int amount,turns;
	
	Potion(const sf::String& name, ITEM::PotionType type, int value)
	{
		this->name = name;
		
		//this->value = value;
	}
	Potion()
	{
		Type = ITEM::ItemType::Potion;
	}
	
};

struct Armor : public Item
{
	int protection;
	
	Armor(const sf::String& name, ITEM::ItemType type, int protection)
	{
		Type = type;
		this->protection = protection;
		this->name = name;
	}
	Armor()
	{
		Type = ITEM::ItemType::Armor;

	}
};

struct Weapon : public Item
{
	int damage;
	
	Weapon(const sf::String& name, int damage)
	{
		Type = ITEM::ItemType::Weapon;
		this->damage = damage;
		this->name = name;
	}
	Weapon()
	{
		Type = ITEM::ItemType::Weapon;

	}
};

#endif // !_ITEM_


