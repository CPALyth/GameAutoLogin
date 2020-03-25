#pragma once
#include <windows.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <atltypes.h>
#include <ctime>
#include <atlstr.h>

// 调试输出
void DbgOutput(const char *szFormat, ...);

// 数字处理相关
__int64 Hex2Dec(std::string strHex);

// 键鼠操作
void MoveTo(int x, int y, HWND hWnd = 0);
void LeftClick();
void LeftDoubleClick();
void KeyPress(BYTE vk_Code);

// 随机数
template<class T>
T rnd(T _begin, T _end);

// 数据类型转换
LPCTSTR int2LPCSTR(int a);

