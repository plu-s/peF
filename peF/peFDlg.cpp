
// peFDlg.cpp : ʵ���ļ�
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

// ״̬����Ŀ
static UINT indicators[] = { ID_INDICATOR_PATH };


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CpeFDlg �Ի���



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


// CpeFDlg ��Ϣ�������

BOOL CpeFDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	// ����EDIT�ؼ���ɫΪ��ɫ
	m_whiteBrush.CreateSolidBrush(RGB(255, 255, 255));


	/***************************************************/
	// ��ȡע�����Ϣ���ж��Ƿ��Ѿ�ע��ɹ�
	// ����Ӧ�����йذ�ť�Ŀ���״̬

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
			// ע����е�ֵΪ 5��˵���Ѿ�ע��
			if (value == 5)
			{
				// �����Ѿ��ɹ�ע��ע��
				flag = true;
			}
		}// if
	}// if

	if (flag)
	{
		// ���������ʱ�������桸�򿪡�����Ŀ¼�����顢������Ϣ���ĸ���ťĬ��Ϊ��Ҳ�����״̬
		// �Ѿ�ע�ᣬ���ð�ť����
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);	// ���򿪡���ť

		// ����������֧����ҷ�ļ�
		// ��Ϊ win7 ������ϵͳ�İ�ȫ���Ƶ�ԭ���Թ���Ա������г���ʱ
		// ������������д������֧����ҷ���ļ�
		ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
		ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
		DragAcceptFiles(true);

		// ���������ڱ�����Ϊ��ע��
		AfxGetMainWnd()->SetWindowText(TEXT("peF BY �Ӻţ���ע�ᣩ"));
	}
	else {
		// ���������ڱ�����Ϊδע��
		SetWindowText(TEXT("peF BY �Ӻţ�δע�ᣩ"));
	}
	/***************************************************/


	/***************************************************/
	// ��ʼ��״̬��
	CRect rect;
	GetWindowRect(&rect);

	m_statusBar.Create(this);
	m_statusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	m_statusBar.SetPaneInfo(0, indicators[0], SBPS_NORMAL, rect.Width());
	m_statusBar.SetPaneText(0, TEXT("δ���ļ�"));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	/***************************************************/


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CpeFDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CpeFDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CpeFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �����ڡ� ��ť
void CpeFDlg::OnBnClickedAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// �������� ��ť
void CpeFDlg::OnBnClickedHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CHelp help;
	help.DoModal();
}


// ���˳��� ��ť
void CpeFDlg::OnBnClickedQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	closeFileAndMap();
	SendMessage(WM_CLOSE, 0, 0);
}



// ������ҷ���ߴ򿪶Ի����õ��ļ���
void CpeFDlg::openFile(LPTSTR fileName)
{
	// ѡ�����µ��ļ��򿪣����ر���ǰ���ļ���������ذ�ť��״̬����״̬
	closeFileAndMap();

	// ���ļ�
	if (m_theOpenFile.Open(fileName, CFile::modeRead) == 0)
	{
		MessageBox(TEXT("���ļ�ʧ�ܣ�"), NULL, MB_ICONERROR);
		return;
	}

	// �����ļ��ڴ�ӳ��
	m_fileMapping = CreateFileMapping(m_theOpenFile.m_hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (!m_fileMapping)
	{
		m_theOpenFile.Close();
		MessageBox(TEXT("�����ļ��ڴ�ӳ��ʧ�ܣ�"), NULL, MB_ICONERROR);
		return;
	}

	// ��ȡ�ڴ�ӳ���ַ
	m_pImageBase = MapViewOfFile(m_fileMapping, FILE_MAP_READ, 0, 0, 0);
	if (!m_pImageBase)
	{
		CloseHandle(m_fileMapping);
		m_theOpenFile.Close();
		return;
	}

	// �ж��Ƿ�Ϊ�Ϸ��� PE �ļ�
	if (!isPEfile())
	{
		MessageBox(TEXT("���ǺϷ��� PE ��ʽ�ļ���"), NULL, MB_ICONERROR);
		closeFileAndMap();

		return;
	}

	// ���ļ��Ϸ�����״̬����ʾ�ļ�����·��
	m_statusBar.SetPaneText(0, fileName);

	// ���������桸����Ŀ¼�����顢������Ϣ��������ťΪ����״̬
	GetDlgItem(IDC_BUTTON8)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(true);

	// ����ȫ�� ImageBase��ʹ��ͬ���ڼ乲�� ImageBase
	global_pImageBase = m_pImageBase;

	// ���������������ѡ�ļ�ͷ�������
	showOptionalHeader();
	// ������������� file �ļ�ͷ�������
	showFileHeader();
}



// ʵ����ҷ���ļ�
void CpeFDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TCHAR filePath[MAX_PATH];

	if (DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0) == 1)
	{
		DragQueryFile(hDropInfo, 0, filePath, MAX_PATH);

		// ����ҷ����ļ�����Ȼ����� openFile ���ļ�
		openFile(filePath);
	}
	else {
		MessageBox(TEXT("���ļ�ʧ�ܣ�ֻ������һ���ļ���"), NULL, MB_ICONERROR);
	}

	CDialogEx::OnDropFiles(hDropInfo);
}



// ���򿪡� ��ť
void CpeFDlg::OnBnClickedOpenFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CFileDialog openFileDlg(true);
	openFileDlg.m_ofn.lpstrTitle = TEXT("���ļ�");
	openFileDlg.m_ofn.lpstrFilter = TEXT("EXE Files(*.exe)\0*.exe\0Dll Files(*.dll)\0*.dll\0All File(*.*)\0*.*\0\0");

	// ���ļ��������ļ�ӳ��
	if (IDOK == openFileDlg.DoModal())
	{
		// �ɴ򿪶Ի������ļ�����Ȼ����� openFile ���ļ�
		openFile(openFileDlg.GetPathName().GetBuffer());
	}
}



// �ر��ļ��Լ���Ӧ���ļ�ӳ������״̬������������ذ�ť��״̬
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

	// ����״̬����·����ʾΪ ��δ���ļ���
	m_statusBar.SetPaneText(0, TEXT("δ���ļ�"));

	// ���������桸����Ŀ¼�����顢������Ϣ��������ťΪ��Ҳ�����״̬
	GetDlgItem(IDC_BUTTON8)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(false);

	global_pImageBase = NULL;
	m_theOpenFile.m_hFile = m_theOpenFile.hFileNull;
	m_fileMapping = NULL;
	m_pImageBase = NULL;
}


// ���� dos ͷ��Ǻ� NT ͷ����ж��Ƿ�Ϊ PE �ļ�
bool CpeFDlg::isPEfile()
{
	PIMAGE_DOS_HEADER pDOS;
	PIMAGE_NT_HEADERS pNT;

	// ���� dos ͷ���
	pDOS = (PIMAGE_DOS_HEADER)m_pImageBase;
	if (pDOS->e_magic != IMAGE_DOS_SIGNATURE)
	{
		return false;
	}

	// ���� NT ͷ���
	pNT = (PIMAGE_NT_HEADERS)((DWORD)m_pImageBase + pDOS->e_lfanew);
	if (pNT->Signature != IMAGE_NT_SIGNATURE)
	{
		return false;
	}

	return true;
}


// ��ʾ��ѡ�ļ�ͷ��Ϣ
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


// ��ʾ FILE �ļ�ͷ��Ϣ
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


// ��ʾ����Ŀ¼����Ϣ
void CpeFDlg::OnBnClickedDataDirectory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pImageBase)
	{
		CDataDir dataDirDlg;
		dataDirDlg.DoModal();
	}
}


// ��ʾ�������Ϣ
void CpeFDlg::OnBnClickedSectionTable()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pImageBase)
	{
		CSECTION_TABLE sectionTableDlg;
		sectionTableDlg.DoModal();
	}
}


// ��ʾ������ PE ͷ��Ϣ
void CpeFDlg::OnBnClickedShowAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pImageBase)
	{
		CSHOW_ALL showPEallDlg;
		showPEallDlg.DoModal();
	}
}


// ע��ģ��
void CpeFDlg::OnBnClickedRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegester regesterDlg;
	regesterDlg.DoModal();
}



// ��ģ̬�Ի���չʾ PE �ļ��Ļ����ṹ
void CpeFDlg::OnBnClickedShowPEStruct()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// 1����ģ̬�Ի���ĸ�����Ϊ���棬�������ڳ�Ϊ�ֵܴ��ڶ����Ǹ��Ӵ���
	// �Ӷ���ģ̬�Ի��򲻻�һֱ����������������
	// 2���ж� m_showPEstruct.m_hWnd �Ƿ�Ϊ�գ��Ӷ�ֻ��һ����ģ̬�Ի���
	if (m_showPEstruct.m_hWnd == NULL)
	{
		m_showPEstruct.Create(IDD_PESTRUCT, this->GetDesktopWindow());
		m_showPEstruct.ShowWindow(SW_SHOW);
	}
	else {
		// ����ģ̬�Ի������ڵ�ǰ z ����Ķ���
		m_showPEstruct.BringWindowToTop();
	}
}



// ���� EDIT�ؼ���ɫΪ��ɫ
HBRUSH CpeFDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:		// �� EDIT�ؼ�Ϊ READONLY ����ʱ��Ӧѡ�� CTLCOLOR_STATIC
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_EDIT3:			// EDIT3 ~ EDIT20�������������EDIT�ؼ�
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