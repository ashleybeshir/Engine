
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
#include "MapNode.h"


class PlayState : public GameState
{
	MapNode* DungeonNode;
	Entity* player;
	TileMap map;
	sf::View view;
	
	MenuList* list;
	bool input;
	bool _list{false};
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
	PlayState(MapNode* node);
	~PlayState();
	
};



#endif // !_PLAYSTATE_


