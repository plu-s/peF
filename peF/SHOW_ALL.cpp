// SHOW_ALL.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "peF.h"
#include "SHOW_ALL.h"
#include "afxdialogex.h"

#include "global.h"

// CSHOW_ALL �Ի���

IMPLEMENT_DYNAMIC(CSHOW_ALL, CDialogEx)

CSHOW_ALL::CSHOW_ALL(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHOW_ALL, pParent)
{

}

CSHOW_ALL::~CSHOW_ALL()
{
}

void CSHOW_ALL::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALL, m_listShowALL);
}


BEGIN_MESSAGE_MAP(CSHOW_ALL, CDialogEx)
END_MESSAGE_MAP()


// CSHOW_ALL ��Ϣ�������



BOOL CSHOW_ALL::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CRect listCtfRect;
	// ��ȡ�б�ؼ��ľ��δ�С��Ϣ
	m_listShowALL.GetClientRect(&listCtfRect);
	// ����ѡ���и�����ʽ
	m_listShowALL.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// ���� 3 ��
	m_listShowALL.InsertColumn(0, TEXT("ƫ�Ƶ�ַ"), LVCFMT_LEFT, listCtfRect.Width() / 7, 0);
	m_listShowALL.InsertColumn(1, TEXT("ֵ"), LVCFMT_LEFT, listCtfRect.Width() / 7, 1);
	m_listShowALL.InsertColumn(2, TEXT("Ӣ��˵��	"), LVCFMT_LEFT, listCtfRect.Width() / 7 * 2, 2);
	m_listShowALL.InsertColumn(3, TEXT("����˵��	"), LVCFMT_LEFT, listCtfRect.Width() / 7 * 3, 3);

	PIMAGE_DOS_HEADER pDOS;
	PIMAGE_NT_HEADERS pNT;
	PIMAGE_FILE_HEADER pFILE;
	PIMAGE_OPTIONAL_HEADER pOPTIONAL;
	PIMAGE_SECTION_HEADER pSECTION;

	pDOS = (PIMAGE_DOS_HEADER)global_pImageBase;
	pNT = (PIMAGE_NT_HEADERS)((DWORD)global_pImageBase + pDOS->e_lfanew);
	pFILE = (PIMAGE_FILE_HEADER)(&(pNT->FileHeader));
	pOPTIONAL = (PIMAGE_OPTIONAL_HEADER)(&(pNT->OptionalHeader));
	pSECTION = IMAGE_FIRST_SECTION(pNT);

	DWORD whichItem = -1;		// ָʾ�����б�ؼ��ĵڼ���
	CString buffer;				// ������

/*************************  �궨��  ************************/
#define InsertItem(x) (m_listShowALL.InsertItem((x), buffer))
#define FormatAddr(x) (buffer.Format(TEXT("%08X"), ((x) - (DWORD)global_pImageBase)))
#define FormatAddr_InsertItem(x, y) (FormatAddr((y)), InsertItem((x)))

#define SetColumn1 (m_listShowALL.SetItemText(++whichItem, 1, buffer))

#define FormatB(x) (buffer.Format(TEXT("%02X"), (x)))
#define FormatW(x) (buffer.Format(TEXT("%04X"), (x)))
#define FormatD(x) (buffer.Format(TEXT("%08X"), (x)))

#define FormatB_SetColumn1(x) (FormatB((x)), SetColumn1)
#define FormatW_SetColumn1(x) (FormatW((x)), SetColumn1)
#define FormatD_SetColumn1(x) (FormatD((x)), SetColumn1)

#define NumOfItem 89
/**********************************************************/

	// ��Ӧ��ĵ�ַ�� (��ȥ global_ImageBase �󼴿ɵ�ƫ�Ƶ�ַ)
	LPVOID offAddr[NumOfItem] =
	{
		&pDOS->e_magic,
		&pDOS->e_cblp,
		&pDOS->e_cp,
		&pDOS->e_crlc,
		&pDOS->e_cparhdr,
		&pDOS->e_minalloc,
		&pDOS->e_maxalloc,
		&pDOS->e_ss,
		&pDOS->e_sp,
		&pDOS->e_csum,
		&pDOS->e_ip,
		&pDOS->e_cs,
		&pDOS->e_lfarlc,
		&pDOS->e_ovno,
		&pDOS->e_res,
		&pDOS->e_oemid,
		&pDOS->e_oeminfo,
		&pDOS->e_res2,
		&pDOS->e_lfanew,

		&pNT->Signature,

		&pFILE->Machine,
		&pFILE->NumberOfSections,
		&pFILE->TimeDateStamp,
		&pFILE->PointerToSymbolTable,
		&pFILE->NumberOfSymbols,
		&pFILE->SizeOfOptionalHeader,
		&pFILE->Characteristics,

		&pOPTIONAL->Magic,
		&pOPTIONAL->MajorLinkerVersion,
		&pOPTIONAL->MinorLinkerVersion,
		&pOPTIONAL->SizeOfCode,
		&pOPTIONAL->SizeOfInitializedData,
		&pOPTIONAL->SizeOfUninitializedData,
		&pOPTIONAL->AddressOfEntryPoint,
		&pOPTIONAL->BaseOfCode,
		&pOPTIONAL->BaseOfData,
		&pOPTIONAL->ImageBase,
		&pOPTIONAL->SectionAlignment,
		&pOPTIONAL->FileAlignment,
		&pOPTIONAL->MajorOperatingSystemVersion,
		&pOPTIONAL->MinorOperatingSystemVersion,
		&pOPTIONAL->MajorImageVersion,
		&pOPTIONAL->MinorImageVersion,
		&pOPTIONAL->MajorSubsystemVersion,
		&pOPTIONAL->MinorSubsystemVersion,
		&pOPTIONAL->Win32VersionValue,
		&pOPTIONAL->SizeOfImage,
		&pOPTIONAL->SizeOfHeaders,
		&pOPTIONAL->CheckSum,
		&pOPTIONAL->Subsystem,
		&pOPTIONAL->DllCharacteristics,
		&pOPTIONAL->SizeOfStackReserve,
		&pOPTIONAL->SizeOfStackCommit,
		&pOPTIONAL->SizeOfHeapReserve,
		&pOPTIONAL->SizeOfHeapCommit,
		&pOPTIONAL->LoaderFlags,
		&pOPTIONAL->NumberOfRvaAndSizes,

		&pOPTIONAL->DataDirectory[0].VirtualAddress,
		&pOPTIONAL->DataDirectory[0].Size,
		&pOPTIONAL->DataDirectory[1].VirtualAddress,
		&pOPTIONAL->DataDirectory[1].Size,
		&pOPTIONAL->DataDirectory[2].VirtualAddress,
		&pOPTIONAL->DataDirectory[2].Size,
		&pOPTIONAL->DataDirectory[3].VirtualAddress,
		&pOPTIONAL->DataDirectory[3].Size,
		&pOPTIONAL->DataDirectory[4].VirtualAddress,
		&pOPTIONAL->DataDirectory[4].Size,
		&pOPTIONAL->DataDirectory[5].VirtualAddress,
		&pOPTIONAL->DataDirectory[5].Size,
		&pOPTIONAL->DataDirectory[6].VirtualAddress,
		&pOPTIONAL->DataDirectory[6].Size,
		&pOPTIONAL->DataDirectory[7].VirtualAddress,
		&pOPTIONAL->DataDirectory[7].Size,
		&pOPTIONAL->DataDirectory[8].VirtualAddress,
		&pOPTIONAL->DataDirectory[8].Size,
		&pOPTIONAL->DataDirectory[9].VirtualAddress,
		&pOPTIONAL->DataDirectory[9].Size,
		&pOPTIONAL->DataDirectory[10].VirtualAddress,
		&pOPTIONAL->DataDirectory[10].Size,
		&pOPTIONAL->DataDirectory[11].VirtualAddress,
		&pOPTIONAL->DataDirectory[11].Size,
		&pOPTIONAL->DataDirectory[12].VirtualAddress,
		&pOPTIONAL->DataDirectory[12].Size,
		&pOPTIONAL->DataDirectory[13].VirtualAddress,
		&pOPTIONAL->DataDirectory[13].Size,
		&pOPTIONAL->DataDirectory[14].VirtualAddress,
		&pOPTIONAL->DataDirectory[14].Size,
		&pOPTIONAL->DataDirectory[15].VirtualAddress,
		&pOPTIONAL->DataDirectory[15].Size
	};

	// ���� item ����ʾ���һ��
	for (int i = 0; i < NumOfItem; ++i)
	{
		FormatAddr_InsertItem(i, (DWORD)offAddr[i]);
	}

	/***************************************************************/
	// ��ʾ�ڶ���
	for (int i = 0; i < 19; ++i)
	{
		FormatW_SetColumn1(*(WORD*)offAddr[i]);
	}

	FormatD_SetColumn1((DWORD)pNT->Signature);
	FormatW_SetColumn1((WORD)pFILE->Machine);
	FormatW_SetColumn1((WORD)pFILE->NumberOfSections);
	FormatD_SetColumn1((DWORD)pFILE->TimeDateStamp);
	FormatD_SetColumn1((DWORD)pFILE->PointerToSymbolTable);
	FormatD_SetColumn1((DWORD)pFILE->NumberOfSymbols);
	FormatW_SetColumn1((WORD)pFILE->SizeOfOptionalHeader);
	FormatW_SetColumn1((WORD)pFILE->Characteristics);
	FormatW_SetColumn1((WORD)pOPTIONAL->Magic);
	FormatB_SetColumn1((BYTE)pOPTIONAL->MajorLinkerVersion);
	FormatB_SetColumn1((BYTE)pOPTIONAL->MinorLinkerVersion);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SizeOfCode);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SizeOfInitializedData);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SizeOfUninitializedData);
	FormatD_SetColumn1((DWORD)pOPTIONAL->AddressOfEntryPoint);
	FormatD_SetColumn1((DWORD)pOPTIONAL->BaseOfCode);
	FormatD_SetColumn1((DWORD)pOPTIONAL->BaseOfData);
	FormatD_SetColumn1((DWORD)pOPTIONAL->ImageBase);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SectionAlignment);
	FormatD_SetColumn1((DWORD)pOPTIONAL->FileAlignment);
	FormatW_SetColumn1((WORD)pOPTIONAL->MajorOperatingSystemVersion);
	FormatW_SetColumn1((WORD)pOPTIONAL->MinorOperatingSystemVersion);
	FormatW_SetColumn1((WORD)pOPTIONAL->MajorImageVersion);
	FormatW_SetColumn1((WORD)pOPTIONAL->MinorImageVersion);
	FormatW_SetColumn1((WORD)pOPTIONAL->MajorSubsystemVersion);
	FormatW_SetColumn1((WORD)pOPTIONAL->MinorSubsystemVersion);
	FormatD_SetColumn1((DWORD)pOPTIONAL->Win32VersionValue);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SizeOfImage);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SizeOfHeaders);
	FormatD_SetColumn1((DWORD)pOPTIONAL->CheckSum);
	FormatW_SetColumn1((WORD)pOPTIONAL->Subsystem);
	FormatW_SetColumn1((WORD)pOPTIONAL->DllCharacteristics);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SizeOfStackReserve);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SizeOfStackCommit);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SizeOfHeapReserve);
	FormatD_SetColumn1((DWORD)pOPTIONAL->SizeOfHeapCommit);
	FormatD_SetColumn1((DWORD)pOPTIONAL->LoaderFlags);
	FormatD_SetColumn1((DWORD)pOPTIONAL->NumberOfRvaAndSizes);

	for (int i = 57; i < NumOfItem; ++i)
	{
		FormatD_SetColumn1(*(DWORD*)offAddr[i]);
	}
	/***************************************************************/

	/***************************************************************/
	// ��ʾ������
	TCHAR *englishIns[NumOfItem] =
	{
		TEXT("e_magic"),
		TEXT("e_cblp"),
		TEXT("e_cp"),
		TEXT("e_crlc"),
		TEXT("e_cparhdr"),
		TEXT("e_minalloc"),
		TEXT("e_maxalloc"),
		TEXT("e_ss"),
		TEXT("e_sp"),
		TEXT("e_csum"),
		TEXT("e_ip"),
		TEXT("e_cs"),
		TEXT("e_lfarlc"),
		TEXT("e_ovno"),
		TEXT("e_res"),
		TEXT("e_oemid"),
		TEXT("e_oeminfo"),
		TEXT("e_res2"),
		TEXT("e_lfanew"),

		TEXT("Signature"),

		TEXT("Machine"),
		TEXT("NumberOfSections"),
		TEXT("TimeDateStamp"),
		TEXT("PointerToSymbolTable"),
		TEXT("NumberOfSymbols"),
		TEXT("SizeOfOptionalHeader"),
		TEXT("Characteristics"),

		TEXT("Magic"),
		TEXT("MajorLinkerVersion"),
		TEXT("MinorLinkerVersion"),
		TEXT("SizeOfCode"),
		TEXT("SizeOfInitializedData"),
		TEXT("SizeOfUninitializedData"),
		TEXT("AddressOfEntryPoint"),
		TEXT("BaseOfCode"),
		TEXT("BaseOfData"),
		TEXT("ImageBase"),
		TEXT("SectionAlignment"),
		TEXT("FileAlignment"),
		TEXT("MajorOperatingSystemVersion"),
		TEXT("MinorOperatingSystemVersion"),
		TEXT("MajorImageVersion"),
		TEXT("MinorImageVersion"),
		TEXT("MajorSubsystemVersion"),
		TEXT("MinorSubsystemVersion"),
		TEXT("Win32VersionValue"),
		TEXT("SizeOfImage"),
		TEXT("SizeOfHeaders"),
		TEXT("CheckSum"),
		TEXT("Subsystem"),
		TEXT("DllCharacteristics"),
		TEXT("SizeOfStackReserve"),
		TEXT("SizeOfStackCommit"),
		TEXT("SizeOfHeapReserve"),
		TEXT("SizeOfHeapCommit"),
		TEXT("LoaderFlags"),
		TEXT("NumberOfRvaAndSizes"),

		TEXT("Export Table address"),
		TEXT("Export Table size"),
		TEXT("Import Table address"),
		TEXT("Import Table size"),
		TEXT("Resource Table address"),
		TEXT("Resource Table size"),
		TEXT("Exception Table address"),
		TEXT("Exception Table size"),
		TEXT("Certificate File pointer"),
		TEXT("Certificate Table size"),
		TEXT("Relocation Table address"),
		TEXT("Relocation Table size"),
		TEXT("Debug Data address"),
		TEXT("Debug Data size"),
		TEXT("Architecture Data address"),
		TEXT("Architecture Data size"),
		TEXT("Global Ptr address"),
		TEXT("Global Ptr size"),
		TEXT("TLS Table address"),
		TEXT("TLS Table size"),
		TEXT("Load Config Table address"),
		TEXT("Load Config Table size"),
		TEXT("Bound Import Table address"),
		TEXT("Bound Import Table size"),
		TEXT("Import Address Table address"),
		TEXT("Import Address Table size"),
		TEXT("Delay Import Descriptor address"),
		TEXT("Delay Import Descriptor size"),
		TEXT("COM+ Runtime Header address"),
		TEXT("COM+ Runtime Header size"),
		TEXT("Reserved"),
		TEXT("Reserved"),
	};

	for (int i = 0; i < NumOfItem; ++i)
	{
		buffer = englishIns[i];
		m_listShowALL.SetItemText(i, 2, buffer);
	}
	/***************************************************************/


	/***************************************************************/
	// ��ʾ������
	TCHAR *chineseIns[NumOfItem] =
	{
		TEXT("DOS �ļ���� ��MZ��"),
		TEXT("βҳ�ֽ�"),
		TEXT("�ļ�ҳ��"),
		TEXT("�ض�λ��Ŀ"),
		TEXT("ͷ����С"),
		TEXT("��С�ڴ�"),
		TEXT("����ڴ�"),
		TEXT("��ʼ SS ֵ"),
		TEXT("��ʼ SP ֵ"),
		TEXT("У���"),
		TEXT("DOS ������� IP"),
		TEXT("DOS ������� CS"),
		TEXT("�ض�λ��"),
		TEXT("����"),
		TEXT("����ֵ"),
		TEXT("OEM ��ʶ��"),
		TEXT("OEM ��Ϣ"),
		TEXT("����ֵ"),
		TEXT("PE �ļ�ͷƫ����"),

		TEXT("PE �ļ���ʶ ��PE��"),

		TEXT("����ƽ̨"),
		TEXT("������"),
		TEXT("ʱ��/���ڴ�"),
		TEXT("ָ����ű�"),
		TEXT("������"),
		TEXT("��ѡͷ��С��IMAGE_OPTIONAL_HEADER��"),
		TEXT("����ֵ"),

		TEXT("��־��"),
		TEXT("���������汾��"),
		TEXT("�������ΰ汾��"),
		TEXT("���������ܴ�С"),
		TEXT("�ѳ�ʼ�����ݴ�С"),
		TEXT("δ��ʼ�����ݴ�С"),
		TEXT("������ڵ�"),
		TEXT("�����ַ"),
		TEXT("���ݻ�ַ"),
		TEXT("ӳ���ַ"),
		TEXT("���ζ���"),
		TEXT("�ļ�����"),
		TEXT("����ϵͳ���汾��"),
		TEXT("����ϵͳ�ΰ汾��"),
		TEXT("�û��Զ������汾��"),
		TEXT("�û��Զ���ΰ汾��"),
		TEXT("��ϵͳ���汾��"),
		TEXT("��ϵͳ�ΰ汾��"),
		TEXT("����ֵ��ͨ������Ϊ 0"),
		TEXT("ӳ���С"),
		TEXT("DOSͷ��PEͷ��������ܴ�С"),
		TEXT("ӳ��У���"),
		TEXT("�ļ���ϵͳ"),
		TEXT("DLL��־"),
		TEXT("��ʼ����ջ��С"),
		TEXT("��ʼ��ʵ���ύ��ջ��С"),
		TEXT("��ʼ��������ջ��С"),
		TEXT("��ʼ��ʵ�ʱ�����ջ��С"),
		TEXT("��������־"),
		TEXT("����Ŀ¼���������̶�Ϊ 0x10��"),

		TEXT("�������ַ"),
		TEXT("�������С"),
		TEXT("������ַ"),
		TEXT("������С"),
		TEXT("��Դ���ַ"),
		TEXT("��Դ���С"),
		TEXT("�쳣���ַ"),
		TEXT("�쳣���С"),
		TEXT("��ȫ���ַ"),
		TEXT("��ȫ���С"),
		TEXT("��ַ�ض�λ���ַ"),
		TEXT("��ַ�ض�λ���С"),
		TEXT("�������ݵ�ַ"),
		TEXT("�������ݴ�С"),
		TEXT("�汾���ݵ�ַ"),
		TEXT("�汾���ݴ�С"),
		TEXT("ȫ�� Ptr ��ַ"),
		TEXT("ȫ�� Ptr ��С���̶�Ϊ 0��"),
		TEXT("TLS ���ַ��TLS���ֲ߳̾��洢��"),
		TEXT("TLS ���С"),
		TEXT("�������ñ��ַ"),
		TEXT("�������ñ��С"),
		TEXT("��������ַ"),
		TEXT("��������С"),
		TEXT("�����ַ���ַ��IAT�������ַ��"),
		TEXT("�����ַ���С"),
		TEXT("�ӳ�������������ַ"),
		TEXT("�ӳ�������������С"),
		TEXT("COM+ Runtime ��������ַ"),
		TEXT("COM+ Runtime ��������С"),
		TEXT("����ֵ"),
		TEXT("����ֵ"),
	};

	for (int i = 0; i < NumOfItem; ++i)
	{
		buffer = chineseIns[i];
		m_listShowALL.SetItemText(i, 3, buffer);
	}
	/***************************************************************/

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
