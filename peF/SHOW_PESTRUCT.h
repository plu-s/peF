#pragma once


// CSHOW_PESTRUCT 对话框

class CSHOW_PESTRUCT : public CDialogEx
{
	DECLARE_DYNAMIC(CSHOW_PESTRUCT)

public:
	CSHOW_PESTRUCT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSHOW_PESTRUCT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PESTRUCT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual void OnCancel();
};
