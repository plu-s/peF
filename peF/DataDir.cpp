// DataDir.cpp : 实现文件
//

#include "stdafx.h"
#include "peF.h"
#include "DataDir.h"
#include "afxdialogex.h"

#include "global.h"

// CDataDir 对话框

IMPLEMENT_DYNAMIC(CDataDir, CDialogEx)

CDataDir::CDataDir(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATA_DIR, pParent)
{

}

CDataDir::~CDataDir()
{
}

void CDataDir::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDataDir, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDataDir 消息处理程序

BOOL CDataDir::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 数据目录表中的所有EDIT控件的底色为白色
	m_whiteBrush.CreateSolidBrush(RGB(255, 255, 255));


	PIMAGE_DOS_HEADER pDOS;
	PIMAGE_NT_HEADERS pNT;
	PIMAGE_OPTIONAL_HEADER pOPTIONAL;

	pDOS = (PIMAGE_DOS_HEADER)global_pImageBase;
	pNT = (PIMAGE_NT_HEADERS)((DWORD)global_pImageBase + pDOS->e_lfanew);
	pOPTIONAL = (PIMAGE_OPTIONAL_HEADER)(&(pNT->OptionalHeader));

	struct dataStruct {
		UINT ID_RVA;
		UINT ID_SIZE;
	};

	// 16 组数据目录
	struct dataStruct dataStructArr[16] =
	{
		{ IDC_EDIT1001, IDC_EDIT1002 },
		{ IDC_EDIT1003, IDC_EDIT1004 },
		{ IDC_EDIT1005, IDC_EDIT1006 },
		{ IDC_EDIT1007, IDC_EDIT1008 },
		{ IDC_EDIT1009, IDC_EDIT1010 },
		{ IDC_EDIT1011, IDC_EDIT1012 },
		{ IDC_EDIT1013, IDC_EDIT1014 },
		{ IDC_EDIT1015, IDC_EDIT1016 },
		{ IDC_EDIT1017, IDC_EDIT1018 },
		{ IDC_EDIT1019, IDC_EDIT1020 },
		{ IDC_EDIT1021, IDC_EDIT1022 },
		{ IDC_EDIT1023, IDC_EDIT1024 },
		{ IDC_EDIT1025, IDC_EDIT1026 },
		{ IDC_EDIT1027, IDC_EDIT1028 },
		{ IDC_EDIT1029, IDC_EDIT1030 },
		{ IDC_EDIT1031, IDC_EDIT1032 }
	};

	TCHAR buffer[20];

	// 循环写入到 EDIT控件中
	for (int i = 0; i < 16; ++i)
	{
		wsprintf(buffer, TEXT("%08X"), pOPTIONAL->DataDirectory[i].VirtualAddress);
		SetDlgItemText(dataStructArr[i].ID_RVA, buffer);

		wsprintf(buffer, TEXT("%08X"), pOPTIONAL->DataDirectory[i].Size);
		SetDlgItemText(dataStructArr[i].ID_SIZE, buffer);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CDataDir::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_EDIT1001:		// EDIT1001 ~ EDIT10032，数据目录表中的所有EDIT控件
		case IDC_EDIT1002:
		case IDC_EDIT1003:
		case IDC_EDIT1004:
		case IDC_EDIT1005:
		case IDC_EDIT1006:
		case IDC_EDIT1007:
		case IDC_EDIT1008:
		case IDC_EDIT1009:
		case IDC_EDIT1010:
		case IDC_EDIT1011:
		case IDC_EDIT1012:
		case IDC_EDIT1013:
		case IDC_EDIT1014:
		case IDC_EDIT1015:
		case IDC_EDIT1016:
		case IDC_EDIT1017:
		case IDC_EDIT1018:
		case IDC_EDIT1019:
		case IDC_EDIT1020:
		case IDC_EDIT1021:
		case IDC_EDIT1022:
		case IDC_EDIT1023:
		case IDC_EDIT1024:
		case IDC_EDIT1025:
		case IDC_EDIT1026:
		case IDC_EDIT1027:
		case IDC_EDIT1028:
		case IDC_EDIT1029:
		case IDC_EDIT1030:
		case IDC_EDIT1031:
		case IDC_EDIT1032:
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

