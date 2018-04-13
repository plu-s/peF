#pragma once


// CDataDir 对话框

class CDataDir : public CDialogEx
{
	DECLARE_DYNAMIC(CDataDir)

public:
	CDataDir(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataDir();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_DIR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	CBrush m_whiteBrush;
public:
	virtual BOOL OnInitDialog();
};
