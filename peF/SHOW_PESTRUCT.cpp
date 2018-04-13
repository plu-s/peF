// SHOW_PESTRUCT.cpp : 实现文件
//

#include "stdafx.h"
#include "peF.h"
#include "SHOW_PESTRUCT.h"
#include "afxdialogex.h"


// CSHOW_PESTRUCT 对话框

IMPLEMENT_DYNAMIC(CSHOW_PESTRUCT, CDialogEx)

CSHOW_PESTRUCT::CSHOW_PESTRUCT(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PESTRUCT, pParent)
{

}

CSHOW_PESTRUCT::~CSHOW_PESTRUCT()
{
}

void CSHOW_PESTRUCT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSHOW_PESTRUCT, CDialogEx)
END_MESSAGE_MAP()


// CSHOW_PESTRUCT 消息处理程序


// 非模态对话框点击 OK 或者 cancle，或者按下 enter 键以及 esc 键时，
// 实际上只是把调用 EndDialog 函数对话框给隐藏了，并没有销毁
// 因此对于非模态对话框，必须重载 OnOK 和 OnCancel 虚函数，完成销毁工作
// 并且不能继续调用原来的基类 OnOK 和 OnCancel 函数

void CSHOW_PESTRUCT::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	DestroyWindow();

	// CDialogEx::OnOK();
}

void CSHOW_PESTRUCT::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	DestroyWindow();

	// CDialogEx::OnCancel();
}
