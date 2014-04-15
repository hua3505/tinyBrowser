#pragma once

#include <bkwin/bkimage.h>
#include <bkwin/bkskin.h>

class CWHEdit
	: public CWindowImpl<CWHEdit, CEdit>
{
public:
	CWHEdit()
		: m_crBg(CLR_DEFAULT),mBrush(NULL)
	{

	}
	~CWHEdit()
	{
		if(mBrush != NULL)
		{
			DeleteObject(mBrush);
			mBrush = NULL;
		}
	}

	void SetBkColor(COLORREF crBg)
	{
		m_crBg = crBg;

		Invalidate(TRUE);
	}

protected:
	COLORREF m_crBg;
	HBRUSH mBrush;

	HBRUSH OnReflectedCtlColor(CDCHandle dc, HWND /*hWnd*/)
	{
		if (CLR_DEFAULT == m_crBg)
		{
			SetMsgHandled(FALSE);
			return NULL;
		}

		dc.SetBkColor(m_crBg);
		if(mBrush == NULL)
			mBrush = ::CreateSolidBrush(m_crBg);
		return mBrush;
	}

public:
	BEGIN_MSG_MAP(CWHEdit)
		MSG_OCM_CTLCOLORSTATIC(OnReflectedCtlColor)
		MSG_OCM_CTLCOLOREDIT(OnReflectedCtlColor)
	END_MSG_MAP()
};