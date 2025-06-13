#pragma once

#include "XRFNet_i.h"
#include "DetectorCallback.h"

class CDetectorDlg : public ATL::CDialogImpl<CDetectorDlg>
{
public:
	enum { IDD = IDD_DETECTOR };

public:
	CDetectorDlg(IDetector *pDetector);
	~CDetectorDlg();
	
	void OnRead(UINT uQuickCount, UINT uSlowCount, UINT uSystemTime, UINT uLocalTime, const USHORT *pData, USHORT uLen);

public:
	BEGIN_MSG_MAP(CDetectorDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER(IDC_SET, BN_CLICKED, OnConfig)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
	END_MSG_MAP()

private:
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	LRESULT OnConfig(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
private:
	CDetectorCallBack	m_cb;
	IDetector			*m_pDetector;
	BOOL				m_bOpen;
};
