#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#define ID_TIMER1 1

// CGameLoginDlg 对话框
class CGameLoginDlg : public CDialogEx
{
// 构造
public:
	CGameLoginDlg(CWnd* pParent = nullptr);	// 标准构造函数
	
	void Init_AllCtlData();	//初始化所有控件数据
	void Init_ListCtrl();		

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
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedBtnAddmsg();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSavecfg();
	afx_msg void OnBnClickedBtnReadcfg();

	void InsertListCtl();
	void UpdateListCtl();
	CString GetCmbCurSelItemText(UINT IdOfCtrl, DWORD dwIndex);
	void SaveListCtlDataToFile();
	void ReadFileDataToListCtl();
	
};



class CLoginData
{
public:
	char szUserName[30];	//账号
	char szPwd[30];		//密码
	UINT niDaQu;		//大区
	UINT niServer;		//几服
	UINT niXianLu;	//几线
	UINT niRoleIndex;		//第几个角色
};

enum DaQu{网通一区,网通二区,网通三区,网通四区,电信一区,电信二区,电信三区,电信四区,电信五区,电信六区};
enum XianLu{一线,二线,三线,四线,五线,六线,七线,八线,九线,十线};
enum RoleIndex{第1个,第2个,第3个,第4个};

void RunLaucher();	//启动登录器
BOOL IsAbleToStartGame();		//是否可以点击"开始游戏"
BOOL SelDaQuAndStart(DWORD dwIndex);	//选择区服并开始游戏
void InputString(string strKey);	//输入字符串,用于输入账号和密码
BOOL IsAbleToInputIdAndPwd();		//是否可以输入账号和密码
BOOL InputIdAndPwd(CLoginData* pLoginData, HWND hWnd);		//输入账号和密码
BOOL AutoLogin(CLoginData* pLoginData);

