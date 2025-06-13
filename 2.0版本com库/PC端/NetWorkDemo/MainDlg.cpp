#include "StdAfx.h"
#include "MainDlg.h"
#include "AboutDlg.h"

#include "IPConfigDlg.h"
#include "RayTubeDlg.h"
#include "HighVoltageDlg.h"
#include "MotorDlg.h"
#include "SurfaceSourceDlg.h"
#include "DetectorDlg.h"

// -----------------------------------------------------------------------------------------------------

CMainDlg::CMainDlg()
{
	m_bShowConsol = FALSE;
	m_pNetWork = NULL;

	m_bStartup = FALSE;
	m_bStartupRemote = FALSE;
	m_bStartupRemoteServer = FALSE;

	m_pVacuumPump = NULL;
	m_bVacuumPump = FALSE;

	m_pElectromagnet = NULL;
	m_bElectromagnet = FALSE;

	m_pHeightLaser = NULL;
	m_bHeightLaser = FALSE;
}

// -----------------------------------------------------------------------------------------------------

CMainDlg::~CMainDlg()
{
	if(m_pHeightLaser)
	{
		m_pHeightLaser->Release();
		m_pHeightLaser = NULL;
	}

	if(m_pElectromagnet)
	{
		m_pElectromagnet->Release();
		m_pElectromagnet = NULL;
	}

	if(m_pVacuumPump)
	{
		m_pVacuumPump->Release();
		m_pVacuumPump = NULL;
	}

	if(m_pNetWork)
	{
		m_pNetWork->Release();
		m_pNetWork = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

// -----------------------------------------------------------------------------------------------------

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);
	
	::CoCreateInstance(CLSID_XRFNetwork, NULL, CLSCTX_INPROC_SERVER, IID_IXRFNetwork, (LPVOID *)&m_pNetWork);
	ATLASSERT(m_pNetWork);

	m_pNetWork->SetCallback(this);

#ifdef _DEBUG
	SetDlgItemText(IDC_SERVER_IP, _T("192.168.3.98"));
	SetDlgItemText(IDC_SERVER_PORT, _T("6000"));
	
	SetDlgItemText(IDC_REMOTE_IP, _T("192.168.3.98"));
	SetDlgItemText(IDC_REMOTE_PORT, _T("6000"));

	//SetDlgItemText(IDC_APPARATUS_IP, _T("192.168.3.7"));
	//SetDlgItemText(IDC_APPARATUS_PORT, _T("3333"));

	SetDlgItemText(IDC_APPARATUS_IP, _T("192.168.3.98"));
	SetDlgItemText(IDC_APPARATUS_PORT, _T("6000"));
#endif

	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		m_pNetWork->Release();
		m_pNetWork = NULL;
	}

	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	short		temp = 1;
	char		*pTemp = (char *)(&temp);

	CloseDialog(wID);
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

// -----------------------------------------------------------------------------------------------------

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedConsole(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		if(m_bShowConsol)
		{
			SetDlgItemText(IDC_CONSOLE, _T("显示"));
			m_pNetWork->ShowConsole(FALSE);
			m_bShowConsol = FALSE;
		}
		else
		{
			SetDlgItemText(IDC_CONSOLE, _T("关闭"));
			m_pNetWork->ShowConsole(TRUE);
			m_bShowConsol = TRUE;
		}
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedServerControl(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		if(!m_bStartupRemoteServer)
		{
			CString				strIP;
			CString				strPort;
			std::string			strOutput;

			GetDlgItemText(IDC_SERVER_IP, strIP);
			GetDlgItemText(IDC_SERVER_PORT, strPort);
			
			Unicode2Ansi(strIP, strOutput);
			if(S_OK == m_pNetWork->StartupRemoteServer((const UCHAR*)strOutput.c_str(), (UINT)_tstoi(strPort)))
			{
				m_bStartupRemoteServer = TRUE;
				SetDlgItemText(IDC_SERVER_CONTROL, _T("停止"));
			}
			else
			{
				MessageBox(_T("创建服务失败"));
			}
		}
		else
		{
			m_bStartupRemoteServer = FALSE;
			m_pNetWork->ShutdownRemoteServer();
			SetDlgItemText(IDC_SERVER_CONTROL, _T("启动"));
		}
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedRemoteControl(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		if(!m_bStartupRemote)
		{
			CString				strIP;
			CString				strPort;
			std::string			strOutput;

			GetDlgItemText(IDC_REMOTE_IP, strIP);
			GetDlgItemText(IDC_REMOTE_PORT, strPort);
			
			Unicode2Ansi(strIP, strOutput);
			if(S_OK != m_pNetWork->ConnectRemoteServer((const UCHAR*)strOutput.c_str(), (UINT)_tstoi(strPort)))
			{
				MessageBox(_T("创建远程协助失败"));
			}
		}
		else
		{
			m_bStartupRemote = FALSE;
			m_pNetWork->DisconnectRemoteServer();
			SetDlgItemText(IDC_REMOTE_CONTROL, _T("请求协助"));
		}
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedApparatusControl(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		if(!m_bStartup)
		{
			CString				strIP;
			CString				strPort;
			std::string			strOutput;

			GetDlgItemText(IDC_APPARATUS_IP, strIP);
			GetDlgItemText(IDC_APPARATUS_PORT, strPort);
			
			Unicode2Ansi(strIP, strOutput);
			if(S_OK != m_pNetWork->Connect((const UCHAR*)strOutput.c_str(), (UINT)_tstoi(strPort)))
			{
				MessageBox(_T("连接仪器失败"));
			}
		}
		else
		{
			m_bStartup = FALSE;
			m_pNetWork->Disconnect();
			SetDlgItemText(IDC_APPARATUS_CONTROL, _T("连接到仪器"));
		}
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedIpConfig(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CIPConfigDlg		ipConfigDlg;

	ipConfigDlg.DoModal();
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedRaytube(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		IXRFRayTube			*pRayTube = NULL;

		m_pNetWork->GetRayTube(&pRayTube);
		if(pRayTube)
		{
			CRayTubeDlg			rayTubeDlg(pRayTube);

			rayTubeDlg.DoModal();
		}
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedHighvoltage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		IHighVoltage		*pHighVoltage = NULL;

		m_pNetWork->GetHighVotage(&pHighVoltage);
		if(pHighVoltage)
		{
			CHighVoltageDlg		highVoltageDlg(pHighVoltage);

			highVoltageDlg.DoModal();
		}
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedVacuumPump(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		if(NULL == m_pVacuumPump)
			m_pNetWork->GetVacuumPump(&m_pVacuumPump);

		if(m_pVacuumPump)
		{
			if(m_bVacuumPump)
			{
				m_bVacuumPump = FALSE;
				m_pVacuumPump->Close();
				SetDlgItemText(IDC_VACUUM_PUMP, _T("开启真空泵"));
			}
			else
			{
				m_bVacuumPump = TRUE;
				m_pVacuumPump->Open();
				SetDlgItemText(IDC_VACUUM_PUMP, _T("关闭真空泵"));
			}
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedMotor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		IMotorControl			*pMotorControl = NULL;

		m_pNetWork->GetMotor(&pMotorControl);
		if(pMotorControl)
		{
			CMotorDlg			motorDlg(pMotorControl);

			motorDlg.DoModal();
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedElectromagnet(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		if(NULL == m_pElectromagnet)
			m_pNetWork->GetElectromagnet(&m_pElectromagnet);

		if(m_pElectromagnet)
		{
			if(m_bElectromagnet)
			{
				m_bElectromagnet = FALSE;
				m_pElectromagnet->Close();
				SetDlgItemText(IDC_ELECTROMAGNET, _T("开启电磁铁"));
			}
			else
			{
				m_bElectromagnet = TRUE;
				m_pElectromagnet->Open();
				SetDlgItemText(IDC_ELECTROMAGNET, _T("关闭电磁铁"));
			}
		}
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedHeightLaser(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		if(NULL == m_pHeightLaser)
			m_pNetWork->GetHeightLaser(&m_pHeightLaser);

		if(m_pHeightLaser)
		{
			if(m_bHeightLaser)
			{
				m_bHeightLaser = FALSE;
				m_pHeightLaser->Close();
				SetDlgItemText(IDC_HEIGHT_LASER, _T("打开高度激光"));
			}
			else
			{
				m_bHeightLaser = TRUE;
				m_pHeightLaser->Open();
				SetDlgItemText(IDC_HEIGHT_LASER, _T("关闭高度激光"));
			}
		}
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedSurfaceSource(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		ISurfaceSource			*pSurfaceSource = NULL;

		m_pNetWork->GetSurfaceSource(&pSurfaceSource);
		if(pSurfaceSource)
		{
			CSurfaceSourceDlg		surfaceSourceDlg(pSurfaceSource);

			surfaceSourceDlg.DoModal();
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMainDlg::OnBnClickedDetector(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pNetWork)
	{
		IDetector			*pDetector = NULL;

		m_pNetWork->GetDetector(&pDetector);
		if(pDetector)
		{
			CDetectorDlg			detectorDlg(pDetector);

			detectorDlg.DoModal();
		}
	}
				
	return 0;
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CMainDlg::QueryInterface(const struct _GUID& iid,void** ppv)
{
	if(iid == IID_INetworkCallBack)
	{
		*ppv=this;
		return S_OK;
	}

	return S_FALSE;
}

// -----------------------------------------------------------------------------------------------------

ULONG __stdcall CMainDlg::AddRef(void)
{	
	//仅仅为了测试，此处为权宜之策，因为反正这个对象在程序结束前是不会退出的
	return 1;	
}

// -----------------------------------------------------------------------------------------------------

ULONG __stdcall CMainDlg::Release(void)
{	
	//仅仅为了测试，此处为权宜之策，因为反正这个对象在程序结束前是不会退出的
	return 0;	
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CMainDlg::OnConnected()
{
	m_bStartup = TRUE;
	SetDlgItemText(IDC_APPARATUS_CONTROL, _T("断开连接"));
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CMainDlg::OnDisconnect()
{
	m_bStartup = FALSE;
	m_pNetWork->Disconnect();
	SetDlgItemText(IDC_APPARATUS_CONTROL, _T("连接到仪器"));

	::MessageBox(NULL, _T("与服务器的链接断开"), _T(""), MB_OK);
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CMainDlg::OnRemoteConnected()
{
	m_bStartupRemote = TRUE;
	SetDlgItemText(IDC_REMOTE_CONTROL, _T("结束协助"));
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CMainDlg::OnRemoteDisconnected()
{
	m_bStartupRemote = FALSE;
	m_pNetWork->DisconnectRemoteServer();
	SetDlgItemText(IDC_REMOTE_CONTROL, _T("请求协助"));

	::MessageBox(NULL, _T("与远程协助服务器的链接断开"), _T(""), MB_OK);
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CMainDlg::OnRemoteServerDisconnected()
{
	::MessageBox(NULL, _T("与中转PC的连接断开"), _T(""), MB_OK);
	return S_OK;
}