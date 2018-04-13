
// peFDlg.h : ͷ�ļ�
//

#pragma once
#include "afx.h"
#include "afxext.h"
#include "SHOW_PESTRUCT.h"


// CpeFDlg �Ի���
class CpeFDlg : public CDialogEx
{
// ����
public:
	CpeFDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEF_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// ������״̬������ʾ���ļ�������·��
	CStatusBar m_statusBar;
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
private:
	// ������ҷ���ߴ򿪶Ի����õ��ļ���
	void openFile(LPTSTR fileName);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	CBrush m_whiteBrush;
public:
	afx_msg void OnBnClickedShowPEStruct();
private:
	// ��ģ̬�Ի�����ʾ PE �ļ������ṹʾ��ͼ
	CSHOW_PESTRUCT m_showPEstruct;
};
