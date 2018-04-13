#pragma once
#include "afxcmn.h"


// CSECTION_TABLE 对话框

class CSECTION_TABLE : public CDialogEx
{
	DECLARE_DYNAMIC(CSECTION_TABLE)

public:
	CSECTION_TABLE(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSECTION_TABLE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECTION_TABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_sectionList;
public:
	virtual BOOL OnInitDialog();
};
