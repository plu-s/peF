
// peFDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "peF.h"
#include "peFDlg.h"
#include "afxdialogex.h"

#include "help.h"
#include "DataDir.h"
#include "global.h"
#include "SECTION_TABLE.h"
#include "SHOW_ALL.h"
#include "Regester.h"
#include "SHOW_PESTRUCT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 状态栏栏目
static UINT indicators[] = { ID_INDICATOR_PATH };


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CpeFDlg 对话框



CpeFDlg::CpeFDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PEF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_fileMapping = NULL;
	m_pImageBase = NULL;
}

void CpeFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CpeFDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CpeFDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_BUTTON2, &CpeFDlg::OnBnClickedHelp)
	ON_BN_CLICKED(IDC_BUTTON4, &CpeFDlg::OnBnClickedQuit)
	ON_BN_CLICKED(IDC_BUTTON1, &CpeFDlg::OnBnClickedOpenFile)
	ON_BN_CLICKED(IDC_BUTTON10, &CpeFDlg::OnBnClickedDataDirectory)
	ON_BN_CLICKED(IDC_BUTTON8, &CpeFDlg::OnBnClickedSectionTable)
	ON_BN_CLICKED(IDC_BUTTON9, &CpeFDlg::OnBnClickedShowAll)
	ON_BN_CLICKED(IDC_BUTTON5, &CpeFDlg::OnBnClickedRegister)
	ON_WM_DROPFILES()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON6, &CpeFDlg::OnBnClickedShowPEStruct)
END_MESSAGE_MAP()


// CpeFDlg 消息处理程序

BOOL CpeFDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	// 设置EDIT控件底色为白色
	m_whiteBrush.CreateSolidBrush(RGB(255, 255, 255));


	/***************************************************/
	// 获取注册表信息，判断是否已经注册成功
	// 并相应设置有关按钮的可用状态

	HKEY hKey;
	long ret;
	DWORD value;
	DWORD size;
	bool flag = false;

	ret = RegCreateKey(HKEY_LOCAL_MACHINE, TEXT("Software\\peF\\reg"), &hKey);
	if (ret == ERROR_SUCCESS)
	{
		ret = RegQueryValueEx(hKey, TEXT("flag"), 0, NULL, (LPBYTE)&value, &size);
		if (ret == ERROR_SUCCESS)
		{
			// 注册表中的值为 5，说明已经注册
			if (value == 5)
			{
				// 程序已经成功注册注册
				flag = true;
			}
		}// if
	}// if

	if (flag)
	{
		// 程序刚启动时，主界面「打开、数据目录、区块、所有信息」四个按钮默认为变灰不可用状态
		// 已经注册，设置按钮可用
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);	// 「打开」按钮

		// 设置主窗口支持拖曳文件
		// 因为 win7 及以上系统的安全机制的原因，以管理员身份运行程序时
		// 需添加以下两行代码才能支持拖曳打开文件
		ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
		ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
		DragAcceptFiles(true);

		// 设置主窗口标题栏为已注册
		AfxGetMainWnd()->SetWindowText(TEXT("peF BY 加号（已注册）"));
	}
	else {
		// 设置主窗口标题栏为未注册
		SetWindowText(TEXT("peF BY 加号（未注册）"));
	}
	/***************************************************/


	/***************************************************/
	// 初始化状态栏
	CRect rect;
	GetWindowRect(&rect);

	m_statusBar.Create(this);
	m_statusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	m_statusBar.SetPaneInfo(0, indicators[0], SBPS_NORMAL, rect.Width());
	m_statusBar.SetPaneText(0, TEXT("未打开文件"));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	/***************************************************/


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CpeFDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpeFDlg::OnPaint()
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
HCURSOR CpeFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// “关于” 按钮
void CpeFDlg::OnBnClickedAbout()
{
	// TODO: 在此添加控件通知处理程序代码

	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// “帮助” 按钮
void CpeFDlg::OnBnClickedHelp()
{
	// TODO: 在此添加控件通知处理程序代码

	CHelp help;
	help.DoModal();
}


// “退出” 按钮
void CpeFDlg::OnBnClickedQuit()
{
	// TODO: 在此添加控件通知处理程序代码

	closeFileAndMap();
	SendMessage(WM_CLOSE, 0, 0);
}



// 打开由拖曳或者打开对话框获得的文件名
void CpeFDlg::openFile(LPTSTR fileName)
{
	// 选择了新的文件打开，将关闭以前的文件并设置相关按钮和状态栏的状态
	closeFileAndMap();

	// 打开文件
	if (m_theOpenFile.Open(fileName, CFile::modeRead) == 0)
	{
		MessageBox(TEXT("打开文件失败！"), NULL, MB_ICONERROR);
		return;
	}

	// 创建文件内存映像
	m_fileMapping = CreateFileMapping(m_theOpenFile.m_hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (!m_fileMapping)
	{
		m_theOpenFile.Close();
		MessageBox(TEXT("创建文件内存映像失败！"), NULL, MB_ICONERROR);
		return;
	}

	// 获取内存映像基址
	m_pImageBase = MapViewOfFile(m_fileMapping, FILE_MAP_READ, 0, 0, 0);
	if (!m_pImageBase)
	{
		CloseHandle(m_fileMapping);
		m_theOpenFile.Close();
		return;
	}

	// 判断是否为合法的 PE 文件
	if (!isPEfile())
	{
		MessageBox(TEXT("不是合法的 PE 格式文件！"), NULL, MB_ICONERROR);
		closeFileAndMap();

		return;
	}

	// 打开文件合法，在状态栏显示文件绝对路径
	m_statusBar.SetPaneText(0, fileName);

	// 设置主界面「数据目录、区块、所有信息」三个按钮为可用状态
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(true);

	// 设置全局 ImageBase，使不同窗口间共享 ImageBase
	global_pImageBase = m_pImageBase;

	// 在主窗口中输出可选文件头分析结果
	showOptionalHeader();
	// 在主窗口中输出 file 文件头分析结果
	showFileHeader();
}



// 实现拖曳打开文件
void CpeFDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TCHAR filePath[MAX_PATH];

	if (DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0) == 1)
	{
		DragQueryFile(hDropInfo, 0, filePath, MAX_PATH);

		// 由拖曳获得文件名，然后调用 openFile 打开文件
		openFile(filePath);
	}
	else {
		MessageBox(TEXT("打开文件失败，只能拖入一个文件！"), NULL, MB_ICONERROR);
	}

	CDialogEx::OnDropFiles(hDropInfo);
}



// “打开” 按钮
void CpeFDlg::OnBnClickedOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog openFileDlg(true);
	openFileDlg.m_ofn.lpstrTitle = TEXT("打开文件");
	openFileDlg.m_ofn.lpstrFilter = TEXT("EXE Files(*.exe)\0*.exe\0Dll Files(*.dll)\0*.dll\0All File(*.*)\0*.*\0\0");

	// 打开文件并创建文件映像
	if (IDOK == openFileDlg.DoModal())
	{
		// 由打开对话框获得文件名，然后调用 openFile 打开文件
		openFile(openFileDlg.GetPathName().GetBuffer());
	}
}



// 关闭文件以及对应的文件映像并设置状态栏和主界面相关按钮的状态
void CpeFDlg::closeFileAndMap()
{
	if (m_pImageBase)
	{
		UnmapViewOfFile(m_pImageBase);
	}

	if (m_fileMapping)
	{
		CloseHandle(m_fileMapping);
	}

	if (m_theOpenFile.m_hFile != m_theOpenFile.hFileNull)
	{
		m_theOpenFile.Close();
	}

	// 设置状态栏的路径显示为 “未打开文件”
	m_statusBar.SetPaneText(0, TEXT("未打开文件"));

	// 设置主界面「数据目录、区块、所有信息」三个按钮为变灰不可用状态
	GetDlgItem(IDC_BUTTON8)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(false);

	global_pImageBase = NULL;
	m_theOpenFile.m_hFile = m_theOpenFile.hFileNull;
	m_fileMapping = NULL;
	m_pImageBase = NULL;
}


// 依据 dos 头标记和 NT 头标记判断是否为 PE 文件
bool CpeFDlg::isPEfile()
{
	PIMAGE_DOS_HEADER pDOS;
	PIMAGE_NT_HEADERS pNT;

	// 存在 dos 头标记
	pDOS = (PIMAGE_DOS_HEADER)m_pImageBase;
	if (pDOS->e_magic != IMAGE_DOS_SIGNATURE)
	{
		return false;
	}

	// 存在 NT 头标记
	pNT = (PIMAGE_NT_HEADERS)((DWORD)m_pImageBase + pDOS->e_lfanew);
	if (pNT->Signature != IMAGE_NT_SIGNATURE)
	{
		return false;
	}

	return true;
}


// 显示可选文件头信息
void CpeFDlg::showOptionalHeader()
{
	PIMAGE_DOS_HEADER pDOS;
	PIMAGE_NT_HEADERS pNT;
	PIMAGE_OPTIONAL_HEADER pOPTIONAL;

	pDOS = (PIMAGE_DOS_HEADER)m_pImageBase;
	pNT = (PIMAGE_NT_HEADERS)((DWORD)m_pImageBase + pDOS->e_lfanew);
	pOPTIONAL = (PIMAGE_OPTIONAL_HEADER)(&(pNT->OptionalHeader));

	TCHAR buffer[20];

	wsprintf(buffer, TEXT("%08X"), pOPTIONAL->AddressOfEntryPoint);
	SetDlgItemText(IDC_EDIT3, buffer);

	wsprintf(buffer, TEXT("%08X"), pOPTIONAL->ImageBase);
	SetDlgItemText(IDC_EDIT4, buffer);

	wsprintf(buffer, TEXT("%08X"), pOPTIONAL->BaseOfCode);
	SetDlgItemText(IDC_EDIT5, buffer);

	wsprintf(buffer, TEXT("%08X"), pOPTIONAL->BaseOfData);
	SetDlgItemText(IDC_EDIT6, buffer);

	wsprintf(buffer, TEXT("%08X"), pOPTIONAL->SizeOfImage);
	SetDlgItemText(IDC_EDIT7, buffer);

	wsprintf(buffer, TEXT("%08X"), pOPTIONAL->SizeOfHeaders);
	SetDlgItemText(IDC_EDIT8, buffer);

	wsprintf(buffer, TEXT("%08X"), pOPTIONAL->SectionAlignment);
	SetDlgItemText(IDC_EDIT9, buffer);

	wsprintf(buffer, TEXT("%08X"), pOPTIONAL->FileAlignment);
	SetDlgItemText(IDC_EDIT10, buffer);

	wsprintf(buffer, TEXT("%04X"), pOPTIONAL->Subsystem);
	SetDlgItemText(IDC_EDIT11, buffer);

	wsprintf(buffer, TEXT("%08X"), pOPTIONAL->CheckSum);
	SetDlgItemText(IDC_EDIT12, buffer);

	wsprintf(buffer, TEXT("%04X"), pOPTIONAL->DllCharacteristics);
	SetDlgItemText(IDC_EDIT13, buffer);
}


// 显示 FILE 文件头信息
void CpeFDlg::showFileHeader()
{
	PIMAGE_DOS_HEADER pDOS;
	PIMAGE_NT_HEADERS pNT;
	PIMAGE_FILE_HEADER pFILE;

	pDOS = (PIMAGE_DOS_HEADER)m_pImageBase;
	pNT = (PIMAGE_NT_HEADERS)((DWORD)m_pImageBase + pDOS->e_lfanew);
	pFILE = (PIMAGE_FILE_HEADER)(&(pNT->FileHeader));

	TCHAR buffer[20];

	wsprintf(buffer, TEXT("%04X"), pFILE->Machine);
	SetDlgItemText(IDC_EDIT14, buffer);

	wsprintf(buffer, TEXT("%04X"), pFILE->NumberOfSections);
	SetDlgItemText(IDC_EDIT15, buffer);

	wsprintf(buffer, TEXT("%08X"), pFILE->TimeDateStamp);
	SetDlgItemText(IDC_EDIT16, buffer);

	wsprintf(buffer, TEXT("%08X"), pFILE->PointerToSymbolTable);
	SetDlgItemText(IDC_EDIT17, buffer);

	wsprintf(buffer, TEXT("%08X"), pFILE->NumberOfSymbols);
	SetDlgItemText(IDC_EDIT18, buffer);

	wsprintf(buffer, TEXT("%04X"), pFILE->SizeOfOptionalHeader);
	SetDlgItemText(IDC_EDIT19, buffer);

	wsprintf(buffer, TEXT("%04X"), pFILE->Characteristics);
	SetDlgItemText(IDC_EDIT20, buffer);
}


// 显示数据目录表信息
void CpeFDlg::OnBnClickedDataDirectory()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pImageBase)
	{
		CDataDir dataDirDlg;
		dataDirDlg.DoModal();
	}
}


// 显示区块表信息
void CpeFDlg::OnBnClickedSectionTable()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pImageBase)
	{
		CSECTION_TABLE sectionTableDlg;
		sectionTableDlg.DoModal();
	}
}


// 显示完整的 PE 头信息
void CpeFDlg::OnBnClickedShowAll()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pImageBase)
	{
		CSHOW_ALL showPEallDlg;
		showPEallDlg.DoModal();
	}
}


// 注册模块
void CpeFDlg::OnBnClickedRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegester regesterDlg;
	regesterDlg.DoModal();
}



// 非模态对话框展示 PE 文件的基本结构
void CpeFDlg::OnBnClickedShowPEStruct()
{
	// TODO: 在此添加控件通知处理程序代码

	// 1、非模态对话框的父窗口为桌面，和主窗口成为兄弟窗口而不是父子窗口
	// 从而费模态对话框不会一直覆盖在主窗口上面
	// 2、判断 m_showPEstruct.m_hWnd 是否为空，从而只打开一个非模态对话框
	if (m_showPEstruct.m_hWnd == NULL)
	{
		m_showPEstruct.Create(IDD_PESTRUCT, this->GetDesktopWindow());
		m_showPEstruct.ShowWindow(SW_SHOW);
	}
	else {
		// 将非模态对话框置于当前 z 次序的顶层
		m_showPEstruct.BringWindowToTop();
	}
}



// 设置 EDIT控件底色为白色
HBRUSH CpeFDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:		// 当 EDIT控件为 READONLY 属性时，应选择 CTLCOLOR_STATIC
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_EDIT3:			// EDIT3 ~ EDIT20，主界面的所有EDIT控件
		case IDC_EDIT4:
		case IDC_EDIT5:
		case IDC_EDIT6:
		case IDC_EDIT7:
		case IDC_EDIT8:
		case IDC_EDIT9:
		case IDC_EDIT10:
		case IDC_EDIT11:
		case IDC_EDIT12:
		case IDC_EDIT13:
		case IDC_EDIT14:
		case IDC_EDIT15:
		case IDC_EDIT16:
		case IDC_EDIT17:
		case IDC_EDIT18:
		case IDC_EDIT19:
		case IDC_EDIT20:
			pDC->SetBkColor(RGB(255, 255, 255));		// 文本背景色为白色
			pDC->SetTextColor(RGB(200, 50, 60));		// 文本前景色为红棕色
			hbr = (HBRUSH)m_whiteBrush;					// EDIT控件底色为白色
			break;
		}
		break;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}