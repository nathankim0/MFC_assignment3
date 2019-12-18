
// JINYEOB_infoView.h : CJINYEOB_infoView 클래스의 인터페이스
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CJINYEOB_infoSet;

class CJINYEOB_infoView : public CRecordView
{
protected: // serialization에서만 만들어집니다.
	CJINYEOB_infoView();
	DECLARE_DYNCREATE(CJINYEOB_infoView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_JINYEOB_INFO_FORM };
#endif
	CJINYEOB_infoSet* m_pSet;

// 특성입니다.
public:
	CJINYEOB_infoDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CJINYEOB_infoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	CButton m_ButtonTotal;
	CButton m_ButtonAdd;
	CButton m_ButtonMod;
	CButton m_ButtonDelete;
	void Addcolumn();
	void AddAllRecord();
	void GetTotalRecordCount();
	int record_count;
	afx_msg void OnBnClickedButtonTotal();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonUpdate();
	int current_pos;
	BOOL bUpdate;
	BOOL bAdd;
	BOOL bSearch;

	afx_msg void OnLvnItemchangedListAddr(NMHDR *pNMHDR, LRESULT *pResult);
	void Select();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnRecordFirst();
	afx_msg void OnRecordPrev();
	afx_msg void OnRecordNext();
	afx_msg void OnRecordLast();
	void SetImageList();

	CImageList m_LargeImageList;
	CImageList m_SmallImageList;
	afx_msg void OnIcon();
	afx_msg void OnSmallicon();
	afx_msg void OnList();
	afx_msg void OnReport();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedButtonSearch();
	CString m_Search;
	afx_msg void OnLbnSelchangeListSearch();
	CListBox m_Box;
	afx_msg void OnBnClickedButtonAsset();
};

#ifndef _DEBUG  // JINYEOB_infoView.cpp의 디버그 버전
inline CJINYEOB_infoDoc* CJINYEOB_infoView::GetDocument() const
   { return reinterpret_cast<CJINYEOB_infoDoc*>(m_pDocument); }
#endif

