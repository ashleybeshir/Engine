#include "BSP.h"



bool BSP::Split()
{
	if (LeftChild != nullptr || RightChild != nullptr) return false;

	bool splitH{std::rand() > 0.5f};
	if (width > height && width / height >= 1.25)
		splitH = false;
	else if (height > width && height / width >= 1.25)
		splitH = true;

	int max{ (splitH ? height : width) - min_leaf_size };
	
	if (max <= min_leaf_size) return false;

	int split{ rand() % max + min_leaf_size};

	if (splitH)
	{
		LeftChild = new BSP(x, y, width, split);
		RightChild = new BSP(x, y + split, width, height - split);
	}
	else
	{
		LeftChild = new BSP(x, y, split, height);
		RightChild = new BSP(x + split, y, width - split, height);
	}
	return true;
}

void BSP::CreateRooms()
{
	if (LeftChild != nullptr || RightChild != nullptr)
	{	
		if (LeftChild != nullptr) LeftChild->CreateRooms();
		if (RightChild != nullptr) RightChild->CreateRooms();
	}
	else
	{
		sf::Vector2i roomSize;
		sf::Vector2i roomPos;

		roomSize.x = rand() % (width -2) + 3;
		roomSize.y = rand() % (height - 2) + 3;
		
		roomPos.x = rand() % (width - roomSize.x -1) + 1;
		roomPos.y = rand() % (height - roomSize.y - 1) + 1;
		room.setSize(sf::Vector2f(x + roomPos.x, y + roomPos.y));
		room.setSize(sf::Vector2f(roomSize.x, roomSize.y));
	}
}

BSP::BSP()
{
}


BSP::~BSP()
{
}
