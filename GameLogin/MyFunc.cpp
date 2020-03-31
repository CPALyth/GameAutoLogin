#include "MyFunc.h"

using namespace std;

void tracePrint(const char *szFormat, ...) {
#ifdef _DEBUG
	char szbufFormat[0x1000];
	char szBufFormat_Game[0x1008] = "Game:";
	va_list argList;
	va_start(argList, szFormat);     //参数列表初始化
	vsprintf_s(szbufFormat, szFormat, argList);
	strcat_s(szBufFormat_Game, szbufFormat);
	OutputDebugStringA(szBufFormat_Game);
	va_end(argList);
#endif
}

__int64 Hex2Dec(string strHex)
{
	int temp = 0;
	__int64 qwDec = 0;
	for(int i = 0; strHex[i] != '\0'; ++i)
	{
		switch (strHex[i])
		{
		case 'A':
		case 'a':
			temp = 10;		break;

		case 'B':
		case 'b':
			temp = 11;		break;

		case 'C':
		case 'c':
			temp = 12;		break;

		case 'D':
		case 'd':
			temp = 13;		break;

		case 'E':
		case 'e':
			temp = 14;		break;

		case 'F':
		case 'f':
			temp = 15;		break;

		default:
			if (strHex[i]>='0' && strHex[i] <= '9')
			{
				temp = strHex[i] - '0';
			}
			break;
		}
		qwDec += (__int64)(temp * pow(16, strHex.size() - 1 - i));
	}
	return qwDec;
}

void MoveTo(int x, int y, HWND hWnd)
{
	POINT p;
	if (hWnd != 0)
	{
		p.x = x;
		p.y = y;
		ClientToScreen(hWnd, &p);
	}
	SetCursorPos(p.x, p.y);
	Sleep(100);
}

void LeftClick()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(rnd(50,100));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void LeftDoubleClick()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(rnd(20, 50));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(rnd(20, 50));
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(rnd(20, 50));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(rnd(100, 200));
}

void KeyPress(BYTE vk_Code)
{
	keybd_event(vk_Code, 0, 0, 0);
	Sleep(rnd(50, 100));
	keybd_event(vk_Code, 0, KEYEVENTF_KEYUP, 0);
}

LPCTSTR int2LPCSTR(int a)
{
	CString cstr;
	cstr.Format(_T("%d"), a);
	return cstr;
}



template<class T>
T rnd(T _begin, T _end)
{
	srand(UINT(time(NULL)));
	T len = _end - _begin;
	if (_begin < _end)
		T len = _end - _begin;
	else
		T len = _begin - _end;
	return (_begin + rand() % len);
}


