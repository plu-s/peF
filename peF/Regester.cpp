// Regester.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "peF.h"
#include "Regester.h"
#include "afxdialogex.h"


// CRegester �Ի���

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


// CRegester ��Ϣ�������


// ��д OnOK �麯�����ڸú��������ע���жϹ���
void CRegester::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(true);

	//��ע��������ж�
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
			// ����ע������ȷ
			
			HKEY hKey;
			long ret;
			ret = RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\peF\\reg"), (PHKEY)&hKey);
			if (ret != ERROR_SUCCESS)
			{
				MessageBox(TEXT("ע��ʧ�ܣ��볢����ϵͳ����Ա���ע�ᣡ"), NULL, MB_ICONERROR);
			}
			else 
			{
				DWORD value = 5;
				ret = RegSetValueEx(hKey, TEXT("flag"), 0, REG_DWORD, (const BYTE*)&value, sizeof(DWORD));
				if (ret != ERROR_SUCCESS)
				{
					MessageBox(TEXT("ע��ʧ�ܣ��볢����ϵͳ����Ա���ע�ᣡ"), NULL, MB_ICONERROR);
				}
				else
				{
					// ����ע������ȷ��ע��ɹ���

					MessageBox(TEXT("ע��ɹ���"), NULL, MB_ICONINFORMATION);

					// ������ذ�ťΪ����״̬
					GetParent()->GetDlgItem(IDC_BUTTON1)->EnableWindow(true);

					// ����������֧����ҷ�ļ�
					// ��Ϊ win7 ������ϵͳ�İ�ȫ���Ƶ�ԭ���Թ���Ա������г���ʱ
					// ������������д������֧����ҷ���ļ�
					ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
					ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
					GetParent()->DragAcceptFiles(true);

					// ���������ڱ�����
					AfxGetMainWnd()->SetWindowText(TEXT("peF BY �Ӻţ���ע�ᣩ"));
				}// if else
			}// if else

		}// if

	}// if
	


	CDialogEx::OnOK();
}
