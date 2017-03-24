
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
#include "EndState.h"


typedef std::tuple<int, int> turn;
class PlayState : public GameState
{
	MapNode* DungeonNode;
	Entity* player;
	TileMap map;
	sf::View view;
	sf::Sound sound;
	MenuList* list;
	Label* PHealth;
	Label* PArmor;
	Label* PDamage;
	Console* console;
	bool input;
	bool _list{false};
	bool wear{ false }, drop{ false }, drink{ false };
	std::vector<turn> potion_turns;
public:

	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);

	void ResetGraphics();

	PlayState();
	PlayState(GenerationType type ,int seed);
	PlayState(MapNode* node);
	~PlayState();
	
};



#endif // !_PLAYSTATE_


