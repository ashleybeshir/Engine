#include "WorldState.h"
#include <cstdlib>
#include <ctime>


WorldState::WorldState(int seed)
{
	this->seed = seed;
}

WorldState::WorldState()
{
	seed = std::time(0);
	std::srand(seed);
}


WorldState::~WorldState()
{
}

void WorldState::Start()
{
	Terrain.resize(50);
	for (size_t i = 0; i < Terrain.size(); i++) Terrain[i].resize(50);

	for (size_t x = 0; x < Terrain.size(); x++)
	{
		for (size_t y = 0; y < Terrain[x].size(); y++)
		{
			Terrain[x][y] = (TerrainType)(0 /*min*/ + (rand() % (int)(6/*max*/ - 0 /*min*/ + 1)));
		}
	}
	
}

void WorldState::Delete()
{
}

void WorldState::Pause()
{
}

void WorldState::Resume()
{
}

void WorldState::Run(Engine * engine)
{
}

void WorldState::Input(Engine * engine)
{
}

void WorldState::Draw(Engine * engine)
{
}
