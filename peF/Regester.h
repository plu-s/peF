#pragma once


// CRegester �Ի���

class CRegester : public CDialogEx
{
	DECLARE_DYNAMIC(CRegester)

public:
	CRegester(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegester();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
private:
	CString m_regCode;
};
