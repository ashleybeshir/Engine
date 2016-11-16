#pragma once
#ifndef _WORLDSTATE_
#define _WORLDSTATE_

#include <vector>
#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Terrain.h"
#include "PlayState.h"

class WorldState : public GameState
{
	int seed;
	std::vector<std::vector<TerrainType>> Terrain;
	sf::VertexArray GTerrain;
	sf::View view;
	
	sf::VertexArray Gplayer;
	sf::Vector2i player;
public:
	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);

	WorldState(int seed);
	WorldState();
	~WorldState();
};


#endif // !_WORLDSTATE_





