
// JINYEOB_infoView.cpp : CJINYEOB_infoView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "JINYEOB_info.h"
#endif

#include "JINYEOB_infoSet.h"
#include "JINYEOB_infoDoc.h"
#include "JINYEOB_infoView.h"
#include "ListAddrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CJINYEOB_infoView

IMPLEMENT_DYNCREATE(CJINYEOB_infoView, CRecordView)

BEGIN_MESSAGE_MAP(CJINYEOB_infoView, CRecordView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRecordView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_TOTAL, &CJINYEOB_infoView::OnBnClickedButtonTotal)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CJINYEOB_infoView::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CJINYEOB_infoView::OnBnClickedButtonUpdate)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ADDR, &CJINYEOB_infoView::OnLvnItemchangedListAddr)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CJINYEOB_infoView::OnBnClickedButtonDelete)
	ON_COMMAND(ID_RECORD_FIRST, &CJINYEOB_infoView::OnRecordFirst)
	ON_COMMAND(ID_RECORD_PREV, &CJINYEOB_infoView::OnRecordPrev)
	ON_COMMAND(ID_RECORD_NEXT, &CJINYEOB_infoView::OnRecordNext)
	ON_COMMAND(ID_RECORD_LAST, &CJINYEOB_infoView::OnRecordLast)
	ON_COMMAND(ID_ICON, &CJINYEOB_infoView::OnIcon)
	ON_COMMAND(ID_SMALLICON, &CJINYEOB_infoView::OnSmallicon)
	ON_COMMAND(ID_LIST, &CJINYEOB_infoView::OnList)
	ON_COMMAND(ID_REPORT, &CJINYEOB_infoView::OnReport)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CJINYEOB_infoView::OnBnClickedButtonSearch)
	ON_LBN_SELCHANGE(IDC_LIST_SEARCH, &CJINYEOB_infoView::OnLbnSelchangeListSearch)
	ON_BN_CLICKED(IDC_BUTTON_ASSET, &CJINYEOB_infoView::OnBnClickedButtonAsset)
END_MESSAGE_MAP()

// CJINYEOB_infoView 생성/소멸

CJINYEOB_infoView::CJINYEOB_infoView()
	: CRecordView(IDD_JINYEOB_INFO_FORM)
{
	m_pSet = NULL;
	// TODO: 여기에 생성 코드를 추가합니다.
	current_pos = 1;
	record_count = 0;
	bAdd = FALSE;
	bUpdate = FALSE;
	bSearch = FALSE;
}

CJINYEOB_infoView::~CJINYEOB_infoView()
{
}

CListAddrDlg dlg;

void CJINYEOB_infoView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// 컨트롤을 데이터베이스 필드에 '연결'하기 위해 여기에 DDX_Field* 함수를 삽입할 수 있습니다. 예:
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// 자세한 내용은 MSDN 및 ODBC 샘플을 참조하십시오.

	DDX_Control(pDX, IDC_LIST_ADDR, m_List);
	DDX_Control(pDX, IDC_BUTTON_TOTAL, m_ButtonTotal);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_ButtonAdd);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_ButtonMod);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_ButtonDelete);

	DDX_Text(pDX, IDC_EDIT_SEARCH, m_Search);
	DDX_Control(pDX, IDC_LIST_SEARCH, m_Box);
}

BOOL CJINYEOB_infoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CRecordView::PreCreateWindow(cs);
}

void CJINYEOB_infoView::OnInitialUpdate()
{

	m_pSet = &GetDocument()->m_JINYEOB_infoSet;
	CRecordView::OnInitialUpdate();
	m_Box.AddString(_T("전체"));
	m_Box.AddString(_T("가족"));
	m_Box.AddString(_T("직장"));
	m_Box.AddString(_T("학교"));
	m_Box.AddString(_T("친구"));
	m_Box.AddString(_T("기타"));
	Addcolumn();
	SetImageList();
	AddAllRecord(); 
	GetTotalRecordCount();

	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_GRIDLINES);
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	m_List.SetSelectionMark(current_pos - 1);
	m_List.SetItemState(current_pos - 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_List.SetFocus();
}


// CJINYEOB_infoView 인쇄

BOOL CJINYEOB_infoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CJINYEOB_infoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CJINYEOB_infoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CJINYEOB_infoView 진단

#ifdef _DEBUG
void CJINYEOB_infoView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CJINYEOB_infoView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CJINYEOB_infoDoc* CJINYEOB_infoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJINYEOB_infoDoc)));
	return (CJINYEOB_infoDoc*)m_pDocument;
}
#endif //_DEBUG


// CJINYEOB_infoView 데이터베이스 지원
CRecordset* CJINYEOB_infoView::OnGetRecordset()
{
	return m_pSet;
}



// CJINYEOB_infoView 메시지 처리기



void CJINYEOB_infoView::Addcolumn()
{
	CRect rect;
	m_List.GetClientRect(&rect);
	m_List.InsertColumn(0, _T("이름"), LVCFMT_RIGHT, 100);
	m_List.InsertColumn(1, _T("이메일"), LVCFMT_LEFT, rect.Width() - 430);
	m_List.InsertColumn(2, _T("전화번호"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(3, _T("조직"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(4, _T("관계"), LVCFMT_LEFT, 60);

}


void CJINYEOB_infoView::AddAllRecord()
{
		m_pSet->Requery();
		int i = 0;
		m_List.DeleteAllItems();
		while (m_pSet->IsEOF() == FALSE) {
			m_List.InsertItem(i, m_pSet->m_fname, 0);
			m_List.SetItemText(i, 1, m_pSet->m_femail);
			m_List.SetItemText(i, 2, m_pSet->m_fphone);
			m_List.SetItemText(i, 3, m_pSet->m_fgroup);
			m_List.SetItemText(i, 4, m_pSet->m_frelation);
			m_pSet->MoveNext();
			i++;
		}
		current_pos = record_count = i;
		m_pSet->SetAbsolutePosition(current_pos);
}

void CJINYEOB_infoView::GetTotalRecordCount()
{
	CRecordset cntSet(m_pSet->m_pDatabase);
	cntSet.Open(CRecordset::dynaset, _T("select count(*) from addressbook")); // 전체 레코드의 개수를 구함
		CString strCount;
	cntSet.GetFieldValue((short)0, strCount);
	record_count = atoi((char *)(const wchar_t *)strCount);
	cntSet.Close();
}


void CJINYEOB_infoView::OnBnClickedButtonTotal()
{
	AddAllRecord();
	Select();
}


void CJINYEOB_infoView::OnBnClickedButtonAdd()
{
	int res = dlg.DoModal();

	if (res == IDOK) {
		m_pSet->AddNew();
		m_pSet->SetFieldNull(NULL);

		m_pSet->m_fname = dlg.m_name;
		m_pSet->m_fphone = dlg.m_phone;
		m_pSet->m_femail = dlg.m_email;
		m_pSet->m_fgroup = dlg.m_group;
		m_pSet->m_frelation = dlg.m_relation;

		m_pSet->Update();
		m_pSet->Requery();
		m_pSet->MoveLast();
		GetTotalRecordCount();
		AddAllRecord();
	}
	Select();
}

void CJINYEOB_infoView::OnLvnItemchangedListAddr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nItem = pNMLV->iItem; //선택된 항목의 행의 위치 값을 얻어옵니다.
	current_pos = nItem + 1;
	m_pSet->SetAbsolutePosition(current_pos);

	*pResult = 0;
}

void CJINYEOB_infoView::OnBnClickedButtonUpdate()
{

		CListAddrDlg dlg;

		dlg.m_name= m_pSet->m_fname;
		dlg.m_phone = m_pSet->m_fphone;
		dlg.m_email=m_pSet->m_femail;
		dlg.m_group=m_pSet->m_fgroup;
		dlg.m_relation=m_pSet->m_frelation;

		int res = dlg.DoModal();

		if (res == IDOK) {
			m_pSet->SetAbsolutePosition(current_pos);
			m_pSet->Edit();
			UpdateData(TRUE);
			m_pSet->m_fname = dlg.m_name;
			m_pSet->m_fphone = dlg.m_phone;
			m_pSet->m_femail = dlg.m_email;
			m_pSet->m_fgroup = dlg.m_group;
			m_pSet->m_frelation = dlg.m_relation;

			m_pSet->Update();
			m_pSet->Requery();
			m_pSet->SetAbsolutePosition(current_pos);
			UpdateData(FALSE);
			AddAllRecord();
	}
		Select();
}




void CJINYEOB_infoView::Select()
{
	CListCtrl* list;

	list = (CListCtrl*)GetDlgItem(IDC_LIST_ADDR);

	list->SetItemState(current_pos - 1, LVIS_SELECTED, LVIS_SELECTED);
	list->EnsureVisible(current_pos - 1, FALSE);
	list->SetFocus();
}


void CJINYEOB_infoView::OnBnClickedButtonDelete()
{
	if (record_count == 0) {
		MessageBox(_T("삭제할 데이터가 없습니다!"));
		return;
	}
	m_pSet->Delete(); // 삭제
	m_pSet->Requery(); // 삭제
	GetTotalRecordCount();
	if (record_count == 0) // 데이터가 존재하지 않으면..
	{
		m_pSet->SetFieldNull(NULL);
		UpdateData(FALSE);
		current_pos = 0;
		return;
	}
	if (record_count < current_pos) // 마지막 데이터 삭제시
		current_pos--;// current_pos = record_count;
	m_pSet->SetAbsolutePosition(current_pos);
	UpdateData(FALSE);
	AddAllRecord();
	Select();
}


void CJINYEOB_infoView::OnRecordFirst()
{
	if (record_count == 0)return;
	current_pos = 1;
	m_pSet->MoveFirst();
	UpdateData(FALSE);
	Select();
}


void CJINYEOB_infoView::OnRecordPrev()
{
	if (record_count == 0) return;
	current_pos--; // 현재 위치 값을 1감소시킴
	m_pSet->MovePrev(); // 이전 레코드 위치로 이동
	if (m_pSet->IsBOF()) {
		m_pSet->MoveFirst();
		current_pos = 1;
	}
	UpdateData(FALSE); // Recordset 변수 값을 컨트롤에 출력
	Select();
}


void CJINYEOB_infoView::OnRecordNext()
{
	if (record_count == 0)return;
	current_pos++;
	m_pSet->MoveNext();
	if (m_pSet->IsEOF())
	{
		m_pSet->MoveLast();
		current_pos--;
	}
	UpdateData(FALSE);
	Select();
}


void CJINYEOB_infoView::OnRecordLast()
{
	if (record_count == 0)return;
	current_pos = record_count;
	m_pSet->MoveLast();
	UpdateData(FALSE);
	Select();
}


void CJINYEOB_infoView::SetImageList(void) {
	m_LargeImageList.Create(IDB_BITMAP2, 48, 1, RGB(0, 0, 0));
	m_SmallImageList.Create(IDB_BITMAP1, 16, 1, RGB(0, 0, 0));
	m_List.SetImageList(&m_LargeImageList, LVSIL_NORMAL);
	m_List.SetImageList(&m_SmallImageList, LVSIL_SMALL);;
}

void CJINYEOB_infoView::OnIcon()
{
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_ICON);
}


void CJINYEOB_infoView::OnSmallicon()
{
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_SMALLICON);
}


void CJINYEOB_infoView::OnList()
{
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_LIST);
}


void CJINYEOB_infoView::OnReport()
{
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
}


void CJINYEOB_infoView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	CMenu *subMenu = menu.GetSubMenu(5);
	subMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}


void CJINYEOB_infoView::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);

	if (m_pSet->m_fname.IsEmpty() == false) {
		m_pSet->m_strFilter.Format(_T("fname like '%%%s%%'"), m_Search);
		int i = 0;
		m_pSet->Requery();
		m_pSet->m_strFilter.Empty();
		m_List.DeleteAllItems();

		while (m_pSet->IsEOF() == FALSE) {
			m_List.InsertItem(i, m_pSet->m_fname, 0);
			m_List.SetItemText(i, 1, m_pSet->m_femail);
			m_List.SetItemText(i, 2, m_pSet->m_fphone);
			m_List.SetItemText(i, 3, m_pSet->m_fgroup);
			m_List.SetItemText(i, 4, m_pSet->m_frelation);
			m_pSet->MoveNext();
			i++;
		}
		current_pos = record_count = i;
		m_pSet->SetAbsolutePosition(current_pos);
	}
	Select();
}



void CJINYEOB_infoView::OnLbnSelchangeListSearch()
{
	int Index = m_Box.GetCurSel();
	CString seldata;

	m_Box.GetText(Index, seldata);
	if (seldata == "전체") {
		AddAllRecord();
	}
	else {
		if (m_pSet->m_fname.IsEmpty() == false)
		{
			m_pSet->m_strFilter.Format(_T(" frelation like '%%%s%%'"), seldata);
			int i = 0;
			m_pSet->Requery(); m_pSet->m_strFilter.Empty();
			m_List.DeleteAllItems();
			CString strTemp;
			while (m_pSet->IsEOF() == FALSE) {
				m_List.InsertItem(i, m_pSet->m_fname, 0);
				m_List.SetItemText(i, 1, m_pSet->m_femail);
				m_List.SetItemText(i, 2, m_pSet->m_fphone);
				m_List.SetItemText(i, 3, m_pSet->m_fgroup);
				m_List.SetItemText(i, 4, m_pSet->m_frelation);
				m_pSet->MoveNext();
				i++;
			}
			current_pos = record_count = i;
			m_pSet->SetAbsolutePosition(current_pos);
		}
	}
	Select();
}
#include "ODBCAssetDlg.h"
void CJINYEOB_infoView::OnBnClickedButtonAsset()
{
	CODBCAssetDlg dlgg;
	int res = dlgg.DoModal();
}