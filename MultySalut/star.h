#pragma once
#define PI 3.14159265358
#define TAIL 30

const int qStartsInVolley = 12;
const int startsSize = 12;

class star
{
	int qPoints;
	float shaftLong;
	float dAngle;
	float xTail[TAIL];
	float yTail[TAIL];
	int r, g, b;
public:
	star();
	star(int qP, float sL);
	~star();
	void setTails();
	void setPar(int qP, float sL, int, int, int);
	void drawSelf(HDC hdc, float x, float y, float size);
};

