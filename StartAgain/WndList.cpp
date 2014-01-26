// WndList.cpp : implementation file
//

#include "stdafx.h"
#include "StartAgainV2.h"
#include "WndList.h"
#include "afxdialogex.h"
#include "WindowManager.h"
#include <algorithm>
using namespace std;
// CWndList dialog

IMPLEMENT_DYNAMIC(CWndList, CDialogEx)

CWndList::CWndList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWndList::IDD, pParent)
{
	
	//MessageBox(strWindows);
}

CWndList::~CWndList()
{
}

void CWndList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CWndList, CDialogEx)
	ON_BN_CLICKED(IDOK, &CWndList::OnBnClickedOk)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CWndList::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CWndList message handlers

void CWndList::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


//void CWndList::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}


BOOL CWndList::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_List.InsertColumn(0, L"Caption", 0, 100);
	m_List.InsertColumn(1, L"Class", 0, 100);
	m_List.InsertColumn(2, L"HWND", 0, 100);
	m_List.InsertColumn(3, L"Style", 0, 100);
	m_List.InsertColumn(4, L"ExStyle", 0, 100);

	s_WindowManager.EnumAllWindows();

	for_each(s_WindowManager.m_windowList.begin(), s_WindowManager.m_windowList.end(), [this](CAppWnd *appWnd){ AddItem(appWnd->m_hwnd);});
	
	//int x= m_List.GetCount();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CWndList::AddItem(HWND hwnd)
{
			CString strName;
			LONG lval;
			wchar_t	szClassName[MAX_PATH];
			GetClassName(hwnd, szClassName, MAX_PATH);

			CWnd* wnd = CWnd::FromHandle(hwnd);
			wnd->GetWindowTextW(strName);

			
		//	if (strName.Trim().GetLength() > 0)
			{
				int iCount = m_List.GetItemCount();
				
				m_List.InsertItem(iCount, strName);

				LVITEM item;
				item.iItem = iCount;
				item.mask = LVIF_TEXT;
				item.iSubItem = 1;
				item.pszText = _tcsdup(szClassName);
				m_List.SetItem(&item);

				// hwnd
				_stprintf_s(szClassName, _T("%x"), (int)hwnd);
				item.iSubItem = 2;
				item.pszText = _tcsdup(szClassName);
				m_List.SetItem(&item);
				
				// Style
				lval = ::GetWindowLongPtr(hwnd, GWL_STYLE);
				_stprintf_s(szClassName, _T("0x%.8x"), (int)lval);
				item.iSubItem = 3;
				item.pszText = _tcsdup(szClassName);
				m_List.SetItem(&item);

				// ex style
				lval = ::GetWindowLongPtr(hwnd, GWL_EXSTYLE);
				_stprintf_s(szClassName, _T("0x%.8x"), (int)lval);
				item.iSubItem = 4;
				item.pszText = _tcsdup(szClassName);
				m_List.SetItem(&item);

			}

}

