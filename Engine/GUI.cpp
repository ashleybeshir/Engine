#include "GUI.h"



void GUI::AddWidget(const std::string string, Widget * widget)
{
	if (widget->type == GUITYPE::button)
	{
		Button * button = dynamic_cast<Button*>(widget);
		button->shape.setPosition(Res_x*button->x,Res_y*button->y);
		button->text.setPosition(Res_x*button->x+5, Res_y*button->y);
		widgets[string] = button;
	}else if(widget->type == GUITYPE::console)
	{
		Console* console = dynamic_cast<Console*>(widget);
		console->shape.setPosition(Res_x*console->x,Res_y*console->y);
		widgets[string] = console;
	}
	//widgets[string] = widget;
}



GUI::GUI()
{
	
}


GUI::~GUI()
{
}
