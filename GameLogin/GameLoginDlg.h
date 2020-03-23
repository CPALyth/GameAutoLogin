#pragma once
#include <windows.h>
#include <string>
using namespace std;

#define ID_TIMER1 1

// CGameLoginDlg 对话框
class CGameLoginDlg : public CDialogEx
{
// 构造
public:
	CGameLoginDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMELOGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtn_AutoLogin();
	afx_msg void OnBnClickedBtn_LauncherDir();
	CString m_edt_LauncherPath;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

class CLoginData
{
public:
	string strAccount;	//账号
	string strPwd;		//密码
	UINT niServer;		//几区
	UINT niGameLine;	//几线
	UINT niRoleIndex;		//第几个角色
};

enum Server{网通一区=1,网通二区,网通三区,网通四区,电信一区,电信二区,电信三区,电信四区,电信五区,电信六区};
enum GameLine{一线=1,二线,三线,四线,五线,六线,七线,八线,九线,十线};

void RunLaucher();	//启动登录器
BOOL IsAbleToStartGame();		//是否可以点击"开始游戏"
BOOL SelServerAndStart(DWORD dwIndex);	//选择区服并开始游戏
void InputString(string strKey);	//输入字符串,用于输入账号和密码
BOOL IsAbleToInputIdAndPwd();		//是否可以输入账号和密码
BOOL InputIdAndPwd(CLoginData* pLoginData);				//输入账号和密码
BOOL AutoLogin(CLoginData* pLoginData);

#define Base_RoleProperty 0x02C186D8		//人物属性基址