#pragma once
#include "volley.h"
#include <list>

class salut
{
	std::list <volley*> salutList;
public:
	salut();
	~salut();
	void addVolley(float x, float y);
	void drawSelf(HDC hdc, float);
	void cleaner();
	int getQuantVolley();
};

