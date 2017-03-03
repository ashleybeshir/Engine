#ifndef _MAPNODE_
#define _MAPNODE_

#pragma once

#include <random>
#include <vector>
#include <memory>
//#include "Tilemap.h"
#include "Entity.h"
#include "Terrain.h"
#include "Item.h"
#include <map>

struct ItemBag
{
	ItemBag(Item* _items,sf::Vector2i loc)
	{
		items = _items;
		location = loc;
	}
	Item* items;
	sf::Vector2i location;
};
class MapNode
{
	GenerationType type;
	std::vector<std::vector<Entity*>>  LvLEntities;
	std::vector<std::vector<ItemBag>> LvlItems;
	bool completed{false};
	int Seed;
	int CurrentLevel{0};
	int NumberOfLevels{0};
public:
	int GetNumberOfLevels() { return NumberOfLevels; }
	int GetSeed() { return Seed; }
	void SetSeed(int seed) { Seed = seed; }
	void SetLevel(int lvl) { CurrentLevel = lvl; }
	int GetLevel() { return CurrentLevel; }
	std::vector<Entity*>& GetEntityForLvl();
	std::vector<Entity*>& GetEntityForLvl(int lvl);
	std::vector<ItemBag>& GetItemForLvl();
	std::vector<ItemBag>& GetItemForLvl(int lvl);
	GenerationType GetType() { return type; }
	MapNode();
	MapNode(int seed,GenerationType type,int numberoflevels):Seed(seed),type(type),NumberOfLevels(numberoflevels)
	{
		LvLEntities.resize(numberoflevels);
		LvlItems.resize(numberoflevels);
	}
	~MapNode();
};

#endif // !1