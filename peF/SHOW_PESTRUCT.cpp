// SHOW_PESTRUCT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "peF.h"
#include "SHOW_PESTRUCT.h"
#include "afxdialogex.h"


// CSHOW_PESTRUCT �Ի���

IMPLEMENT_DYNAMIC(CSHOW_PESTRUCT, CDialogEx)

CSHOW_PESTRUCT::CSHOW_PESTRUCT(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PESTRUCT, pParent)
{

}

CSHOW_PESTRUCT::~CSHOW_PESTRUCT()
{
}

void CSHOW_PESTRUCT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSHOW_PESTRUCT, CDialogEx)
END_MESSAGE_MAP()


// CSHOW_PESTRUCT ��Ϣ�������


// ��ģ̬�Ի����� OK ���� cancle�����߰��� enter ���Լ� esc ��ʱ��
// ʵ����ֻ�ǰѵ��� EndDialog �����Ի���������ˣ���û������
// ��˶��ڷ�ģ̬�Ի��򣬱������� OnOK �� OnCancel �麯����������ٹ���
// ���Ҳ��ܼ�������ԭ���Ļ��� OnOK �� OnCancel ����

void CSHOW_PESTRUCT::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	DestroyWindow();

	// CDialogEx::OnOK();
}

void CSHOW_PESTRUCT::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	DestroyWindow();

	// CDialogEx::OnCancel();
}
