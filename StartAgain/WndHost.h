
// MainFrm.h : interface of the CWndHost class
//

#pragma once
#include "ChildView.h"

class CWndHost : public CFrameWnd
{
	
public:
	CWndHost();
protected: 
	DECLARE_DYNAMIC(CWndHost)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CWndHost();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	//CChildView    m_wndView;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnStack();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileWndlist();

	
	void UpdateScrolling();

	 private:
        // member variables to keep track of various 
        // screen dimensions
        int m_ViewWidth;
        int m_ViewHeight;
        int m_HScrollPos;
        int m_HPageSize;
    protected:
        // declare our handlers
		afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
        afx_msg void OnSize(UINT,int,int);
        afx_msg void OnHScroll(UINT,UINT,CScrollBar*);

        afx_msg BOOL OnMouseWheel(UINT,short,CPoint);


		// events
public:
	void OnContentChange();
		
};


