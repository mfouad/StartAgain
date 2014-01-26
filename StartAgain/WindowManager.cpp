#include "stdafx.h"

#include "WindowManager.h"

CWindowManager	s_WindowManager;
const CString	strMetroClass = L"Windows.UI.Core.CoreWindow";
//const CString	strMetroClass = L"MetroGhostWindow"; //L"NativeHWNDHost";//
const CString	strStartMenuClass = L"ImmersiveLauncher";
const CString	strMetroBackgroundClass = L"ImmersiveBackgroundWindow";

CWindowManager::CWindowManager(void)
{
	m_iWidth = 500;
}


CWindowManager::~CWindowManager(void)
{
}


void CWindowManager::AddMetroWindow(HWND hwnd)
{
	//m_hwnd = hwnd;
	CAppWnd *pWnd = new  CMetroWnd(hwnd);
	m_windowList.push_back(pWnd);
}

void CWindowManager::AddDesktopWindow(HWND hwnd)
{
	//m_hwnd = hwnd;
	CAppWnd *pWnd = new CDesktopWnd(hwnd);
	m_windowList.push_back(pWnd);
}

void CWindowManager::Clear()
{
	m_windowList.clear();
}

void CWindowManager::EnumAllWindows()
{
	Clear();
	
	//EnumMetroWindows();
	EmumDesktopWindows();
	//EnumDummyWindows();

	OnContentChange();

}

void CWindowManager::EmumDesktopWindows()
{
	EnumWindows( [] (HWND hwnd, LPARAM lParam) -> BOOL
		{
			CWindowManager *pWndMgr = (CWindowManager *)lParam;
			CDesktopWnd wnd(hwnd);

			if (hwnd != pWndMgr->m_HostHwnd && wnd.IsTopmost())
				if (!IsExcluded(wnd))
					pWndMgr->AddDesktopWindow(hwnd);
			return TRUE;
	}  , (LPARAM)this);
}

bool CWindowManager::IsExcluded(CAppWnd wnd)
{
	if (wnd.Contains(_T("StartAgain")))
		return true;
}


void CWindowManager::EnumMetroWindows()
{
	HWND			hwndNext = NULL;
	
	hwndNext = NULL;
	while (true)
	{
		hwndNext = ::FindWindowEx(NULL, hwndNext, strMetroClass, NULL);
		if (hwndNext == NULL)
			break;
		AddMetroWindow(hwndNext);
	}
}

/*
void CWindowManager::EnumMetroWindows()
{
	HWND			hwndNext = NULL;
	
	hwndNext = NULL;
	while (true)
	{
		hwndNext = ::FindWindowEx(NULL, hwndNext, NULL, L"Deezer");
		if (hwndNext == NULL)
			break;
		AddMetroWindow(hwndNext);
	}
}
*/
HWND CWindowManager::GetWindowByClass(LPCWSTR szWndClass)
{
	HWND			hwndNext = NULL;
	
	hwndNext = NULL;
	hwndNext = ::FindWindowEx(NULL, hwndNext, szWndClass, NULL);
	return hwndNext;
	//AddWindow(hwndNext);
}



HWND CWindowManager::GetStart()
{
	
	return GetWindowByClass(strStartMenuClass);
	//AddWindow(hwndNext);
}


HWND CWindowManager::GetMetroBackground()
{
	return GetWindowByClass(strMetroBackgroundClass);
	//AddWindow(hwndNext);
	
}





void CWindowManager::Stack(int iScrollPos)
{
	WindowListIter	wnd;
	RECT			recHostWnd;

	CWnd *pHostWnd = CWnd::FromHandle(m_HostHwnd);
	pHostWnd->GetWindowRect(&recHostWnd);
	
	CRect rViewPort(recHostWnd);
	
	int cWindows = m_windowList.size();
	int iWidth = m_iWidth;//rViewPort.Width() / cWindows;
	int iHight = rViewPort.Height() - 200;
		
	int iLeft;
	int iRight;

	/*
	HWND hwndBack = GetMetroBackground();
	CMetroWnd backWnd(hwndBack);
	//backWnd.FixStyles();
	::SetWindowPos(hwndBack, HWND_TOP, rViewPort.left, rViewPort.top, rViewPort.Width() + 100, rViewPort.Height() + 100, SWP_NOACTIVATE);
	*/

	CRect rWnd;
	rWnd.SetRect(0, 100, 0, 0);
	rWnd.InflateRect(0, 0, iWidth, iHight);
	rWnd.OffsetRect(-iScrollPos, 0);

	for (wnd = m_windowList.begin(); wnd != m_windowList.end(); wnd++)
	{
		//::SetWindowPos(hwndBack, HWND_TOPMOST, rWnd.left, rWnd.top, rWnd.Width(), rWnd.Height(), SWP_NOACTIVATE );
		//::SetWindowPos((*wnd)->m_hwnd, HWND_TOPMOST, rViewPort.left, rViewPort.top, rViewPort.Width(), rViewPort.Height(), SWP_SHOWWINDOW);
		//(*wnd)->FixStyles();
		(*wnd)->Stack(rWnd);
		rWnd.OffsetRect(iWidth + 10, 0);
	}
	
	
	
}

void CWindowManager::SetHost(CWndHost* host)
{
	m_Host = host;
	m_HostHwnd = host->GetSafeHwnd();
}

void CWindowManager::OnContentChange()
{
	if (m_Host)
		m_Host->OnContentChange();
}

int CWindowManager::GetWidth()
{
	int cWindows = m_windowList.size();
	int iWidth = m_iWidth + 10;

	return cWindows* iWidth;
}

void CWindowManager::EnumDummyWindows()
{
	int icWindows = 10;
	RECT rect;
	
	for (int i = 0; i < icWindows; i++)
	{
		CStatic* pwnd = new CStatic();
		pwnd->Create(_T("my static"), WS_CHILD|WS_VISIBLE|SS_CENTER|SS_GRAYRECT|SS_SUNKEN | WS_CLIPSIBLINGS, CRect(10,50,100,100), m_Host, 1500+i);
		AddDesktopWindow(pwnd->GetSafeHwnd());
	}
}


