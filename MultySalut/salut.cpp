#include "stdafx.h"
#include "salut.h"
//const int superBottom = 1500;

salut::salut(){}


salut::~salut(){
	for (auto vol = salutList.begin(); vol != salutList.end();)	{
		(*vol)->~volley();					//�������� ����������� ���� ������, ����� �������� ������������ ������ �� �������� �����
		vol = salutList.erase(vol);			//���������� ������ ������ �� �����
	}

}
//������� ������ - ���������� �������� ������ ������, � ������� ����� ��������
void salut::cleaner(){
	for (auto vol = salutList.begin(); vol != salutList.end();)	{
		if (!((*vol)->isStars())){
			(*vol)->~volley();
			vol = salutList.erase(vol);
		} else vol++;
	}
}
//��������� � ������ ����� ���� � ��������� ������������
void salut::addVolley(float x, float y){
	volley *vol = new volley(qStartsInVolley, x, y);
	salutList.push_back(vol);
}
//������������ ���� ������ ������
void salut::drawSelf(HDC hdc, float){
	for each (volley *vol in salutList)	{
		vol->drawSelf(hdc, startsSize);
	}
}
//���������� ������� ���������� ������
int salut::getQuantVolley(){
	return salutList.size();
}
