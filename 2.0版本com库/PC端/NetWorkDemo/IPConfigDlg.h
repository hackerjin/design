#pragma once

class CIPConfigDlg : public ATL::CDialogImpl<CIPConfigDlg>
{
public:
	enum { IDD = IDD_IP_CONFIG };

public:
	CIPConfigDlg();
	~CIPConfigDlg();

public:
	BEGIN_MSG_MAP(CIPConfigDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
		COMMAND_HANDLER(IDC_GET_IP, BN_CLICKED, OnBnClickedGetIp)
		COMMAND_HANDLER(IDC_SET_IP, BN_CLICKED, OnBnClickedSetIp)
		COMMAND_HANDLER(IDC_GET_PORT, BN_CLICKED, OnBnClickedGetPort)
	END_MSG_MAP()

private:
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedGetIp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedSetIp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedGetPort(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);	
};
