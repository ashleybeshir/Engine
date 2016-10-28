#include "GameState.h"



void GameState::ChangeState(Engine * engine, GameState * State)
{
	engine->ChangeState(State);
}

GameState::GameState()
{
}


GameState::~GameState()
{
}
