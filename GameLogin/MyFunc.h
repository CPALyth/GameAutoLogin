#pragma once
#include <windows.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <atltypes.h>
#include <ctime>
#include <atlstr.h>

// �������
void tracePrint(const char *szFormat, ...);

// ����ת��
__int64 Hex2Dec(std::string strHex);

// �������
void MoveTo(int x, int y, HWND hWnd = 0);
void LeftClick();
void LeftDoubleClick();
void KeyPress(BYTE vk_Code);

// �����߳�
BOOL EndProcess(LPCTSTR className, LPCTSTR captionName);	//��������

// �����
template<class T>
T rnd(T _begin, T _end);

// ��������ת��
LPCTSTR int2LPCSTR(int a);

// �쳣����
enum ExceptionType{ ErrorOnLauncher,ErrorOnClient};
struct MyException
{
	int m_ErrorType;
	MyException(int errorType):m_ErrorType(errorType)
	{
		tracePrint("�����쳣,�쳣����:%d", m_ErrorType);
	}
};