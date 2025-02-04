// MultySalut.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "MultySalut.h"
#include "salut.h"

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����

salut theSalut;									// ����������� ������ "�����"

// ��������� ���������� �������, ���������� � ���� ������ ����:
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

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MULTYSALUT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MULTYSALUT));

	// ���� ��������� ���������:
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
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
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
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

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
const unsigned int TIMER_SEC = 1; // ������������� �������
//���� ������� ���������
void MyDraw(HDC hdc){
	theSalut.drawSelf(hdc, startsSize);		//��������� ������
	theSalut.cleaner();						//������� ������ ������ �� ���������� ����

	//��� �������� ������� �������
	TCHAR qVolley[64];																			//�������� ������
	int qVolleySize = wsprintf(qVolley, _T("������ ������ - %d"), theSalut.getQuantVolley());	//��������� ���������� �������� ������
	TextOut(hdc, 30, 30, qVolley, qVolleySize);													//����������� �����
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
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
			br.lbStyle = BS_SOLID;				//�������� ����� ��� ����������
			br.lbColor = 0x550000;				//-----"-------
			brush = CreateBrushIndirect(&br);	//-----"-------
			SetTimer(hWnd, TIMER_SEC, 60, NULL);// �������� 0.06 ������� - ������� ���������� �������
			break;
		case WM_LBUTTONUP:
			GetCursorPos(&pt);					//����������� ������� �������
			ScreenToClient(hWnd, &pt);			//�������� ������� � �������� ����
			theSalut.addVolley(pt.x, pt.y);		//��� ������ ����� ����� ������� ����� �������� ����� ����
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// ��������� ����� � ����:
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
		case WM_TIMER:					// ��������� ��������� WM_TIMER
			InvalidateRect(hWnd, NULL, TRUE);  //����� ������� WM_PAINT
			break;	
		case WM_PAINT:
			GetClientRect(hWnd, &Rect);					//�������� ���������� �������� ����
			hdc = BeginPaint(hWnd, &ps);				//��������� ��������� ��� ��������� � ���������� ���������� ��������� ���������� ����������� ��� ��������� ����
			SelectObject(hdc, GetStockObject(DC_PEN));	//�������� ��� ��������� ����� �������
			SetDCPenColor(hdc, RGB(255, 255, 255));		//������������� ���� �������
			FillRect(hdc, &Rect, brush);				//�������� ���� ������ ����������, ������ �� ��� ��� ����
			MyDraw(hdc);								//�������� ���� ������� ���������
			EndPaint(hWnd, &ps);						//��������� ���������
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
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
