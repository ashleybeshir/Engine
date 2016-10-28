#include <iostream>
#include "Engine.h"
#include "MenuState.h"

void main()
{
	Engine engine;

	engine.PushState(new MenuState);
	while (true)
	{

	}
}