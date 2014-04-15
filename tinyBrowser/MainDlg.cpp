#include "stdafx.h"
#include "MainDlg.h"

int CDECL MessageBoxPrintf(TCHAR * szCaption, TCHAR * szFormat, ...)
{
	TCHAR szBuffer[1024];
	va_list pArgList;

	va_start(pArgList, szFormat);
	_vsntprintf(szBuffer, sizeof(szBuffer) / sizeof(TCHAR), szFormat, pArgList);
	va_end(pArgList);

	return MessageBox(NULL, szBuffer, szCaption, 0);
}

CMainDlg::CMainDlg():CBkDialogImpl<CMainDlg>(IDR_BK_MAIN_DIALOG)
{
	m_whEdit = new CMyEdit(this);
	m_ctlWeb = new CTinyHtmlContainerWindow(this);
}

CMainDlg::~CMainDlg()
{
	if (m_whEdit)
	{
		delete m_whEdit;
		m_whEdit = NULL;
	}
	if (m_ctlWeb)
	{
		delete m_ctlWeb;
		m_ctlWeb = NULL;
	}
}

//最小化按钮
void CMainDlg::OnMinBtnClick()
{
	ShowWindow(SW_SHOWMINIMIZED);
}

//关闭按钮
void CMainDlg::OnBtnClose()
{
	EndDialog(IDCANCEL);
}

//后退
void CMainDlg::OnGoBack()
{
	m_ctlWeb->GoBack();
}

void CMainDlg::OnGoForward()
{
	m_ctlWeb->GoForward();
}

void CMainDlg::OnRefresh()
{
	m_ctlWeb->Refresh();
}

void CMainDlg::OnGoHome()
{
	m_ctlWeb->Show2(_T("http://www.baidu.com/"), _T("about:blank"));
}

LRESULT CMainDlg::OnOpenUrl(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//MessageBox(m_whEdit->GetEditText(), _T("url"));
	CString strUrl = m_whEdit->GetEditText();
	//MessageBoxPrintf(_T("url"), _T("index is %d"), strUrl.Find(_T("http://")));
	if (0 == strUrl.Find(_T("http://")))
	{
		m_ctlWeb->Show2(strUrl, _T("about:blank"));
	}
	else
	{
		strUrl = _T("https://www.google.com.hk/#q=") + strUrl;
		m_ctlWeb->Show2(strUrl, _T("about:blank"));
	}
	return 1L;
}

LRESULT CMainDlg::OnNavigate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CString strUrl = m_ctlWeb->GetUrl();
	m_whEdit->SetEditText(strUrl);
	UpdateWindow();
	return 1L;
}

//系统命令
LRESULT CMainDlg::OnCommand(UINT wParam, CPoint point)
{
	switch(wParam)
	{
	case SC_CLOSE :
		EndDialog(IDCANCEL);
		break;
	}				
	DefWindowProc();
	return 0;
}

//对话框初始化
BOOL CMainDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	SetIcon(::LoadIcon((HMODULE)&__ImageBase, MAKEINTRESOURCE(IDI_BIG)));
	SetIcon(::LoadIcon((HMODULE)&__ImageBase, MAKEINTRESOURCE(IDI_SMALL)), FALSE);

	DWORD dwEditFlags = WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_LEFT | ES_AUTOHSCROLL;
	m_whEdit->Create( GetViewHWND(), NULL, NULL, dwEditFlags, WS_EX_NOPARENTNOTIFY, IDC_ADDRESS_EDIT, NULL);

	m_whEdit->SetFont(BkFontPool::GetFont(static_cast<WORD>(CBkObject::HexStringToULong("0400"))/*BKF_DEFAULTFONT*/));
	m_whEdit->SetBkColor(0xFFFFFF);
	m_whEdit->SetWindowText(_T(""));
	//m_whEdit->SetLimitText(20);
	m_whEdit->SetFocus();
	m_whEdit->ShowCaret();
	//m_whEdit->ShowWindow(SW_SHOW);
	
	
	if(!m_ctlWeb->Create(GetViewHWND(), 601, FALSE, RGB(0xFB, 0xFC, 0xFD)))
	{
		; 
	}
	else
	{
		CString	strURL;
		m_ctlWeb->SetOpenInWindow(TRUE);
		m_ctlWeb->Show2(_T("http://www.baidu.com/"), _T("about:blank"));
	}

	return TRUE;
}

void CMainDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (VK_F5  == nChar)
	{
		OnRefresh();
	}
}
