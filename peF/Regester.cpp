// Regester.cpp : 实现文件
//

#include "stdafx.h"
#include "peF.h"
#include "Regester.h"
#include "afxdialogex.h"


// CRegester 对话框

IMPLEMENT_DYNAMIC(CRegester, CDialogEx)

CRegester::CRegester(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGISTER, pParent)
	, m_regCode(_T(""))
{

}

CRegester::~CRegester()
{
}

void CRegester::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RegCode, m_regCode);
}


BEGIN_MESSAGE_MAP(CRegester, CDialogEx)
END_MESSAGE_MAP()


// CRegester 消息处理程序


// 重写 OnOK 虚函数，在该函数中完成注册判断功能
void CRegester::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(true);

	//对注册码进行判断
	if ((m_regCode.GetLength() != 0) && (m_regCode.GetLength() % 4 == 0))
	{
		char *regCode = (char*)malloc(m_regCode.GetLength() + 1);
		memset(regCode, 0, strlen(regCode));
		WideCharToMultiByte(CP_ACP, 0, m_regCode, -1, regCode, m_regCode.GetLength(), NULL, NULL);
		ULONG64 key = 0;

		char *p = regCode;
		for (UINT i = 0; i < strlen(regCode) / 4; ++i)
		{
			key += *(UINT*)p;
			p += 4;
		}

		if (key == 4465466720)
		{
			// 输入注册码正确
			
			HKEY hKey;
			long ret;
			ret = RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\peF\\reg"), (PHKEY)&hKey);
			if (ret != ERROR_SUCCESS)
			{
				MessageBox(TEXT("注册失败，请尝试以系统管理员身份注册！"), NULL, MB_ICONERROR);
			}
			else 
			{
				DWORD value = 5;
				ret = RegSetValueEx(hKey, TEXT("flag"), 0, REG_DWORD, (const BYTE*)&value, sizeof(DWORD));
				if (ret != ERROR_SUCCESS)
				{
					MessageBox(TEXT("注册失败，请尝试以系统管理员身份注册！"), NULL, MB_ICONERROR);
				}
				else
				{
					// 输入注册码正确且注册成功！

					MessageBox(TEXT("注册成功！"), NULL, MB_ICONINFORMATION);

					// 设置相关按钮为可用状态
					GetParent()->GetDlgItem(IDC_BUTTON1)->EnableWindow(true);

					// 设置主窗口支持拖曳文件
					// 因为 win7 及以上系统的安全机制的原因，以管理员身份运行程序时
					// 需添加以下两行代码才能支持拖曳打开文件
					ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
					ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
					GetParent()->DragAcceptFiles(true);

					// 设置主窗口标题栏
					AfxGetMainWnd()->SetWindowText(TEXT("peF BY 加号（已注册）"));
				}// if else
			}// if else

		}// if

	}// if
	


	CDialogEx::OnOK();
}
