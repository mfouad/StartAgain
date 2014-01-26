#pragma once

class CAppWnd: public CWnd
{
public:
	CAppWnd(HWND);
	virtual ~CAppWnd(void);

	void Stack(CRect& rectTarget);
	void FixStyles();

	bool IsTopmost();
	bool IsWindowName(CString strName);
	bool Contains(CString strName);
	bool Restore();

public:
	HWND m_hwnd;
};

