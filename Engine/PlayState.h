
#ifndef _PLAYSTATE_
#define _PLAYSTATE_

#pragma once

#include <vector>
#include <string>
#include "GameState.h"
#include "Entity.h"
#include "Terrain.h"
#include "Tilemap.h"
#include "Components.h"
#include "AssetsManager.h"


class PlayState : public GameState
{
	
	std::vector<std::unique_ptr<Entity>> Entities;
	Entity* player;
	TileMap map;
	sf::View view;
	int seed;
	int Clvl{0};
	bool input;
public:

	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);

	PlayState();
	PlayState(GenerationType type ,int seed);
	~PlayState();
	void AddEntity(Entity* entity);
};



#endif // !_PLAYSTATE_


