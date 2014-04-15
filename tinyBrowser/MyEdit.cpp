#include "stdafx.h"
#include "MyEdit.h"

CMyEdit::CMyEdit(CMainDlg * m)
		: mMainDlg(m)
{
	;
}

CMyEdit::~CMyEdit()
{
	mMainDlg =NULL;
}

void CMyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (VK_RETURN == nChar)
	{
		CString strText;
		GetWindowText(strText);
		m_strText = strText;
		mMainDlg->PostMessage(RSMSG_AYSN_OPEN_URL);
		//MessageBox(strText, TEXT("tesst"));
	}
	else
	{
		SetMsgHandled(false);
	}
}

CString CMyEdit::GetEditText()
{ 
	return m_strText;
}

BOOL CMyEdit::SetEditText(LPCTSTR lpszText)
{
	m_strText = lpszText;
	SetWindowText(m_strText);
	return TRUE;
}