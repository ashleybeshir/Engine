#include "MapNode.h"



std::vector<Entity*>* MapNode::GetEntityForLvl()
{
	return &LvLEntities[CurrentLevel];
}

std::vector<Entity*>* MapNode::GetEntityForLvl(int lvl)
{
	return &LvLEntities[lvl];
}

MapNode::MapNode()
{
}


MapNode::~MapNode()
{
}
