#ifndef _MENUSTATE_
#define _MENUSTATE_

#pragma once

#include <iostream>
#include "GameState.h"

class MenuState : public GameState
{
public:
	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);

	MenuState();
	~MenuState();
};



#endif // !_MENUSTATE_


