
// JINYEOB_infoSet.cpp : CJINYEOB_infoSet 클래스의 구현
//

#include "stdafx.h"
#include "JINYEOB_info.h"
#include "JINYEOB_infoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJINYEOB_infoSet 구현

// 코드 생성 위치 2018년 11월 20일 화요일, 오후 4:59

IMPLEMENT_DYNAMIC(CJINYEOB_infoSet, CRecordset)

CJINYEOB_infoSet::CJINYEOB_infoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_fname = L"";
	m_femail = L"";
	m_fphone = L"";
	m_fgroup = L"";
	m_frelation = L"";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CJINYEOB_infoSet::GetDefaultConnect()
{
	return _T("DSN=informationDSN;DBQ=C:\\db\\my_information.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CJINYEOB_infoSet::GetDefaultSQL()
{
	return _T("[addressbook]");
}

void CJINYEOB_infoSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[fname]"), m_fname);
	RFX_Text(pFX, _T("[femail]"), m_femail);
	RFX_Text(pFX, _T("[fphone]"), m_fphone);
	RFX_Text(pFX, _T("[fgroup]"), m_fgroup);
	RFX_Text(pFX, _T("[frelation]"), m_frelation);

}
/////////////////////////////////////////////////////////////////////////////
// CJINYEOB_infoSet 진단

#ifdef _DEBUG
void CJINYEOB_infoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CJINYEOB_infoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

