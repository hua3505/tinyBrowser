#pragma once

#include "stdafx.h"
#include "wtlhelper/whwindow.h"

class CMainDlg;

class CTinyHtmlContainerWindow
	: public CWHHtmlContainerWindow
{
private:
	CMainDlg * m_MainDlg;
	CString m_strUrl;

public:
	CTinyHtmlContainerWindow(CMainDlg * m);
	virtual ~CTinyHtmlContainerWindow();
	CString GetUrl();

protected:
	//void WINAPI BeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);
	void WINAPI NavigateComplete2WebAdinfo(LPDISPATCH pDisp, VARIANT* URL);
};