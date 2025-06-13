#pragma once

#include "XRFNet_i.h"

class CRayTubeDlg : public ATL::CDialogImpl<CRayTubeDlg>
{
public:
	enum { IDD = IDD_RAYTUBE };

public:
	CRayTubeDlg(IXRFRayTube *pRayTube);
	~CRayTubeDlg();

public:
	BEGIN_MSG_MAP(CRayTubeDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER(IDC_SET, BN_CLICKED, OnSetInfo)
		COMMAND_HANDLER(IDC_GET, BN_CLICKED, OnGetInfo)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
	END_MSG_MAP()

private:
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	LRESULT OnSetInfo(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnGetInfo(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
private:
	IXRFRayTube		*m_pRayTube;		
	BOOL			m_bOpen;
};
