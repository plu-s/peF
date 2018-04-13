
// peFDlg.h : 头文件
//

#pragma once
#include "afx.h"
#include "afxext.h"
#include "SHOW_PESTRUCT.h"


// CpeFDlg 对话框
class CpeFDlg : public CDialogEx
{
// 构造
public:
	CpeFDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEF_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedHelp();
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedOpenFile();
private:
	CFile m_theOpenFile;
	LPVOID m_pImageBase;
	HANDLE m_fileMapping;
	void closeFileAndMap();
	void showOptionalHeader();
	void showFileHeader();
public:
	afx_msg void OnBnClickedDataDirectory();
	afx_msg void OnBnClickedSectionTable();
	afx_msg void OnBnClickedShowAll();
	afx_msg void OnBnClickedRegister();
private:
	bool isPEfile();
private:
	// 主窗口状态栏，显示打开文件的完整路径
	CStatusBar m_statusBar;
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
private:
	// 打开由拖曳或者打开对话框获得的文件名
	void openFile(LPTSTR fileName);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	CBrush m_whiteBrush;
public:
	afx_msg void OnBnClickedShowPEStruct();
private:
	// 非模态对话框显示 PE 文件基本结构示意图
	CSHOW_PESTRUCT m_showPEstruct;
};
