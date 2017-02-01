#ifndef _GUI_
#define _GUI_

#pragma once
#include <map>
#include <string>
#include "Widget.h"

enum class guitype
{
	button,
	label,
	menu,
	console,
	input
};
class GUI
{
	std::map<std::string, Widget*> widgets;
	int Res_x, Res_y;
public:
	void AddWidget(const std::string string, Widget* widget);
	Widget* GetWidget(const std::string string);
	//Widget* GetButtom

	GUI();
	~GUI();
};

#endif // _GUI_




