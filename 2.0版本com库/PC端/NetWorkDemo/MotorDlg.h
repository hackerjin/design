#pragma once

#include "XRFNet_i.h"

class CMotorDlg : public ATL::CDialogImpl<CMotorDlg>
{
public:
	enum { IDD = IDD_MOTOR };

public:
	CMotorDlg(IMotorControl *pMotorControl);
	~CMotorDlg();

public:
	BEGIN_MSG_MAP(CMotorDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER(IDC_QUERY, BN_CLICKED, OnQuery)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
	END_MSG_MAP()

private:
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	LRESULT OnQuery(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
	IMotorControl		*m_pMotorControl;		
};
