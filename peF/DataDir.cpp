// DataDir.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "peF.h"
#include "DataDir.h"
#include "afxdialogex.h"

#include "global.h"

// CDataDir �Ի���

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


// CDataDir ��Ϣ�������

BOOL CDataDir::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ����Ŀ¼���е�����EDIT�ؼ��ĵ�ɫΪ��ɫ
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

	// 16 ������Ŀ¼
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

	// ѭ��д�뵽 EDIT�ؼ���
	for (int i = 0; i < 16; ++i)
	{
		wsprintf(buffer, TEXT("%08X"), pOPTIONAL->DataDirectory[i].VirtualAddress);
		SetDlgItemText(dataStructArr[i].ID_RVA, buffer);

		wsprintf(buffer, TEXT("%08X"), pOPTIONAL->DataDirectory[i].Size);
		SetDlgItemText(dataStructArr[i].ID_SIZE, buffer);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CDataDir::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_EDIT1001:		// EDIT1001 ~ EDIT10032������Ŀ¼���е�����EDIT�ؼ�
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
			pDC->SetBkColor(RGB(255, 255, 255));		// �ı�����ɫΪ��ɫ
			pDC->SetTextColor(RGB(200, 50, 60));		// �ı�ǰ��ɫΪ����ɫ
			hbr = (HBRUSH)m_whiteBrush;					// EDIT�ؼ���ɫΪ��ɫ
			break;
		}
		break;
	}


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

