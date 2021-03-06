#pragma once
#include <GdiPlus.h>
#include "resource.h"

class ShadowBorderWnd :
	public CDialogImpl<ShadowBorderWnd>
{
public:
	enum { IDD = IDD_DIALOG_NONE };
	
	BEGIN_MSG_MAP_EX(ShadowBorderWnd)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_PAINT(OnPaint)
	END_MSG_MAP()
	ShadowBorderWnd(void);
	~ShadowBorderWnd(void);
	void OnPaint(CDCHandle dc);
	BOOL OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/);
	void Move(int x,int y,int w,int h);
    void SetRound(bool bRound);
    void SetMargin(int iLen);
    void InitImgShadow();
    int GetShadowWidth();
    int GetShadowHeight();
private:
	Gdiplus::Image* mImgShadow;
	bool mDrawed;
    bool mRound;
    int mMarginLen;
    int mShadowLeftWidth;
    int mShadowTopHeight;
    int mShadowTotalWidth;
    int mShadowTotalHeight;
    int mShadowWidthMid;
    int mShadowHeightMid;
};

template <class T>
class HaveShadowDlg : public CBkDialogImpl<T>
{
public:

	BEGIN_MSG_MAP_EX(HaveShadowDlg)
		MSG_WM_MOVE(OnMove)
        MSG_WM_SIZE(OnSize)
		MSG_WM_SHOWWINDOW(OnShowWindow)
		//MSG_WM_SYSCOMMAND(OnSysCommand)
		MSG_WM_DESTROY(OnDestroyWnd)
		//MSG_WM_ACTIVATE(OnActivate)
		MSG_WM_WINDOWPOSCHANGED(OnWindowPosChanging)
		CHAIN_MSG_MAP(CBkDialogImpl<T>)		
	END_MSG_MAP()
	HaveShadowDlg(UINT uResID = 0, bool bRound = false):CBkDialogImpl<T>(uResID)
	{
        mShadowWnd.SetRound(bRound);
        m_bInited = false;
        m_bShowWindowOnInit = true;
	}

    void OnSize(UINT nType, CSize size)
    {
        CBkDialogImpl<T>::OnSize(nType, size);
        if(mShadowWnd.IsWindow())
        {
            mShadowWnd.SetWindowPos(m_hWnd, 0, 0, size.cx + mShadowWnd.GetShadowWidth(), size.cy + mShadowWnd.GetShadowHeight(), SWP_NOMOVE|SWP_NOACTIVATE);
            mShadowWnd.UpdateWindow();
            mShadowWnd.Invalidate();
        }
    }

	void OnDestroyWnd()
	{
		mShadowWnd.DestroyWindow();
		mShadowWnd.m_hWnd = NULL;
		SetMsgHandled(FALSE);
	}
	void OnShowWindow(BOOL bShow, UINT nStatus)
	{
		mShadowWnd.ShowWindow(bShow?SW_SHOW:SW_HIDE);
		SetMsgHandled(FALSE);
	}
	void OnWindowPosChanging(LPWINDOWPOS lpWndPos)
	{
        if (!m_bInited && m_bShowWindowOnInit)
        {
            m_bInited = true;
            mShadowWnd.SetWindowPos(m_hWnd,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_SHOWWINDOW); 
        }
        else
        {
            mShadowWnd.SetWindowPos(m_hWnd,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE); 
        }
		SetMsgHandled(FALSE);
	}
	void OnMove(CPoint ptPos)
	{
		if(mShadowWnd.IsWindow())
		{
			RECT rect;
			GetWindowRect(&rect);
			mShadowWnd.Move(ptPos.x,ptPos.y,rect.right - rect.left,rect.bottom - rect.top);
		}
		SetMsgHandled(FALSE);
	}
	HWND Create(HWND hWndParent = ::GetActiveWindow(), LPRECT rect = NULL)
	{
		mShadowWnd.Create(hWndParent);
		mShadowWnd.ShowWindow(SW_HIDE);
		return __super::Create(hWndParent,rect);
	}
	UINT_PTR DoModal(HWND hWndParent = NULL, LPRECT rect = NULL)
	{
		mShadowWnd.Create(hWndParent);
		mShadowWnd.ShowWindow(SW_HIDE);
		return __super::DoModal(hWndParent,rect);
	}
    void SetShowWindowOnInit(bool bShow)
    {
        m_bShowWindowOnInit = bShow;
    }
protected:
	ShadowBorderWnd mShadowWnd;
    bool m_bInited;
    bool m_bShowWindowOnInit;
};