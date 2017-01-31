#include "GUI.h"



void GUI::AddWidget(const std::string string, Widget * widget)
{
	widgets[string] = widget;
}

Widget * GUI::GetWidget(const std::string string)
{
	return widgets[string];
}

GUI::GUI()
{
}


GUI::~GUI()
{
}
