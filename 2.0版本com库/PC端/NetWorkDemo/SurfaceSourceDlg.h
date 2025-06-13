#pragma once

#include "XRFNet_i.h"

class CSurfaceSourceDlg : public ATL::CDialogImpl<CSurfaceSourceDlg>
{
public:
	enum { IDD = IDD_SURFACE_SOURCE };

public:
	CSurfaceSourceDlg(ISurfaceSource *pSurfaceSource);
	~CSurfaceSourceDlg();

public:
	BEGIN_MSG_MAP(CSurfaceSourceDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
	END_MSG_MAP()

private:
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
	ISurfaceSource		*m_pSurfaceSource;		
};
