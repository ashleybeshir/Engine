#include "MapNode.h"



std::vector<Entity*>& MapNode::GetEntityForLvl()
{
	return LvLEntities[CurrentLevel];
}

std::vector<Entity*>& MapNode::GetEntityForLvl(int lvl)
{
	return LvLEntities[lvl];
}

std::vector<Item*>& MapNode::GetItemForLvl()
{
	return LvlItems[CurrentLevel];
}

std::vector<Item*>& MapNode::GetItemForLvl(int lvl)
{
	return LvlItems[lvl];
}

MapNode::MapNode()
{
}


MapNode::~MapNode()
{
}
