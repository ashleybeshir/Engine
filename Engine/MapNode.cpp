#include "MapNode.h"



std::vector<Entity*> MapNode::GetEntityForLvl()
{
	if (!LvLEntities.empty()) 
	{
		if (LvLEntities.size() >= CurrentLevel ) 
		{
			return LvLEntities[CurrentLevel];
		}else return{};
	}else return{};
}

std::vector<Entity*> MapNode::GetEntityForLvl(int lvl)
{
	if (!LvLEntities.empty())
	{
		if (LvLEntities.size() >= lvl)
		{
			return LvLEntities[lvl];
		}
		else return{};
	}
	else return{};
}

MapNode::MapNode()
{
}


MapNode::~MapNode()
{
}
