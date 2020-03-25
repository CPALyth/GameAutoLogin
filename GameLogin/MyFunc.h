#pragma once
#include <windows.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <atltypes.h>
#include <ctime>
#include <atlstr.h>

// �������
void DbgOutput(const char *szFormat, ...);

// ���ִ������
__int64 Hex2Dec(std::string strHex);

// �������
void MoveTo(int x, int y, HWND hWnd = 0);
void LeftClick();
void LeftDoubleClick();
void KeyPress(BYTE vk_Code);

// �����
template<class T>
T rnd(T _begin, T _end);

// ��������ת��
LPCTSTR int2LPCSTR(int a);

