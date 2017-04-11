#ifndef _COMPONENTS_
#define _COMPONENTS_
#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include "Item.h"
#include "Entity.h"

struct PositionC : public Component
{
	PositionC(int x, int y) 
	{
		Position.x = x;
		Position.y = y;
	}
	sf::Vector2i Position;
};

struct GraphicC : public Component
{
	GraphicC()
	{
	}
	sf::Sprite sprite;
	
};
struct DirectionC : public Component
{
	sf::Vector2i direction{ 0,0 };
};

struct EnergyC : public Component
{
	EnergyC(int energy)
	{
		Energy = energy;
	}
	int Energy;
};
struct PathC : public Component
{
	PathC() 
	{
		path = "";
	}
	std::string path;
};
struct NameC : public Component
{
	NameC(std::string name)
	{
		this->name = name;
	}
	std::string name;
};
struct DamageC : public Component
{
	DamageC(int damage) 
	{
		this->damage = damage;
	}
	int damage{0};
};
struct HealthC : public Component
{
	HealthC(int health)
	{
		this->health = health;
	}
	int health;
	int maxHealth{100};
};
struct ManaC : public Component
{
	ManaC(int mana): mana(mana)
	{

	}
	int mana;
	int maxMana{100};
};
struct LevelC : public Component
{
	LevelC(int lvl):lvl(lvl)
	{
		kill_required = kill_required + lvl * 3  + 3;
	}
	int lvl;
	int kill_count{0};
	int kill_required{ 0 };
};
struct InventoryC : public Component 
{
	InventoryC(std::vector<Item*>& inventory)
	{
		this->inventory = inventory;
		armor = nullptr;
		hand = nullptr;
	}
	InventoryC(){}
	std::vector<Item*> inventory;
	Item* hand{nullptr};
	Item* armor{nullptr};
};
#endif // !_COMPONENTS_


