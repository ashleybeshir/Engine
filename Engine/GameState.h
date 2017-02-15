#ifndef _GAMESTATE_
#define _GAMESTATE_

#pragma once

#include "Engine.h"

class Engine;

class GameState
{
public:
	Engine* engine;
	virtual void Start() = 0;
	virtual void Delete() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;


	virtual void Run(Engine* engine) = 0;
	virtual void Input(Engine* engine)= 0;
	virtual void Draw(Engine* engine)= 0;
	
	void ChangeState(Engine* engine, GameState* State);
	

	GameState();
	~GameState();
};

#endif // _GAMESTATE_