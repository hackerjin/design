// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "XRFNet_i.h"
#include "NetworkCallBack.h"

class CMainDlg : public CDialogImpl<CMainDlg>
			   , public CUpdateUI<CMainDlg>
			   , public CMessageFilter
			   , public CIdleHandler
			   , public INetworkCallBack
{
public:
	enum { IDD = IDD_MAINDLG };

public:
	CMainDlg();
	~CMainDlg();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();
	
public:
	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_CONSOLE, BN_CLICKED, OnBnClickedConsole)
		COMMAND_HANDLER(IDC_SERVER_CONTROL, BN_CLICKED, OnBnClickedServerControl)
		COMMAND_HANDLER(IDC_REMOTE_CONTROL, BN_CLICKED, OnBnClickedRemoteControl)
		COMMAND_HANDLER(IDC_APPARATUS_CONTROL, BN_CLICKED, OnBnClickedApparatusControl)
		COMMAND_HANDLER(IDC_IP_CONFIG, BN_CLICKED, OnBnClickedIpConfig)
		COMMAND_HANDLER(IDC_RAYTUBE, BN_CLICKED, OnBnClickedRaytube)
		COMMAND_HANDLER(IDC_HIGHVOLTAGE, BN_CLICKED, OnBnClickedHighvoltage)
		COMMAND_HANDLER(IDC_VACUUM_PUMP, BN_CLICKED, OnBnClickedVacuumPump)
		COMMAND_HANDLER(IDC_MOTOR, BN_CLICKED, OnBnClickedMotor)
		COMMAND_HANDLER(IDC_ELECTROMAGNET, BN_CLICKED, OnBnClickedElectromagnet)
		COMMAND_HANDLER(IDC_HEIGHT_LASER, BN_CLICKED, OnBnClickedHeightLaser)
		COMMAND_HANDLER(IDC_SURFACE_SOURCE, BN_CLICKED, OnBnClickedSurfaceSource)
		COMMAND_HANDLER(IDC_DETECTOR, BN_CLICKED, OnBnClickedDetector)
	END_MSG_MAP()

private:
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedConsole(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedServerControl(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedRemoteControl(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedApparatusControl(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedIpConfig(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedRaytube(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedHighvoltage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedVacuumPump(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedMotor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedElectromagnet(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedHeightLaser(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedSurfaceSource(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedDetector(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
	HRESULT __stdcall QueryInterface(const struct _GUID& iid,void** ppv);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall OnConnected();
	HRESULT __stdcall OnDisconnect();
	HRESULT __stdcall OnRemoteConnected();
	HRESULT __stdcall OnRemoteDisconnected();
	HRESULT __stdcall OnRemoteServerDisconnected();

private:
	void CloseDialog(int nVal);

private:
	BOOL				m_bShowConsol;
	//CNetworkCallBack	m_cb;
	IXRFNetwork			*m_pNetWork;

	BOOL				m_bStartup;
	BOOL				m_bStartupRemote;
	BOOL				m_bStartupRemoteServer;	

	IVacuumPump			*m_pVacuumPump;
	BOOL				m_bVacuumPump;	

	IElectromagnet		*m_pElectromagnet;
	BOOL				m_bElectromagnet;	

	IHeightLaser		*m_pHeightLaser;
	BOOL				m_bHeightLaser;

};
