// ODBCAssetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JINYEOB_info.h"
#include "ODBCAssetDlg.h"
#include "afxdialogex.h"
#include <string>

// CODBCAssetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CODBCAssetDlg, CDialog)

CODBCAssetDlg::CODBCAssetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ODBCDIALOG_ASSET, pParent)
{

}

CODBCAssetDlg::~CODBCAssetDlg()
{
}

void CODBCAssetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ASSET, m_ListAsset);
}


BEGIN_MESSAGE_MAP(CODBCAssetDlg, CDialog)
END_MESSAGE_MAP()


// CODBCAssetDlg 메시지 처리기입니다.


BOOL CODBCAssetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CDatabase db;
	db.OpenEx(_T("DSN=informationDSN"), 0);
	CRecordset rs(&db);
	rs.Open(CRecordset::dynaset, _T("SELECT * FROM asset"));

	m_LargeImageList2.Create(IDB_BITMAP2, 48, 1, RGB(0, 0, 0));
	m_SmallImageList2.Create(IDB_BITMAP1, 16, 1, RGB(0, 0, 0));
	m_ListAsset.SetImageList(&m_LargeImageList2, LVSIL_NORMAL);
	m_ListAsset.SetImageList(&m_SmallImageList2, LVSIL_SMALL);

	m_ListAsset.SetExtendedStyle(m_ListAsset.GetExtendedStyle() | LVS_EX_GRIDLINES);
	m_ListAsset.SetExtendedStyle(m_ListAsset.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_ListAsset.InsertColumn(0, _T("번호"), LVCFMT_RIGHT, 60);
	m_ListAsset.InsertColumn(1, _T("제품"), LVCFMT_LEFT, 100);
	m_ListAsset.InsertColumn(2, _T("금액"), LVCFMT_LEFT, 150);
	m_ListAsset.InsertColumn(3, _T("구매년도"), LVCFMT_LEFT, 100);
	m_ListAsset.InsertColumn(4, _T("분류"), LVCFMT_LEFT, 100);

	CString str;
	int i = 0;
	while (!rs.IsEOF()) {
		rs.GetFieldValue(short(0), str);
		m_ListAsset.InsertItem(i, str, 0);
		rs.GetFieldValue(short(1), str);
		m_ListAsset.SetItemText(i, 1, str);
		rs.GetFieldValue(short(2), str);
		m_ListAsset.SetItemText(i, 2, str);
		rs.GetFieldValue(short(3), str);
		m_ListAsset.SetItemText(i, 3, str);
		rs.GetFieldValue(short(4), str);
		m_ListAsset.SetItemText(i, 4, str);

		rs.MoveNext();
		i++;
	}

	rs.Close(); 
	db.Close();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
