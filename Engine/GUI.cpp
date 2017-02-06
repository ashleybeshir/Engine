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
		for (size_t i = 0; i < console->log.size(); i++)
		{
			console->log[i].setPosition(Res_x*console->x + 5, Res_y*console->y + (i*24)-24);
		}
		widgets[string] = console;
	}
	else if (widget->type == GUITYPE::list)
	{
		MenuList* list = dynamic_cast<MenuList*>(widget);
		list->shape.setPosition(Res_x*list->x,Res_y*list->y);
		list->left->shape.setPosition(Res_x*list->x, Res_y*list->y+ list->size_y);
		list->left->text.setPosition(Res_x*list->x + 5, Res_y*list->y + list->size_y);
		list->right->shape.setPosition(Res_x*list->x + list->size_x - Button_X , Res_y*list->y + list->size_y);
		list->right->text.setPosition(Res_x*list->x + 5 + list->size_x - Button_X , Res_y*list->y + list->size_y);
		int divider{ 0 };
		for (int i=0;i < list->buttons.size();i++) 
		{
			list->buttons[i]->shape.setPosition(Res_x*list->x + 5 , Res_y*list->y + Button_Y * i + 3 + divider);
			list->buttons[i]->text.setPosition(Res_x*list->x + 10  , Res_y*list->y + Button_Y * i + 3 + divider);
			divider += 2;
		}
		widgets[string] = list;
	}
	//widgets[string] = widget;
}



GUI::GUI()
{
	
}


GUI::~GUI()
{
}
