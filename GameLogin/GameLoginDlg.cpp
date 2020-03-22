
// GameLoginDlg.cpp: 实现文件
//

#include "framework.h"
#include "GameLogin.h"
#include "GameLoginDlg.h"
#include "afxdialogex.h"
#include "MyFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char szPath_Client[MAX_PATH] = { 0 };	//"client"文件夹的全路径
char szPath_Launcher[MAX_PATH] = { 0 };	//launcher.exe的全路径
char szPath_Game[MAX_PATH] = { 0 };		//"热血江湖兵临城下"文件夹的全路径


// CGameLoginDlg 对话框
CGameLoginDlg::CGameLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMELOGIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edt_LauncherPath);
}

BEGIN_MESSAGE_MAP(CGameLoginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON5, &CGameLoginDlg::OnBnClickedBtn_AutoLogin)
	ON_BN_CLICKED(IDC_BUTTON1, &CGameLoginDlg::OnBnClickedBtn_LauncherDir)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGameLoginDlg 消息处理程序

BOOL CGameLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	strcpy_s(szPath_Launcher, "D:\\热血江湖兵临城下\\launcher.exe");
	strcpy_s(szPath_Game, "D:\\热血江湖兵临城下\\");
	strcpy_s(szPath_Client, "D:\\热血江湖兵临城下\\Client\\");
	m_edt_LauncherPath = szPath_Launcher;
	UpdateData(FALSE);	//变量 -> 控件

	SetTimer(ID_TIMER1, 1000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BYTE GameOpenNum = 0;	//游戏窗口打开数
BOOL CALLBACK EnumWindowsProc(
	HWND hwnd,
	LPARAM lParam)
{
	TCHAR buf_ClassName[200] = { 0 };
	GetClassName(hwnd, buf_ClassName, sizeof(buf_ClassName));
	if (strcmp(buf_ClassName, "D3D Window") == 0)	// 增加窗口打开数
		GameOpenNum++;
	return TRUE;
}

void CGameLoginDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case ID_TIMER1:
	{
		GameOpenNum = 0;
		EnumWindows(EnumWindowsProc, NULL);

		CString str;
		str.Format(_T("%d"), GameOpenNum);
		GetDlgItem(IDC_TEXT)->SetWindowText(str);
	}
	break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

// 选择launcher.exe的目录
void CGameLoginDlg::OnBnClickedBtn_LauncherDir()
{
	BROWSEINFOA bi = { 0 };

	char szDisplayName[MAX_PATH] = { 0 };
	bi.pszDisplayName = szDisplayName;	//接收 文件名称 的缓冲区(不包含路径)
	bi.hwndOwner = m_hWnd;	//父窗口
	bi.lpszTitle = "请选择包含launcher.exe的路径:";	//标题
	bi.ulFlags = BIF_BROWSEINCLUDEFILES | BIF_RETURNONLYFSDIRS;	//样式

	ITEMIDLIST* idList = SHBrowseForFolder(&bi);
	SHGetPathFromIDList(idList, szPath_Launcher);
	TRACE("%s\n", szDisplayName);
	if (strcmp(szDisplayName, "launcher.exe") != 0)
	{
		::MessageBoxA(0, "选择launcher.exe路径错误", "Error", MB_OK);
		szPath_Launcher[0] = 0;
		return;
	}
	char* sztmp = StrStrA(szPath_Launcher, "launcher.exe");
	if (sztmp != NULL)
	{
		sztmp[0] = 0;
		//获取 游戏目录 全路径
		strcpy_s(szPath_Game, szPath_Launcher);
		//重新设置 launcher.exe 的全路径
		strcat_s(szPath_Launcher, "launcher.exe");
		//获取 client目录 全路径
		strcpy_s(szPath_Client, szPath_Game);
		strcat_s(szPath_Client, "Client\\");
	}

	m_edt_LauncherPath = szPath_Launcher;
	UpdateData(FALSE);	//变量 -> 控件
}

//自动登录
void CGameLoginDlg::OnBnClickedBtn_AutoLogin()
{
	CLoginData LoginData;
	LoginData.strAccount = "ws164803";
	LoginData.strPwd = "kptg6594571";
	LoginData.niServer = 网通二区;
	LoginData.niGameLine = 七线;
	LoginData.niRoleIndex = 1;

	AutoLogin(&LoginData);
}



#define MultiOpenAddr 0x00407BDA
/* [2020/03/19 10:25]-[Remark: None] */
/* [启动登录器]-[成功返回真，否则返回假] */
void RunLaucher()
{
	if (szPath_Launcher[0] == 0)
	{
		::MessageBoxA(0, "请先选择launcher.exe的正确路径", "提示", MB_OK);
		return;
	}
	//创建一个挂起的进程
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;	//指定wShowWindow成员有效
	si.wShowWindow = TRUE;	//显示新建进程的主窗口
	BOOL bRet = CreateProcessA(NULL,szPath_Launcher,NULL,NULL,FALSE,
		CREATE_SUSPENDED,NULL,szPath_Game,&si,&pi);

	//Inline Hook
	BYTE byWriteBuf = 0xEB;
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pi.dwProcessId);
	WriteProcessMemory(hProcess, (DWORD*)MultiOpenAddr, &byWriteBuf, 1, NULL);

	//恢复主线程
	ResumeThread(pi.hThread);
}

BOOL IsAbleToStartGame()
{
	HWND hWnd = FindWindow(NULL, "Yulgang_File_Update");
	if (hWnd == NULL)	return FALSE;
	HDC hdcClient = GetDC(hWnd);
	DWORD dwBGR = GetPixel(hdcClient, 204, 467);	//取窗口客户区一个点的颜色BGR: 0a0a0a
	DbgOutput("%X\n", dwBGR);
	if (dwBGR == 0x0a0a0a)	return TRUE;
	return FALSE;
}

/* [2020/03/19 10:11]-[Remark: None] */
/* [选择区服并开始游戏]-[成功返回真，否则返回假] */
BOOL SelServerAndStart(DWORD dwIndex)
{
	int x = 210;	//"网通一区"按钮正中央
	int y = 110 + (dwIndex-1)*28;
	HWND hWnd = FindWindow(NULL, "Yulgang_File_Update");
	if (hWnd == NULL)	return FALSE;

	// 点击 区服
	MoveTo(x, y,hWnd);
	LeftClick();
	//等待 开始游戏按钮 显示
	while (!IsAbleToStartGame())	Sleep(500);
	Sleep(500);

	// 点击"开始游戏"
	MoveTo(66, 428, hWnd);
	LeftClick();
	return TRUE;
}

/* [2020/03/20 09:03]-[Remark: None] */
/* [输入字符串,用于输入账号和密码]-[成功返回真，否则返回假] */
void InputString(string strKey)
{
	for(DWORD i = 0; i < strKey.size(); ++i)
	{
		if (strKey[i] >= 'a' && strKey[i] <= 'z')
		{
			if ((GetKeyState(VK_CAPITAL) & 01) == 1)	//低位为1,则CapsLock开启, 要关闭它
			{
				KeyPress(VK_CAPITAL);
			}
			KeyPress(strKey[i] + 'A' - 'a');
		}
		else if (strKey[i] >= 'A' && strKey[i] <= 'Z')
		{
			if ((GetKeyState(VK_CAPITAL) & 01) == 0)	//低位为0,则CapsLock关闭, 要打开它
			{
				KeyPress(VK_CAPITAL);
			}
			KeyPress(strKey[i]);
		}
		else if (strKey[i] >= '0' && strKey[i] <= '9')
		{
			KeyPress(strKey[i]);
		}
	}
}

BOOL IsAbleToInputIdAndPwd()
{
	HWND hWnd = FindWindow("D3D Window", NULL);
	if (hWnd == NULL)	return FALSE;
	HDC hdcClient = GetDC(hWnd);
	DWORD dwBGR = GetPixel(hdcClient, 382, 154);	//取窗口客户区一个点的颜色BGR: 78D0FE
	DbgOutput("%X\n", dwBGR);
	if (dwBGR == 0x78D0FE)	return TRUE;
	return FALSE;
}

void InputIdAndPwd(CLoginData* pLoginData)
{
	DbgOutput("开始输入账号和密码\n");
	Sleep(100);
	KeyPress(VK_SHIFT);	//切换为英文输入法

	DbgOutput("输入账号\n");
	InputString(pLoginData->strAccount);	//输入账号
	KeyPress(VK_TAB);	//TAB切换到密码编辑框

	DbgOutput("输入密码\n");
	InputString(pLoginData->strPwd);		//输入密码
	KeyPress(VK_RETURN);	//Enter登录游戏
	Sleep(3000);
}

void AutoLogin(CLoginData* pLoginData)
{
	// 启动登录器,并等待登录器初始化完成
	RunLaucher();
	HWND hWnd = NULL;
	while (hWnd == NULL)
	{
		Sleep(500);
		DbgOutput("登录器还未打开\n");
		hWnd = FindWindowA(NULL, "Yulgang_File_Update");
	}
	Sleep(1000);

	// 把登录器窗口前置
	SwitchToThisWindow(hWnd, TRUE);
	SelServerAndStart(pLoginData->niServer);	//选择区服
	// 一直等待直到可以输入账号密码
	while (!IsAbleToInputIdAndPwd())	Sleep(500);

	// 把游戏窗口前置
	hWnd = FindWindowA("D3D Window", NULL);
	if (hWnd == NULL)	return;
	SwitchToThisWindow(hWnd, TRUE);
	// 输入账号和密码
	InputIdAndPwd(pLoginData);
	// 选线
	MoveTo(613, 435 + (pLoginData->niGameLine) * 21, hWnd);
	LeftDoubleClick();
	// 等待直到可以选择游戏角色
	Sleep(3000);
	MoveTo(173, 226 + (pLoginData->niRoleIndex) * 42, hWnd);
	LeftClick();
	Sleep(1000);
	// 进入游戏
	MoveTo(519, 719, hWnd);
	LeftClick();
}

