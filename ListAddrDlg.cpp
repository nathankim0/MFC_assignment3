// ListAddrDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JINYEOB_info.h"
#include "ListAddrDlg.h"
#include "afxdialogex.h"
// CListAddrDlg 대화 상자입니다.
IMPLEMENT_DYNAMIC(CListAddrDlg, CDialogEx)

CListAddrDlg::CListAddrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LIST, pParent)
{

}

CListAddrDlg::~CListAddrDlg()
{
}


void CListAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_phone);
	DDX_Text(pDX, IDC_EDIT_GROUP, m_group);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_email);

	DDX_Control(pDX, IDC_COMBO_RELATION, m_comboRelation);
	DDX_CBString(pDX, IDC_COMBO_RELATION, m_relation);
}


BEGIN_MESSAGE_MAP(CListAddrDlg, CDialogEx)
END_MESSAGE_MAP()

