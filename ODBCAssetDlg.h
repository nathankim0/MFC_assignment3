#pragma once
#include "afxcmn.h"


// CODBCAssetDlg 대화 상자입니다.

class CODBCAssetDlg : public CDialog
{
	DECLARE_DYNAMIC(CODBCAssetDlg)

public:
	CODBCAssetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CODBCAssetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ODBCDIALOG_ASSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListAsset;
	CImageList m_LargeImageList2;
	CImageList m_SmallImageList2;
};
