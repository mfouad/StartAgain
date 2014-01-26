#include "stdafx.h"
#include "AppWnd.h"


CAppWnd::CAppWnd(HWND hwnd)
{
	m_hwnd = hwnd;
}


CAppWnd::~CAppWnd(void)
{
}

void CAppWnd::FixStyles()
{
	LONG lStyle;
	lStyle = ::GetWindowLongPtr(m_hwnd, GWL_STYLE);
	lStyle = lStyle | WS_OVERLAPPED & ~WS_POPUP | WS_CLIPCHILDREN & ~WS_VISIBLE;
	::SetWindowLong(m_hwnd, GWL_STYLE, lStyle);

	lStyle = ::GetWindowLongPtr(m_hwnd, GWL_EXSTYLE);
	lStyle = lStyle & ~WS_EX_TOPMOST;
	::SetWindowLong(m_hwnd, GWL_EXSTYLE, lStyle);


}

void CAppWnd::Stack(CRect& rectTarget)
{
	Restore();
	
	if (rectTarget)
	::SetWindowPos(m_hwnd, HWND_TOPMOST,//HWND_TOP,
		rectTarget.left, rectTarget.top, rectTarget.Width(), rectTarget.Height(),
		 SWP_ASYNCWINDOWPOS | SWP_SHOWWINDOW | SWP_NOCOPYBITS );
	
}

bool CAppWnd::IsTopmost()
{
	LONG lStyle;
	LONG lExStyle;
	bool bHasTitlebar = false;
	bool bIsVisible = false;
	
	lStyle = ::GetWindowLongPtr(m_hwnd, GWL_STYLE);
	lExStyle = ::GetWindowLongPtr(m_hwnd, GWL_EXSTYLE);
	
	if (lStyle & WS_CHILDWINDOW)
		return false;

	//| WS_VISIBLE
	//(lExStyle & WS_EX_APPWINDOW) || 
	bHasTitlebar = ((lStyle & WS_CAPTION) == WS_CAPTION);
	bIsVisible = ((lStyle & WS_VISIBLE) == WS_VISIBLE);
	return bHasTitlebar && bIsVisible;

	/*
	lStyle = lStyle | WS_OVERLAPPED & ~WS_POPUP | WS_CLIPCHILDREN & ~WS_VISIBLE;
	::SetWindowLong(m_hwnd, GWL_STYLE, lStyle);

	lStyle = ::GetWindowLongPtr(m_hwnd, GWL_EXSTYLE);
	lStyle = lStyle & ~WS_EX_TOPMOST;
	::SetWindowLong(m_hwnd, GWL_EXSTYLE, lStyle);
	*/
}


bool CAppWnd::Restore()
{
	return ::ShowWindow(m_hwnd, SW_SHOWNOACTIVATE);
}


bool CAppWnd::IsWindowName(CString strName)
{
	CString str;
	GetWindowText(str);

	return str == strName;
}


bool CAppWnd::Contains(CString strName)
{
	CString str;
	GetWindowText(str);

	return str.Find(strName) > -1;
}
