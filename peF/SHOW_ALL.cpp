// SHOW_ALL.cpp : 实现文件
//

#include "stdafx.h"
#include "peF.h"
#include "SHOW_ALL.h"
#include "afxdialogex.h"

#include "global.h"

// CSHOW_ALL 对话框

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


// CSHOW_ALL 消息处理程序



BOOL CSHOW_ALL::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CRect listCtfRect;
	// 获取列表控件的矩形大小信息
	m_listShowALL.GetClientRect(&listCtfRect);
	// 设置选中行高亮样式
	m_listShowALL.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// 插入 3 列
	m_listShowALL.InsertColumn(0, TEXT("偏移地址"), LVCFMT_LEFT, listCtfRect.Width() / 7, 0);
	m_listShowALL.InsertColumn(1, TEXT("值"), LVCFMT_LEFT, listCtfRect.Width() / 7, 1);
	m_listShowALL.InsertColumn(2, TEXT("英文说明	"), LVCFMT_LEFT, listCtfRect.Width() / 7 * 2, 2);
	m_listShowALL.InsertColumn(3, TEXT("中文说明	"), LVCFMT_LEFT, listCtfRect.Width() / 7 * 3, 3);

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

	DWORD whichItem = -1;		// 指示插入列表控件的第几项
	CString buffer;				// 缓冲区

/*************************  宏定义  ************************/
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

	// 对应项的地址表 (减去 global_ImageBase 后即可得偏移地址)
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

	// 插入 item 并显示其第一列
	for (int i = 0; i < NumOfItem; ++i)
	{
		FormatAddr_InsertItem(i, (DWORD)offAddr[i]);
	}

	/***************************************************************/
	// 显示第二列
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
	// 显示第三列
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
	// 显示第四列
	TCHAR *chineseIns[NumOfItem] =
	{
		TEXT("DOS 文件标记 “MZ”"),
		TEXT("尾页字节"),
		TEXT("文件页数"),
		TEXT("重定位项目"),
		TEXT("头部大小"),
		TEXT("最小内存"),
		TEXT("最大内存"),
		TEXT("初始 SS 值"),
		TEXT("初始 SP 值"),
		TEXT("校验和"),
		TEXT("DOS 代码入口 IP"),
		TEXT("DOS 代码入口 CS"),
		TEXT("重定位表"),
		TEXT("覆盖"),
		TEXT("保留值"),
		TEXT("OEM 标识符"),
		TEXT("OEM 信息"),
		TEXT("保留值"),
		TEXT("PE 文件头偏移量"),

		TEXT("PE 文件标识 “PE”"),

		TEXT("运行平台"),
		TEXT("区块数"),
		TEXT("时间/日期戳"),
		TEXT("指向符号表"),
		TEXT("符号数"),
		TEXT("可选头大小（IMAGE_OPTIONAL_HEADER）"),
		TEXT("特征值"),

		TEXT("标志字"),
		TEXT("链接器主版本号"),
		TEXT("链接器次版本号"),
		TEXT("代码区块总大小"),
		TEXT("已初始化数据大小"),
		TEXT("未初始化数据大小"),
		TEXT("程序入口点"),
		TEXT("代码基址"),
		TEXT("数据基址"),
		TEXT("映像基址"),
		TEXT("区段对齐"),
		TEXT("文件对齐"),
		TEXT("操作系统主版本号"),
		TEXT("操作系统次版本号"),
		TEXT("用户自定义主版本号"),
		TEXT("用户自定义次版本号"),
		TEXT("子系统主版本号"),
		TEXT("子系统次版本号"),
		TEXT("保留值，通常设置为 0"),
		TEXT("映像大小"),
		TEXT("DOS头、PE头、区块表总大小"),
		TEXT("映像校验和"),
		TEXT("文件子系统"),
		TEXT("DLL标志"),
		TEXT("初始化堆栈大小"),
		TEXT("初始化实际提交堆栈大小"),
		TEXT("初始化保留堆栈大小"),
		TEXT("初始化实际保留堆栈大小"),
		TEXT("加载器标志"),
		TEXT("数据目录表项数（固定为 0x10）"),

		TEXT("导出表地址"),
		TEXT("导出表大小"),
		TEXT("导入表地址"),
		TEXT("导入表大小"),
		TEXT("资源表地址"),
		TEXT("资源表大小"),
		TEXT("异常表地址"),
		TEXT("异常表大小"),
		TEXT("安全表地址"),
		TEXT("安全表大小"),
		TEXT("基址重定位表地址"),
		TEXT("基址重定位表大小"),
		TEXT("调试数据地址"),
		TEXT("调试数据大小"),
		TEXT("版本数据地址"),
		TEXT("版本数据大小"),
		TEXT("全局 Ptr 地址"),
		TEXT("全局 Ptr 大小（固定为 0）"),
		TEXT("TLS 表地址（TLS：线程局部存储）"),
		TEXT("TLS 表大小"),
		TEXT("载入配置表地址"),
		TEXT("载入配置表大小"),
		TEXT("绑定输入表地址"),
		TEXT("绑定输入表大小"),
		TEXT("输入地址表地址（IAT：输入地址表）"),
		TEXT("输入地址表大小"),
		TEXT("延迟输入描述符地址"),
		TEXT("延迟输入描述符大小"),
		TEXT("COM+ Runtime 描述符地址"),
		TEXT("COM+ Runtime 描述符大小"),
		TEXT("保留值"),
		TEXT("保留值"),
	};

	for (int i = 0; i < NumOfItem; ++i)
	{
		buffer = chineseIns[i];
		m_listShowALL.SetItemText(i, 3, buffer);
	}
	/***************************************************************/

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
