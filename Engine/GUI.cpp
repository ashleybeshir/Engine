#include "GUI.h"



void GUI::AddWidget(const std::string string, Widget * widget)
{
	if (widget->type == GUITYPE::button)
	{
		Button * button = dynamic_cast<Button*>(widget);
		button->shape.setPosition(Res_x*button->x,Res_y*button->y);
		button->text.setPosition(Res_x*button->x, Res_y*button->y);
		widgets[string] = button;
	}
	//widgets[string] = widget;
}



GUI::GUI()
{
	
}


GUI::~GUI()
{
}
