#pragma once
#ifndef _PLAYSTATE_
#define _PLAYSTATE_
#pragma

#include <vector>
#include "GameState.h"
#include "Entity.h"
#include "BSP.h"

class PlayState : public GameState
{
	bool Dungeon_Cave; // True for Dungeon. false for cave
	std::vector<std::unique_ptr<Entity>> Entities;
	std::vector<BSP*> bsp;
public:

	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);

	PlayState();
	PlayState(bool type);
	~PlayState();
protected:
	void AddEntity(Entity* entity);
};



#endif // !_PLAYSTATE_


