// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#include "wtlhelper/whwindow.h"
#include "MyEdit.h"
#include "BrowserWnd.h"
#include "ShadowWnd.h"

#pragma once

int CDECL MessageBoxPrintf(TCHAR * szCaption, TCHAR * szFormat, ...);

class CMyEdit;

class CMainDlg  : public CBkDialogImpl<CMainDlg>
				, public CWHRoundRectFrameHelper<CMainDlg>
				, public IDispEventImpl<IDC_IE_ONLINE_INFO, CMainDlg>
{
public:
	CMainDlg();
	~CMainDlg();

	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_CLOSE, OnBtnClose)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_MIN, OnMinBtnClick)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_GOBACK, OnGoBack)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_GOFORWARD, OnGoForward);
		BK_NOTIFY_ID_COMMAND(IDC_BTN_REFRESH, OnRefresh);
		BK_NOTIFY_ID_COMMAND(IDC_BTN_GOHOME, OnGoHome);
	BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP(CMainDlg)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CBkDialogImpl<CMainDlg>)
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CMainDlg>)  //ÊµÏÖÔ²½Ç´°¿Ú
		MSG_WM_SYSCOMMAND(OnCommand)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_KEYDOWN(OnKeyDown)
		MESSAGE_HANDLER_EX(RSMSG_AYSN_OPEN_URL, OnOpenUrl)
		MESSAGE_HANDLER_EX(RSMSG_AYSN_NAVIGATE, OnNavigate)
	END_MSG_MAP()

	BEGIN_SINK_MAP(CMainDlg)
		//SINK_ENTRY(IDC_IE_ONLINE_INFO, DISPID_NEWWINDOW, OnNewWindow)
		
	END_SINK_MAP()

protected:
	LRESULT OnCommand(UINT wParam, CPoint point);
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	void OnBtnClose();
	void OnMinBtnClick();
	void OnGoBack();
	void OnGoForward();
	void OnRefresh();
	void OnGoHome();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	LRESULT OnOpenUrl(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnNavigate(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//void __stdcall OnNewWindow(IDispatch **ppDisp, VARIANT_BOOL* Cancel);
	CMyEdit * m_whEdit;
	CTinyHtmlContainerWindow * m_ctlWeb;
	//CEdit m_addrEdit;
};
