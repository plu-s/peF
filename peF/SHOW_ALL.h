#pragma once
#include "afxcmn.h"


// CSHOW_ALL �Ի���

class CSHOW_ALL : public CDialogEx
{
	DECLARE_DYNAMIC(CSHOW_ALL)

public:
	CSHOW_ALL(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSHOW_ALL();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_ALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_listShowALL;
public:
	virtual BOOL OnInitDialog();
};
