#include "stdafx.h"
#include "salut.h"
//const int superBottom = 1500;

salut::salut(){}


salut::~salut(){
	for (auto vol = salutList.begin(); vol != salutList.end();)	{
		(*vol)->~volley();					//вызываем деструкторы всех залпов, чтобы очистить динамическую память от объектов залпа
		vol = salutList.erase(vol);			//уничтожаем список ссылок на залпы
	}

}
//сборщик мусора - уничтожает элементы списка залпов, в которых звёзды догорели
void salut::cleaner(){
	for (auto vol = salutList.begin(); vol != salutList.end();)	{
		if (!((*vol)->isStars())){
			(*vol)->~volley();
			vol = salutList.erase(vol);
		} else vol++;
	}
}
//добавляет в список новый залп с заданными координатами
void salut::addVolley(float x, float y){
	volley *vol = new volley(qStartsInVolley, x, y);
	salutList.push_back(vol);
}
//отрисовывает весь список залпов
void salut::drawSelf(HDC hdc, float){
	for each (volley *vol in salutList)	{
		vol->drawSelf(hdc, startsSize);
	}
}
//возвращает текущее количество залпов
int salut::getQuantVolley(){
	return salutList.size();
}
