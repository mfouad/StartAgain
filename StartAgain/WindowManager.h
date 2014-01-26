#pragma once
#include<list>
using namespace std;

typedef list<CAppWnd*> WindowList;
typedef list<CAppWnd*>::iterator WindowListIter;

class CWindowManager
{
public:
	CWindowManager(void);
	~CWindowManager(void);
public:
	void EnumMetroWindows();
	void EnumDummyWindows();
	void EmumDesktopWindows();
	void EnumAllWindows();
	void AddMetroWindow(HWND hwnd);
	void AddDesktopWindow(HWND hwnd);
	void OnContentChange();
	static bool IsExcluded(CAppWnd wnd);

	HWND GetWindowByClass(LPCWSTR szWndClass);
HWND GetStart();
HWND GetMetroBackground();

	void Stack(int iScrollPos);
	
	void Clear();
	void SetHost(CWndHost* host);
	int GetWidth();
public:
	WindowList					m_windowList;
	CWndHost					*m_Host;
	HWND						m_HostHwnd;

	int							m_iWidth;
	int							m_iHeight;
};

extern CWindowManager	s_WindowManager;