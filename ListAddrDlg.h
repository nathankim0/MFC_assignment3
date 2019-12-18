#pragma once
#include "afxwin.h"

// CListAddrDlg 대화 상자입니다.

class CListAddrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListAddrDlg)

public:
	CListAddrDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CListAddrDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_phone;
	CString m_group;
	CString m_email;
	CString m_relation;
	CComboBox m_comboRelation;
};