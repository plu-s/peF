#pragma once


// CRegester 对话框

class CRegester : public CDialogEx
{
	DECLARE_DYNAMIC(CRegester)

public:
	CRegester(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegester();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
private:
	CString m_regCode;
};
