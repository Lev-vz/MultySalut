#include "stdafx.h"
#include "star.h"
#include <cmath>
#include <string>
#include <cstdio>

//задание парметров звезды: кол.лучей, относительная длина лучей, компоненты цвета
void star::setPar(int qP, float sL, int R, int G, int B){
	qPoints = qP;
	shaftLong = sL;
	dAngle = 2 * PI / qPoints;	//угол между лучами
	r = R; g = G; b = B;
}
star::star(){
}
star::~star(){
}
//инициализация NAN элементов хвоста звезды, чтобы они не отрисовывались раньше времени
void star::setTails(){
	for (int i = 0; i < TAIL; i++){
		xTail[i] = NAN;
		yTail[i] = NAN;
	}
}
//Отрисовка звезды
void star::drawSelf(HDC hdc, float x, float y, float size){
	POINT *pt = new POINT[qPoints * 2];						//создание массива точек для полигона
	for (int i = 0; i < qPoints; i++){						//цикл по лучам - расчёт координат концов лучей и оснований лучей
		pt[i * 2].x = size * sin(dAngle * i) + x;							
		pt[i * 2].y = size * cos(dAngle * i) + y;							
		pt[i * 2 + 1].x = size * shaftLong * sin(dAngle * (i + 0.5)) + x;
		pt[i * 2 + 1].y = size * shaftLong * cos(dAngle * (i + 0.5)) + y;
	}
	SelectObject(hdc, GetStockObject(DC_BRUSH));			//установка цвера отрисовки хвоста
	SetDCBrushColor(hdc, RGB(255, 255, 255));
	for (int i = TAIL - 1; i > 0; i--){						//отрисовка хвоста
		float rad = ((float)TAIL - i) / TAIL * size / 2;
		if (xTail[i] != NAN) Ellipse(hdc, xTail[i]-rad, yTail[i]-rad, xTail[i] + rad, yTail[i] + rad); //хвост рисуется кружками по следу звезды с постепенным уменьшением (возможно надо рисовать полилайном!!!!!!!)
		xTail[i] = xTail[i-1];										//смещение хвоста
		yTail[i] = yTail[i-1];
	}
	xTail[0] = x;											//сохранение текущих координат звезды в хвост
	yTail[0] = y;
	SetDCBrushColor(hdc, RGB(r,g,b));						//установка цвета звезды
	Polygon(hdc, pt, qPoints * 2);							//отрисовка звезды
	delete[] pt;											//удаление массива точек полигона
}