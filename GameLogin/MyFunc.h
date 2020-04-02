#pragma once
#include <windows.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <atltypes.h>
#include <ctime>
#include <atlstr.h>

// 调试输出
void tracePrint(const char *szFormat, ...);

// 类型转换
__int64 Hex2Dec(std::string strHex);

// 键鼠操作
void MoveTo(int x, int y, HWND hWnd = 0);
void LeftClick();
void LeftDoubleClick();
void KeyPress(BYTE vk_Code);

// 进程线程
BOOL EndProcess(LPCTSTR className, LPCTSTR captionName);	//结束进程

// 随机数
template<class T>
T rnd(T _begin, T _end);

// 数据类型转换
LPCTSTR int2LPCSTR(int a);

// 异常处理
enum ExceptionType{ ErrorOnLauncher,ErrorOnClient};
struct MyException
{
	int m_ErrorType;
	MyException(int errorType):m_ErrorType(errorType)
	{
		tracePrint("发生异常,异常类型:%d", m_ErrorType);
	}
};