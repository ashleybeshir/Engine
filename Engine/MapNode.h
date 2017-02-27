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


class MapNode
{
	GenerationType type;
	//std::vector<std::vector<std::unique_ptr<Entity>>> LvLEntities;
	std::vector<std::vector<Entity*>>  LvLEntities;
	std::vector<std::vector<Item*>> LvlItems;
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
	std::vector<Item*>& GetItemForLvl();
	std::vector<Item*>& GetItemForLvl(int lvl);
	GenerationType GetType() { return type; }
	MapNode();
	MapNode(int seed,GenerationType type,int numberoflevels):Seed(seed),type(type),NumberOfLevels(numberoflevels)
	{
		LvLEntities.resize(numberoflevels);
	}
	~MapNode();
};

#endif // !1