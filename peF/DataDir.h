#pragma once


// CDataDir �Ի���

class CDataDir : public CDialogEx
{
	DECLARE_DYNAMIC(CDataDir)

public:
	CDataDir(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataDir();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_DIR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	CBrush m_whiteBrush;
public:
	virtual BOOL OnInitDialog();
};
