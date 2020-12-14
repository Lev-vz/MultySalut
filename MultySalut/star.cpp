#include "stdafx.h"
#include "star.h"
#include <cmath>
#include <string>
#include <cstdio>

//������� ��������� ������: ���.�����, ������������� ����� �����, ���������� �����
void star::setPar(int qP, float sL, int R, int G, int B){
	qPoints = qP;
	shaftLong = sL;
	dAngle = 2 * PI / qPoints;	//���� ����� ������
	r = R; g = G; b = B;
}
star::star(){
}
star::~star(){
}
//������������� NAN ��������� ������ ������, ����� ��� �� �������������� ������ �������
void star::setTails(){
	for (int i = 0; i < TAIL; i++){
		xTail[i] = NAN;
		yTail[i] = NAN;
	}
}
//��������� ������
void star::drawSelf(HDC hdc, float x, float y, float size){
	POINT *pt = new POINT[qPoints * 2];						//�������� ������� ����� ��� ��������
	for (int i = 0; i < qPoints; i++){						//���� �� ����� - ������ ��������� ������ ����� � ��������� �����
		pt[i * 2].x = size * sin(dAngle * i) + x;							
		pt[i * 2].y = size * cos(dAngle * i) + y;							
		pt[i * 2 + 1].x = size * shaftLong * sin(dAngle * (i + 0.5)) + x;
		pt[i * 2 + 1].y = size * shaftLong * cos(dAngle * (i + 0.5)) + y;
	}
	SelectObject(hdc, GetStockObject(DC_BRUSH));			//��������� ����� ��������� ������
	SetDCBrushColor(hdc, RGB(255, 255, 255));
	for (int i = TAIL - 1; i > 0; i--){						//��������� ������
		float rad = ((float)TAIL - i) / TAIL * size / 2;
		if (xTail[i] != NAN) Ellipse(hdc, xTail[i]-rad, yTail[i]-rad, xTail[i] + rad, yTail[i] + rad); //����� �������� �������� �� ����� ������ � ����������� ����������� (�������� ���� �������� ����������!!!!!!!)
		xTail[i] = xTail[i-1];										//�������� ������
		yTail[i] = yTail[i-1];
	}
	xTail[0] = x;											//���������� ������� ��������� ������ � �����
	yTail[0] = y;
	SetDCBrushColor(hdc, RGB(r,g,b));						//��������� ����� ������
	Polygon(hdc, pt, qPoints * 2);							//��������� ������
	delete[] pt;											//�������� ������� ����� ��������
}