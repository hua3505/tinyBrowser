#pragma once

#include "stdafx.h"
#include "wtlhelper/whwindow.h"

class CMainDlg;

class CMyEdit
	: public CWHEdit
{
public:
	CMyEdit(CMainDlg * m);
	~CMyEdit();
	CString GetEditText();
	BOOL SetEditText(LPCTSTR lpszText);
	BEGIN_MSG_MAP_EX(CMyEdit)
		MSG_WM_KEYDOWN(OnKeyDown)
	END_MSG_MAP()

protected:
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	CString m_strText;
	CMainDlg * mMainDlg;
};