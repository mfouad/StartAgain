
// MainFrm.cpp : implementation of the CWndHost class
//

#include "stdafx.h"
#include "StartAgainV2.h"
#include "WndList.h"

#include "WndHost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LINESIZE 10

// CWndHost

IMPLEMENT_DYNAMIC(CWndHost, CFrameWnd)

	BEGIN_MESSAGE_MAP(CWndHost, CFrameWnd)
		ON_WM_CREATE()
		ON_COMMAND(ID_STACK_STACK, &CWndHost::OnStack)
		ON_COMMAND(ID_FILE_WNDLIST, &CWndHost::OnFileWndlist)
		ON_WM_SIZE()
		//ON_WM_PAINT()
		ON_WM_HSCROLL()
		ON_WM_MOUSEWHEEL()
		ON_WM_SHOWWINDOW()

	END_MESSAGE_MAP()

	static UINT indicators[] =
	{
		ID_SEPARATOR,           // status line indicator
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
	};

	// CWndHost construction/destruction

	CWndHost::CWndHost()
	{
		m_HScrollPos = 0;
	}

	CWndHost::~CWndHost()
	{
	}

	int CWndHost::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;

		// create a view to occupy the client area of the frame
		/*	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW | WS_HSCROLL, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
		{
		TRACE0("Failed to create view window\n");
		return -1;
		}
		*/
		
		m_ViewWidth = 0;
		m_ViewHeight = 0;
		s_WindowManager.SetHost(this);
		return 0;
	}

	void CWndHost::OnShowWindow(BOOL bShow, UINT nStatus)
	{
	//	s_WindowManager.m_HostHwnd = GetSafeHwnd();
	//	s_WindowManager.EnumAllWindows();

	}

	void CWndHost::OnStack()
	{
		s_WindowManager.m_HostHwnd = GetSafeHwnd();
		s_WindowManager.EnumAllWindows();
	}


	

	BOOL CWndHost::PreCreateWindow(CREATESTRUCT& cs)
	{
		if( !CFrameWnd::PreCreateWindow(cs) )
			return FALSE;

		cs.style |= WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_MAXIMIZE | WS_HSCROLL | WS_CLIPSIBLINGS;
		//cs.style &= ~WS_CLIPCHILDREN;
		//cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

		// Size the window to 1/3 screen size and center it
		//cs.cy = ::GetSystemMetrics(SM_CYMAXIMIZED);
		//cs.cx = ::GetSystemMetrics(SM_CXMAXIMIZED);
	
		cs.lpszClass = AfxRegisterWndClass(0);
		return TRUE;
	}

#ifdef _DEBUG
	void CWndHost::AssertValid() const
	{
		CFrameWnd::AssertValid();
	}

	void CWndHost::Dump(CDumpContext& dc) const
	{
		CFrameWnd::Dump(dc);
	}
#endif //_DEBUG


	

	BOOL CWndHost::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
	{

		// let the view have first crack at the command
		//if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			//return TRUE;

		// otherwise, do default handling
		return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}


	void CWndHost::OnFileWndlist()
	{
		//if (nID == ID_FILE_WINDOWLIST)
		{
			CWndList dlg;
			dlg.DoModal();
		}

	}

	// this gets called on WM_SIZE
	void CWndHost::OnSize(UINT type,int x,int y)
	{
		// call base class OnSize
		CFrameWnd::OnSize(type,x,y);
		
		//OnContentChange();
		
	}

	void CWndHost::OnContentChange()
	{
		s_WindowManager.Stack(0);
		UpdateScrolling();
	}

	// called when a page is rendered or windows added or so, it just updates the size of scroll bars
	void CWndHost::UpdateScrolling()
	{
		m_ViewWidth = s_WindowManager.GetWidth();
		// update horizontal scroll bar info
		int HScrollMax = 0;

		RECT rectClient;
		GetClientRect(&rectClient);
		m_HPageSize = rectClient.right - rectClient.left;

		if (m_HPageSize < m_ViewWidth)
		{
			HScrollMax = m_ViewWidth - m_HPageSize - 1;
			
			m_HScrollPos = min(m_HScrollPos, m_ViewWidth - m_HPageSize - 1);
		}
		SCROLLINFO si;
		si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS | SIF_DISABLENOSCROLL;
		si.nMin = 0;
		si.nMax = HScrollMax;
		si.nPos = m_HScrollPos;
		si.nPage = m_HPageSize;
		SetScrollInfo(SB_HORZ, &si, TRUE);
	}

	// This gets called on a WM_PAINT

	// this is called on WM_HSCROLL
	void CWndHost::OnHScroll(UINT code,UINT pos,CScrollBar* sb)
	{
		// number of pixels to be scrolled
		int delta;
		// which sb msg was sent. Set delta accordingly
		switch(code)
		{
		case SB_LINELEFT:
			delta = -LINESIZE;
			break;
		case SB_PAGELEFT:
			delta = -m_HPageSize;
			break;
		case SB_THUMBTRACK:
			delta = static_cast<int>(pos) - m_HScrollPos;
			break;
		case SB_PAGERIGHT:
			delta = m_HPageSize;
			break;
		case SB_LINERIGHT:
			delta = LINESIZE;
			break;
		default:
			// ignore other messages
			return;
		}
		int scrollpos = m_HScrollPos + delta;
		int maxpos = m_ViewWidth - m_HPageSize;
		if( scrollpos < 0)
			delta = - m_HScrollPos;
		else
			if(scrollpos > maxpos)
				delta = maxpos - m_HScrollPos;
		// if we need to scroll do the scrolling
		if(delta != 0)
		{
			m_HScrollPos += delta;
			SetScrollPos(SB_HORZ,m_HScrollPos,TRUE);
			//ScrollWindowEx(-delta,0, NULL, NULL, NULL, NULL, SW_ERASE);
			//RedrawWindow(NULL, NULL, RDW_ERASE);
			s_WindowManager.Stack(m_HScrollPos);
		}
	}

	// this is called on WM_MOUSEWHEEL
	BOOL CWndHost::OnMouseWheel(UINT flags,short zdelta,CPoint point)
	{
		BOOL up = TRUE;
		int delta = zdelta;
		if(zdelta < 0)
		{
			up = FALSE;
			delta = - delta;
		}
		UINT WheelScrollLines;
		// get from the OS the number of wheel scrolllines. win95 doesnt support this call
		::SystemParametersInfo(SPI_GETWHEELSCROLLLINES,0,&WheelScrollLines,0);
		// scroll a page at a time
		if(WheelScrollLines == WHEEL_PAGESCROLL)
		{
			SendMessage(WM_HSCROLL,MAKEWPARAM((up)? SB_PAGELEFT:SB_PAGERIGHT,0),0);
		}
		else
			// or scroll numlines
		{
			int numlines = (delta * WheelScrollLines) / WHEEL_DELTA;
			while ( numlines-- )
				SendMessage(WM_HSCROLL,MAKEWPARAM((up)? SB_LINELEFT:SB_LINERIGHT,0),0);
		}
		return TRUE;
	}