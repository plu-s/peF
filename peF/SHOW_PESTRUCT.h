#pragma once


// CSHOW_PESTRUCT �Ի���

class CSHOW_PESTRUCT : public CDialogEx
{
	DECLARE_DYNAMIC(CSHOW_PESTRUCT)

public:
	CSHOW_PESTRUCT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSHOW_PESTRUCT();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PESTRUCT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual void OnCancel();
};
