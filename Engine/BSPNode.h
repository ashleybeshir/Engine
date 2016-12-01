#ifndef _BSPNODE_
#define _BSPNODE_

#pragma once

struct BSPNode
{
	int x, y, width, height;
	BSPNode *parent, *leftchild{ nullptr }, *rightchild{nullptr};

	BSPNode(int x,int y,int width,int height,BSPNode* parent):x(x),y(y),parent(parent),width(width),height(height)
	{
	}
	~BSPNode() 
	{
		delete leftchild;
		delete rightchild;
	}
};

#endif // !_BSPNODE_



