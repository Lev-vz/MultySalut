#pragma once

#include "star.h"

class volley
{
	star *starArr;
	float *x;
	float *y;
	float *xStep;
	float *yStep;
	int qStars;
	float mult;
	float mulStep;
public:
	volley(int qS, float x, float y);
	~volley();
	void drawSelf(HDC hdc, float);
	bool isStars();
};

