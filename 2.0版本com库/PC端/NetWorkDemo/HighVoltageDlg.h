#pragma once

#include "XRFNet_i.h"

class CHighVoltageDlg : public ATL::CDialogImpl<CHighVoltageDlg>
{
public:
	enum { IDD = IDD_HIGH_VOLTAGE };

public:
	CHighVoltageDlg(IHighVoltage *pHighVoltage);
	~CHighVoltageDlg();

public:
	BEGIN_MSG_MAP(CHighVoltageDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER(IDC_SET, BN_CLICKED, OnSetType)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
		COMMAND_HANDLER(IDC_PILOT, BN_CLICKED, OnBnClickedPilot)
	END_MSG_MAP()

private:
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	LRESULT OnSetType(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedPilot(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
	IHighVoltage		*m_pHighVoltage;		
	BOOL				m_bOpen;
	BOOL				m_bOpenPilot;
};
