#pragma once
#include "afxcmn.h"


// CSHOW_ALL 对话框

class CSHOW_ALL : public CDialogEx
{
	DECLARE_DYNAMIC(CSHOW_ALL)

public:
	CSHOW_ALL(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSHOW_ALL();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_ALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_listShowALL;
public:
	virtual BOOL OnInitDialog();
};
