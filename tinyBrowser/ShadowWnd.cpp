#include "stdafx.h"
#include "ShadowWnd.h"
#include "MainDlg.h"
ShadowBorderWnd::ShadowBorderWnd(void)
{
	mImgShadow = NULL;
	mDrawed = false;
    mRound = false;
    mShadowLeftWidth = 0;
    mShadowTopHeight = 0;
    mShadowTotalWidth = 0;
    mShadowTotalHeight = 0;
    mShadowWidthMid = 0;
    mShadowHeightMid = 0;
    mMarginLen = 0;
}
ShadowBorderWnd::~ShadowBorderWnd(void)
{
}
void DrawImageDot9(Gdiplus::Graphics* g,Gdiplus::Image* img,int x,int y,int w,int h,int wd,int hd)//采用点9方式自动拉伸图片
{
	ATLASSERT(g && img);	
	int wl = img->GetWidth() - wd - 1;//右侧不拉伸宽度
	int hl = img->GetHeight() - hd - 1;//下侧不拉伸长度
	int midw = w - wd - wl;
	int midh = h - hd - wl;
	
	g->DrawImage(img,Gdiplus::Rect(0,0,wd,hd),0,0,wd,hd,Gdiplus::UnitPixel);//左上	
	g->DrawImage(img,Gdiplus::Rect(wd,0,midw,hd),wd,0,1,hd,Gdiplus::UnitPixel);	//上
	g->DrawImage(img,Gdiplus::Rect(wd + midw,0,wl,hd),wd + 1,0,wl,hd,Gdiplus::UnitPixel);//右上
	g->DrawImage(img,Gdiplus::Rect(0,hd,wd,midh),0,hd,wd,1,Gdiplus::UnitPixel);//左	
	g->DrawImage(img,Gdiplus::Rect(wd,hd,midw,midh),wd,hd,1,1,Gdiplus::UnitPixel);//中
	g->DrawImage(img,Gdiplus::Rect(wd + midw,hd,wl,midh),wd + 1,hd,wl,1,Gdiplus::UnitPixel);//右
	g->DrawImage(img,Gdiplus::Rect(0,hd + midh,wd,hl),0,hd + 1,wd,hl,Gdiplus::UnitPixel);//左下
	g->DrawImage(img,Gdiplus::Rect(wd,hd + midh,midw,hl),wd,hd + 1,1,hl,Gdiplus::UnitPixel);	//下
	g->DrawImage(img,Gdiplus::Rect(wd + midw,hd + midh,wl,hl),wd + 1,hd + 1,wl,hl,Gdiplus::UnitPixel);//右下
}

void DrawImageDot9Ex(Gdiplus::Graphics* g,Gdiplus::Image* img,int w,int h,int ileft,int itop,int iright,int ibottom)//采用点9方式自动拉伸图片
{
    ATLASSERT(g && img);	
    int iDestMidW = w - ileft - iright;
    int iDestMidH = h - itop - ibottom;
    int iSrcMidW = img->GetWidth() - ileft - iright;       
    int iSrcMidH = img->GetHeight() - itop - ibottom;


    g->DrawImage(img, 
        Gdiplus::Rect(0, 0, ileft, itop), 
        0, 
        0,
        ileft,
        itop, 
        Gdiplus::UnitPixel); //左上
    g->DrawImage(img, 
        Gdiplus::Rect(ileft, 0, iDestMidW, itop), 
        ileft,
        0, 
        iSrcMidW,
        itop,
        Gdiplus::UnitPixel);//上
    g->DrawImage(img,
        Gdiplus::Rect(ileft + iDestMidW, 0, iright, itop),
        ileft + iSrcMidW,
        0,
        iright,
        itop,
        Gdiplus::UnitPixel);//右上

    g->DrawImage(img,
        Gdiplus::Rect(0, itop, ileft, iDestMidH),
        0,
        itop,
        ileft,
        iSrcMidH,
        Gdiplus::UnitPixel);//左
    g->DrawImage(img,
        Gdiplus::Rect(ileft, itop, iDestMidW, iDestMidH),
        ileft,
        itop,
        iSrcMidW,
        iSrcMidH,
        Gdiplus::UnitPixel);//中
    g->DrawImage(img,
        Gdiplus::Rect(ileft + iDestMidW, itop, iright, iDestMidH),
        ileft + iSrcMidW,
        itop,
        iright,
        iSrcMidH,
        Gdiplus::UnitPixel);//右

    g->DrawImage(img,
        Gdiplus::Rect(0, itop + iDestMidH, ileft, ibottom),
        0,
        itop + iSrcMidH,
        ileft,
        ibottom,
        Gdiplus::UnitPixel);//左下
    g->DrawImage(img,
        Gdiplus::Rect(ileft, itop + iDestMidH, iDestMidW, ibottom),
        ileft,
        itop + iSrcMidH,
        iSrcMidW,
        ibottom, 
        Gdiplus::UnitPixel);//下
    g->DrawImage(img,
        Gdiplus::Rect(ileft + iDestMidW, itop + iDestMidH, iright, ibottom),
        ileft + iSrcMidW,
        itop + iSrcMidH,
        iright,
        ibottom,
        Gdiplus::UnitPixel);//右下
}

void ShadowBorderWnd::OnPaint(CDCHandle dc)
{	
	CPaintDC hdc(m_hWnd);
// 	Gdiplus::Graphics g(hdc);
// 	g.DrawImage(mRomIcon,0,0);
	if(mImgShadow == NULL)return;
	POINT DestPt = {0,0};
	RECT rect;
	GetWindowRect(&rect);
	SIZE psize = {rect.right - rect.left,rect.bottom - rect.top};
	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;
	HDC hDC = GetDC();
	HDC hMemDC=::CreateCompatibleDC(hDC);
	BITMAPINFO bitmapinfo;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biBitCount = 32;
	bitmapinfo.bmiHeader.biHeight = psize.cy;
	bitmapinfo.bmiHeader.biWidth = psize.cx;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biCompression=BI_RGB;
	bitmapinfo.bmiHeader.biXPelsPerMeter=0;
	bitmapinfo.bmiHeader.biYPelsPerMeter=0;
	bitmapinfo.bmiHeader.biClrUsed=0;
	bitmapinfo.bmiHeader.biClrImportant=0;
	bitmapinfo.bmiHeader.biSizeImage = bitmapinfo.bmiHeader.biWidth * bitmapinfo.bmiHeader.biHeight * bitmapinfo.bmiHeader.biBitCount / 8;
	HBITMAP hBitmap=::CreateDIBSection (hMemDC,&bitmapinfo, 0,NULL, 0, 0);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject (hMemDC,hBitmap);
	//Ellipse(hMemDC,0,0,psize.cx,psize.cy);
	Gdiplus::Graphics g(hMemDC);
    if (mRound)
        DrawImageDot9Ex(&g,mImgShadow,
        psize.cx,
        psize.cy,
        mShadowLeftWidth + 4,
        mShadowTopHeight + 4,
        mShadowTotalWidth - mShadowLeftWidth + 4,
        mShadowTotalHeight - mShadowTopHeight + 4);
    else
        DrawImageDot9(&g,mImgShadow,0,0,psize.cx,psize.cy,mShadowWidthMid,mShadowHeightMid);
	::UpdateLayeredWindow(m_hWnd,hDC,NULL,&psize,hMemDC,&DestPt,0,&blendFunc32bpp,ULW_ALPHA);
	::SelectObject (hMemDC,hOldBitmap);
	DeleteObject(hMemDC);
	DeleteObject(hBitmap);
	ReleaseDC(hDC);
}
BOOL ShadowBorderWnd::OnInitDialog(CWindow /*wndFocus*/, LPARAM lInitParam)
{
	ModifyStyleEx(0,WS_EX_LAYERED|WS_EX_TRANSPARENT);
    InitImgShadow();
	//mImgShadow = BkPngPool::Get(1000); //new Gdiplus::Image(_T("d:\\1.png"));
	//ShowWindow(SW_SHOW);
	return TRUE;
}
void ShadowBorderWnd::Move(int x,int y,int w,int h)
{
	if(mImgShadow && w > 0 && h > 0)
	{
        //RECT rect;
        //GetWindowRect(&rect);
		SetWindowPos(NULL, x - mShadowLeftWidth + mMarginLen, y - mShadowTopHeight + mMarginLen, w + mShadowTotalWidth - 2 * mMarginLen, h + mShadowTotalHeight - 2 * mMarginLen, SWP_NOACTIVATE|SWP_NOZORDER|(mDrawed?SWP_NOSIZE:0));
		if(!mDrawed)
		{
			mDrawed = true;
			OnPaint(NULL);
		}		
		ShowWindow(SW_SHOW);
	}
}

void ShadowBorderWnd::SetRound(bool bRound)
{
    mRound = bRound;
    InitImgShadow();
}

void ShadowBorderWnd::SetMargin(int iLen)
{
    mMarginLen = iLen;
}

void ShadowBorderWnd::InitImgShadow()
{
    if (mRound)
    {
        mImgShadow = BkPngPool::Get(1004);
        mShadowLeftWidth = 34;
        mShadowTopHeight = 27;
        mShadowTotalWidth = 68;
        mShadowTotalHeight = 70;
        mShadowWidthMid = 52;
        mShadowHeightMid = 40;
    }
    else
    {
        mImgShadow = BkPngPool::Get(1000);
        mShadowLeftWidth = 11;
        mShadowTopHeight = 6;
        mShadowTotalWidth = 22;
        mShadowTotalHeight = 22;
        mShadowWidthMid = 30;
        mShadowHeightMid = 20;
    }
}

int ShadowBorderWnd::GetShadowWidth()
{
    return mShadowTotalWidth;
}

int ShadowBorderWnd::GetShadowHeight()
{
    return mShadowTotalHeight;
}
