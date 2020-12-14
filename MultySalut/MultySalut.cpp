// MultySalut.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "MultySalut.h"
#include "salut.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

salut theSalut;									// статический объект "Салют"

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MULTYSALUT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MULTYSALUT));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MULTYSALUT));
	wcex.hCursor = LoadCursor(NULL, IDC_HAND);// IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(0);// COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MULTYSALUT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

POINT pt;
const unsigned int TIMER_SEC = 1; // идентификатор таймера
//Своя функция рисования
void MyDraw(HDC hdc){
	theSalut.drawSelf(hdc, startsSize);		//отрисовка салюта
	theSalut.cleaner();						//очистка списка залпов от догоревших звёзд

	//Для контроля функции очистка
	TCHAR qVolley[64];																			//создание буфера
	int qVolleySize = wsprintf(qVolley, _T("Залпов сейчас - %d"), theSalut.getQuantVolley());	//получение количества активных залпов
	TextOut(hdc, 30, 30, qVolley, qVolleySize);													//контрольный вывод
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static RECT Rect;
	static LOGBRUSH br;
	static HBRUSH brush;

	switch (message){
		case WM_CREATE:
			br.lbStyle = BS_SOLID;				//создание кисти для бэкграунда
			br.lbColor = 0x550000;				//-----"-------
			brush = CreateBrushIndirect(&br);	//-----"-------
			SetTimer(hWnd, TIMER_SEC, 60, NULL);// интервал 0.06 секунды - частота обновления рисунка
			break;
		case WM_LBUTTONUP:
			GetCursorPos(&pt);					//определение позиции курсора
			ScreenToClient(hWnd, &pt);			//Привязка курсора к текущему окну
			theSalut.addVolley(pt.x, pt.y);		//при каждом клике левой кнопкой мышки создаётся новый залп
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Разобрать выбор в меню:
			switch (wmId){
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_TIMER:					// обработка сообщения WM_TIMER
			InvalidateRect(hWnd, NULL, TRUE);  //вызов события WM_PAINT
			break;	
		case WM_PAINT:
			GetClientRect(hWnd, &Rect);					//получить координаты главного окна
			hdc = BeginPaint(hWnd, &ps);				//заполнить структуру для рисования и возвращает дескриптор контекста устройства отображения для заданного окна
			SelectObject(hdc, GetStockObject(DC_PEN));	//выбираем для установки цвета обводку
			SetDCPenColor(hdc, RGB(255, 255, 255));		//устанавливаем цвет обводки
			FillRect(hdc, &Rect, brush);				//заливаем окно цветом бэкграунда, стирая всё что там было
			MyDraw(hdc);								//вызываем свою функцию рисования
			EndPaint(hWnd, &ps);						//завершаем рисование
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
