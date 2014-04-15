#include "stdafx.h"
#include "BrowserWnd.h"

CTinyHtmlContainerWindow::CTinyHtmlContainerWindow(CMainDlg * m)
							: m_MainDlg(m)
{

}

CTinyHtmlContainerWindow::~CTinyHtmlContainerWindow()
{
	m_MainDlg = NULL;
}

//void WINAPI CTinyHtmlContainerWindow::BeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags,
//									VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
//{
//	//CString sURL;
//	//sURL = URL->bstrVal;
//	//m_strUrl = sURL;
//	m_strUrl = GetLocationUrl();
//	//m_strUrl = __super.getLocationURL();
//	m_MainDlg->PostMessage(RSMSG_AYSN_NAVIGATE);
//	//OnVisitePage(sURL, Cancel, TargetFrameName->bstrVal);
//}

void WINAPI CTinyHtmlContainerWindow::NavigateComplete2WebAdinfo(LPDISPATCH pDisp, VARIANT* URL)
{
	if (!m_bNavigateError)
	{
		m_wndIE.ShowWindow(SW_SHOW);
	}
	m_strUrl = GetLocationUrl();
	m_MainDlg->PostMessage(RSMSG_AYSN_NAVIGATE);
}

CString CTinyHtmlContainerWindow::GetUrl()
{
	return m_strUrl;
}