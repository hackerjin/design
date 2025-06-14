// XRFNetwork.cpp : Implementation of CXRFNetwork

#include "stdafx.h"
#include "XRFNetwork.h"
#include "EventDef.h"
#include "EventMgr.h"
#include "SkyrayUtil.h"

extern NetLib::INetKernel	*g_pNetKernel;

// -----------------------------------------------------------------------------------------------------

CXRFNetwork::CXRFNetwork()
{
	m_pRayTube = NULL;
	m_pHighVoltage = NULL;
	m_pVacuumPump = NULL;
	m_pMotorControl = NULL;
	m_pElectromagnet = NULL;
	m_pHeightLaser = NULL;
	m_pSurfaceSource = NULL;
	m_pDetector = NULL;
	m_pApparatus = NULL;

	m_pCallback = NULL;
	m_hNetWork = NULL;

	m_uSignalCount = 0;
}

// -----------------------------------------------------------------------------------------------------

CXRFNetwork::~CXRFNetwork()
{

}

// -----------------------------------------------------------------------------------------------------

HRESULT CXRFNetwork::FinalConstruct()
{
	if (NULL == g_hNetLib)
	{
		std::wstring			strDllFileName;

		strDllFileName = g_acModulePath;
		strDllFileName += L"NetLib.dll";
		g_hNetLib = ::LoadLibrary(strDllFileName.c_str());
		ATLASSERT(g_hNetLib);
		if (NULL == g_hNetLib)
			return E_ACCESSDENIED;
	}

	if (NULL == g_pNetKernel)
	{
		CreateNetKernel		pCreateKernel;

		ATLASSERT(g_hNetLib);
		if (NULL == g_hNetLib)
			return E_ACCESSDENIED;

		pCreateKernel = (CreateNetKernel)::GetProcAddress(g_hNetLib, "CreateNetKernel");
		ATLASSERT(pCreateKernel);
		if (NULL == pCreateKernel)
			return E_NOTIMPL;

		g_pNetKernel = pCreateKernel();
		ATLASSERT(g_pNetKernel);
		if (NULL == g_pNetKernel)
			return E_FAIL;

		m_uSignalCount = 0;

		g_pNetKernel->SetCallback(this);

		g_eventMgr.SetProcedureContext();
		g_eventMgr.Register(gEventApparatusConnected.c_str());
		g_eventMgr.Register(gEventApparatusShutdown.c_str());
		g_eventMgr.Register(gEventRemoteConnected.c_str());
		g_eventMgr.Register(gEventRemoteShutdown.c_str());
		g_eventMgr.Register(gEventRemoteServerShutdown.c_str());
		g_eventMgr.Register(gEventReceiveDetectorData.c_str());

		g_eventMgr.Hook(gEventApparatusConnected.c_str(), this);
		g_eventMgr.Hook(gEventApparatusShutdown.c_str(), this);
		g_eventMgr.Hook(gEventRemoteConnected.c_str(), this);
		g_eventMgr.Hook(gEventRemoteShutdown.c_str(), this);
		g_eventMgr.Hook(gEventRemoteServerShutdown.c_str(), this);
	}

	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

void CXRFNetwork::FinalRelease()
{
	g_eventMgr.Unhook(gEventApparatusConnected.c_str(), this);
	g_eventMgr.Unhook(gEventApparatusShutdown.c_str(), this);
	g_eventMgr.Unhook(gEventRemoteConnected.c_str(), this);
	g_eventMgr.Unhook(gEventRemoteShutdown.c_str(), this);
	g_eventMgr.Unhook(gEventRemoteServerShutdown.c_str(), this);

	if (m_pCallback)
	{
		m_pCallback->Release();
		m_pCallback = NULL;
	}

	if (m_pApparatus)
	{
		m_pApparatus->Release();
		m_pApparatus = NULL;
	}

	if (m_pDetector)
	{
		m_pDetector->Release();
		m_pDetector = NULL;
	}

	if (m_pSurfaceSource)
	{
		m_pSurfaceSource->Release();
		m_pSurfaceSource = NULL;
	}

	if (m_pHeightLaser)
	{
		m_pHeightLaser->Release();
		m_pHeightLaser = NULL;
	}

	if (m_pElectromagnet)
	{
		m_pElectromagnet->Release();
		m_pElectromagnet = NULL;
	}

	if (m_pMotorControl)
	{
		m_pMotorControl->Release();
		m_pMotorControl = NULL;
	}

	if (m_pVacuumPump)
	{
		m_pVacuumPump->Release();
		m_pVacuumPump = NULL;
	}

	if (m_pHighVoltage)
	{
		m_pHighVoltage->Release();
		m_pHighVoltage = NULL;
	}

	if (m_pRayTube)
	{
		m_pRayTube->Release();
		m_pRayTube = NULL;
	}

	if (g_pNetKernel)
	{
		g_pNetKernel->Destroy();
		g_pNetKernel = NULL;
	}

	if (g_hNetLib)
	{
		::FreeLibrary(g_hNetLib);
		g_hNetLib = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::Connect(const UCHAR* pIP, unsigned short uPort)
{
	if ((NULL == pIP) || (0 == strlen((const char*)pIP)) || (0 == uPort))
		return E_INVALIDARG;

	std::wstring		strIP;

	Skyray::Ansi2Unicode((const char*)pIP, strIP);

	ATLASSERT(g_pNetKernel);
	if (g_pNetKernel->Startup(strIP.c_str(), uPort))
		return S_OK;
	else
		return E_FAIL;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::Disconnect(void)
{
	if (g_pNetKernel)
		g_pNetKernel->Shutdown();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::StartupRemoteServer(const UCHAR* pIP, unsigned short uPort)
{
	if ((NULL == pIP) || (0 == strlen((const char*)pIP)) || (0 == uPort))
		return E_INVALIDARG;

	std::wstring		strIP;

	Skyray::Ansi2Unicode((const char*)pIP, strIP);

	ATLASSERT(g_pNetKernel);
	if (g_pNetKernel->StartupRemoteServer(strIP.c_str(), uPort))
		return S_OK;
	else
		return E_FAIL;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::ShutdownRemoteServer(void)
{
	if (g_pNetKernel)
		g_pNetKernel->ShutdownRemoteServer();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::ConnectRemoteServer(const UCHAR* pIP, unsigned short uPort)
{
	if ((NULL == pIP) || (0 == strlen((const char*)pIP)) || (0 == uPort))
		return E_INVALIDARG;

	std::wstring		strIP;

	Skyray::Ansi2Unicode((const char*)pIP, strIP);

	ATLASSERT(g_pNetKernel);
	if (g_pNetKernel->StartupRemote(strIP.c_str(), uPort))
		return S_OK;
	else
		return E_FAIL;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::DisconnectRemoteServer(void)
{
	if (g_pNetKernel)
		g_pNetKernel->ShutdownRemote();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::ShowConsole(BOOL bShow)
{
	ATLASSERT(g_pNetKernel);

	if (bShow)
		g_pNetKernel->OpenConsole();
	else
		g_pNetKernel->CloseConsole();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::GetRayTube(IXRFRayTube** ppXRFRay)
{
	if (NULL == ppXRFRay)
		return E_INVALIDARG;

	m_lock.Lock();
	if (NULL == m_pRayTube)
	{
		::CoCreateInstance(CLSID_XRFRay, NULL, CLSCTX_INPROC_SERVER, IID_IXRFRayTube, (LPVOID *)&m_pRayTube);
		ATLASSERT(m_pRayTube);
		if (NULL == m_pRayTube)
		{
			m_lock.Unlock();
			return E_NOINTERFACE;
		}
	}
	m_lock.Unlock();

	*ppXRFRay = m_pRayTube;
	(*ppXRFRay)->AddRef();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::GetHighVotage(IHighVoltage** ppHighVoltage)
{
	if (NULL == ppHighVoltage)
		return E_INVALIDARG;

	m_lock.Lock();
	if (NULL == m_pHighVoltage)
	{
		::CoCreateInstance(CLSID_HighVoltage, NULL, CLSCTX_INPROC_SERVER, IID_IHighVoltage, (LPVOID *)&m_pHighVoltage);
		ATLASSERT(m_pHighVoltage);
		if (NULL == m_pHighVoltage)
		{
			m_lock.Unlock();
			return E_NOINTERFACE;
		}
	}
	m_lock.Unlock();

	*ppHighVoltage = m_pHighVoltage;
	(*ppHighVoltage)->AddRef();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::GetVacuumPump(IVacuumPump** ppVacuumPump)
{
	if (NULL == ppVacuumPump)
		return E_INVALIDARG;

	m_lock.Lock();
	if (NULL == m_pVacuumPump)
	{
		::CoCreateInstance(CLSID_VacuumPump, NULL, CLSCTX_INPROC_SERVER, IID_IVacuumPump, (LPVOID *)&m_pVacuumPump);
		ATLASSERT(m_pVacuumPump);
		if (NULL == m_pVacuumPump)
		{
			m_lock.Unlock();
			return E_NOINTERFACE;
		}
	}
	m_lock.Unlock();

	*ppVacuumPump = m_pVacuumPump;
	(*ppVacuumPump)->AddRef();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::GetMotor(IMotorControl** ppMotorControl)
{
	if (NULL == ppMotorControl)
		return E_INVALIDARG;

	m_lock.Lock();
	if (NULL == m_pMotorControl)
	{
		::CoCreateInstance(CLSID_MotorControl, NULL, CLSCTX_INPROC_SERVER, IID_IMotorControl, (LPVOID *)&m_pMotorControl);
		ATLASSERT(m_pMotorControl);
		if (NULL == m_pMotorControl)
		{
			m_lock.Unlock();
			return E_NOINTERFACE;
		}
	}
	m_lock.Unlock();

	*ppMotorControl = m_pMotorControl;
	(*ppMotorControl)->AddRef();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::GetElectromagnet(IElectromagnet** ppElectromagnet)
{
	if (NULL == ppElectromagnet)
		return E_INVALIDARG;

	m_lock.Lock();
	if (NULL == m_pElectromagnet)
	{
		::CoCreateInstance(CLSID_Electromagnet, NULL, CLSCTX_INPROC_SERVER, IID_IElectromagnet, (LPVOID *)&m_pElectromagnet);
		ATLASSERT(m_pElectromagnet);
		if (NULL == m_pElectromagnet)
		{
			m_lock.Unlock();
			return E_NOINTERFACE;
		}
	}
	m_lock.Unlock();

	*ppElectromagnet = m_pElectromagnet;
	(*ppElectromagnet)->AddRef();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::GetHeightLaser(IHeightLaser** ppHeightLaser)
{
	if (NULL == ppHeightLaser)
		return E_INVALIDARG;

	m_lock.Lock();
	if (NULL == m_pHeightLaser)
	{
		::CoCreateInstance(CLSID_HeightLaser, NULL, CLSCTX_INPROC_SERVER, IID_IHeightLaser, (LPVOID *)&m_pHeightLaser);
		ATLASSERT(m_pHeightLaser);
		if (NULL == m_pHeightLaser)
		{
			m_lock.Unlock();
			return E_NOINTERFACE;
		}
	}
	m_lock.Unlock();

	*ppHeightLaser = m_pHeightLaser;
	(*ppHeightLaser)->AddRef();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::GetSurfaceSource(ISurfaceSource** ppSurfaceSource)
{
	if (NULL == ppSurfaceSource)
		return E_INVALIDARG;

	m_lock.Lock();
	if (NULL == m_pSurfaceSource)
	{
		::CoCreateInstance(CLSID_SurfaceSource, NULL, CLSCTX_INPROC_SERVER, IID_ISurfaceSource, (LPVOID *)&m_pSurfaceSource);
		ATLASSERT(m_pSurfaceSource);
		if (NULL == m_pSurfaceSource)
		{
			m_lock.Unlock();
			return E_NOINTERFACE;
		}
	}
	m_lock.Unlock();

	*ppSurfaceSource = m_pSurfaceSource;
	(*ppSurfaceSource)->AddRef();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::GetDetector(IDetector** ppDetector)
{
	if (NULL == ppDetector)
		return E_INVALIDARG;

	m_lock.Lock();
	if (NULL == m_pDetector)
	{
		::CoCreateInstance(CLSID_Detector, NULL, CLSCTX_INPROC_SERVER, IID_IDetector, (LPVOID *)&m_pDetector);
		ATLASSERT(m_pDetector);
		if (NULL == m_pDetector)
		{
			m_lock.Unlock();
			return E_NOINTERFACE;
		}
	}
	m_lock.Unlock();

	*ppDetector = m_pDetector;
	(*ppDetector)->AddRef();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::GetApparatus(IApparatus** ppApparatus)
{
	if (NULL == ppApparatus)
		return E_INVALIDARG;

	m_lock.Lock();
	if (NULL == m_pApparatus)
	{
		::CoCreateInstance(CLSID_Apparatus, NULL, CLSCTX_INPROC_SERVER, IID_IApparatus, (LPVOID *)&m_pApparatus);
		ATLASSERT(m_pApparatus);
		if (NULL == m_pApparatus)
		{
			m_lock.Unlock();
			return E_NOINTERFACE;
		}
	}
	m_lock.Unlock();

	*ppApparatus = m_pApparatus;
	(*ppApparatus)->AddRef();
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::SetCallback(INetworkCallBack* pCallback)
{
	if (m_pCallback)
	{
		m_pCallback->Release();
		m_pCallback = NULL;
	}

	if (NULL != pCallback)
	{
		m_pCallback = pCallback;
		pCallback->AddRef();
	}

	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::CheckVersion(BOOL *pCanUse, UINT uTimeOut)
{
	if (NULL == pCanUse)
		return E_INVALIDARG;

	*pCanUse = FALSE;

	if (0 == g_uIICVersion)		//未取到IIC的版本号
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if (NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_ver);
			pPacking->Push((char)0x01);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else
		{
			m_uSignalCount++;
			m_lock.Unlock();
		}

		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			if (0 != g_uIICVersion)
			{
				if (g_uIICVersion <= g_uLocalIICVersion)
					*pCanUse = TRUE;
			}

			hReturn = S_OK;
		}
		else
		{
			g_uIICVersion = 0;
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if (0 == m_uSignalCount)			//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uSignalCount--;
			if (S_OK == m_uSignalCount)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				::SetEvent(m_hNetWork);
		}
		m_lock.Unlock();

		return hReturn;
	}
	else
	{
		if (g_uIICVersion <= g_uLocalIICVersion)
			*pCanUse = TRUE;
	}

	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFNetwork::ConsolePrint(const UCHAR* pText)
{
	std::wstring		strText;

	Skyray::Ansi2Unicode((const char*)pText, strText);

	ATLASSERT(g_pNetKernel);
	g_pNetKernel->ConsolePrint(strText.c_str());
	return S_OK;
}

//近景摄像头打开及关闭
STDMETHODIMP CXRFNetwork::OpenSmallCamera(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)0x1E);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}


STDMETHODIMP CXRFNetwork::CloseSmallCamera(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)0x1E);
		pPacking->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}


//近景摄像头补光灯增强或减弱


STDMETHODIMP CXRFNetwork::GainSmallCameraLight(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)0x1D);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFNetwork::ReduceSmallCameraLight(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)0x1C);
		pPacking->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}


//远景摄像头补光灯增强或减弱
STDMETHODIMP CXRFNetwork::GainLargeCameraLight(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)0x1B);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFNetwork::ReduceLargeCameraLight(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)0x1B);
		pPacking->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}



void CXRFNetwork::Procedure(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam)
{
	if (gEventApparatusConnected == lpEventName)
	{
		if (m_pCallback)
			m_pCallback->OnConnected();

		return;
	}

	if (gEventApparatusShutdown == lpEventName)
	{
		if (m_pCallback)
			m_pCallback->OnDisconnect();
		return;
	}

	if (gEventRemoteConnected == lpEventName)
	{
		if (m_pCallback)
			m_pCallback->OnRemoteConnected();
	}

	if (gEventRemoteShutdown == lpEventName)
	{
		if (m_pCallback)
			m_pCallback->OnRemoteDisconnected();
		return;
	}

	if (gEventRemoteServerShutdown == lpEventName)
	{
		if (m_pCallback)
			m_pCallback->OnRemoteServerDisconnected();
		return;
	}
}

void CXRFNetwork::OnConnected()
{
	g_eventMgr.Notify(gEventApparatusConnected.c_str(), 0, 0);
}


void CXRFNetwork::OnShutdown()
{
	g_eventMgr.Notify(gEventApparatusShutdown.c_str(), 0, 0);
}


void CXRFNetwork::OnRemoteConnected()
{
	g_eventMgr.Notify(gEventRemoteConnected.c_str(), 0, 0);
}

// -----------------------------------------------------------------------------------------------------

void CXRFNetwork::OnRemoteShutdown()
{
	g_eventMgr.Notify(gEventRemoteShutdown.c_str(), 0, 0);
}

// -----------------------------------------------------------------------------------------------------

void CXRFNetwork::OnRemoteServerShutdown()
{
	g_eventMgr.Notify(gEventRemoteServerShutdown.c_str(), 0, 0);
}

// -----------------------------------------------------------------------------------------------------

void CXRFNetwork::OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking)
{
	if (NetLib::e_apparatus_transport == eID)
	{
		char				cOperator;

		pUnpacking->Pop(cOperator);
		if (e_ver == (unsigned char)cOperator)
		{
			int			uVersion;

			pUnpacking->Pop(uVersion);
			g_uIICVersion = uVersion;

			::SetEvent(m_hNetWork);
		}
	}
}


