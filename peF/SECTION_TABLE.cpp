// SECTION_TABLE.cpp : 实现文件
//

#include "stdafx.h"
#include "peF.h"
#include "SECTION_TABLE.h"
#include "afxdialogex.h"

#include "global.h"

// CSECTION_TABLE 对话框

IMPLEMENT_DYNAMIC(CSECTION_TABLE, CDialogEx)

CSECTION_TABLE::CSECTION_TABLE(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SECTION_TABLE, pParent)
{

}

CSECTION_TABLE::~CSECTION_TABLE()
{
}

void CSECTION_TABLE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SECTION_LIST, m_sectionList);
}


BEGIN_MESSAGE_MAP(CSECTION_TABLE, CDialogEx)
END_MESSAGE_MAP()


// CSECTION_TABLE 消息处理程序



BOOL CSECTION_TABLE::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect listCtfRect;
	// 获取列表控件的矩形大小信息
	m_sectionList.GetClientRect(&listCtfRect);
	// 设置选中行高亮样式
	m_sectionList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// 插入 6 列
	m_sectionList.InsertColumn(0, TEXT("Name"), LVCFMT_CENTER, listCtfRect.Width() / 6, 0);
	m_sectionList.InsertColumn(1, TEXT("VAddress"), LVCFMT_CENTER, listCtfRect.Width() / 6, 1);
	m_sectionList.InsertColumn(2, TEXT("VSize"), LVCFMT_CENTER, listCtfRect.Width() / 6, 2);
	m_sectionList.InsertColumn(3, TEXT("ROffset"), LVCFMT_CENTER, listCtfRect.Width() / 6, 3);
	m_sectionList.InsertColumn(4, TEXT("RSize"), LVCFMT_CENTER, listCtfRect.Width() / 6, 4);
	m_sectionList.InsertColumn(5, TEXT("Flags"), LVCFMT_CENTER, listCtfRect.Width() / 6, 5);


	PIMAGE_DOS_HEADER pDOS;
	PIMAGE_NT_HEADERS pNT;
	PIMAGE_FILE_HEADER pFILE;
	PIMAGE_SECTION_HEADER pSECTION;

	pDOS = (PIMAGE_DOS_HEADER)global_pImageBase;
	pNT = (PIMAGE_NT_HEADERS)((DWORD)global_pImageBase + pDOS->e_lfanew);
	pFILE = (PIMAGE_FILE_HEADER)(&(pNT->FileHeader));
	pSECTION = IMAGE_FIRST_SECTION(pNT);

	//TCHAR name[9], buffer[9];
	CString name, buffer;

	// 循环设置区块的每一列信息
	for (int i = 0; i < pFILE->NumberOfSections; ++i)
	{
		name = pSECTION->Name;
		m_sectionList.InsertItem(i, name);

		buffer.Format(TEXT("%08X"), pSECTION->VirtualAddress);
		m_sectionList.SetItemText(i, 1, buffer);

		buffer.Format(TEXT("%08X"), pSECTION->Misc.VirtualSize);
		m_sectionList.SetItemText(i, 2, buffer);

		buffer.Format(TEXT("%08X"), pSECTION->PointerToRawData);
		m_sectionList.SetItemText(i, 3, buffer);

		buffer.Format(TEXT("%08X"), pSECTION->SizeOfRawData);
		m_sectionList.SetItemText(i, 4, buffer);

		buffer.Format(TEXT("%08X"), pSECTION->Characteristics);
		m_sectionList.SetItemText(i, 5, buffer);

		++pSECTION;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
