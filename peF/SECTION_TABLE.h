#pragma once
#include "afxcmn.h"


// CSECTION_TABLE �Ի���

class CSECTION_TABLE : public CDialogEx
{
	DECLARE_DYNAMIC(CSECTION_TABLE)

public:
	CSECTION_TABLE(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSECTION_TABLE();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECTION_TABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_sectionList;
public:
	virtual BOOL OnInitDialog();
};
