#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "MenuState.h"


void main()
{
	Engine engine;

	engine.Start();
	engine.PushState(new MenuState);

	while (engine.window.isOpen())
	{
		engine.Run();
		engine.Input();
		engine.Draw();
	}
}