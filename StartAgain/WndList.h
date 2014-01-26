#pragma once
#include "afxwin.h"
#include <functional>
#include "afxcmn.h"
using namespace std;
// CWndList dialog

class CWndList : public CDialogEx
{
	DECLARE_DYNAMIC(CWndList)

public:
	CWndList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWndList();

// Dialog Data
	enum { IDD = IDD_WNDLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void AddItem(HWND hwnd);
	void EmumDesktopWindows();
	void EnumMetroWindows();
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);

private:
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
};
