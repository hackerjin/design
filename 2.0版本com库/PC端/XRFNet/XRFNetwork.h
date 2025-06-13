// XRFNetwork.h : Declaration of the CXRFNetwork

#pragma once
#include "resource.h"       // main symbols
#include "XRFNet_i.h"

#include "INetKernel.h"
#include "IEndPoint.h"
#include "IEventMgr.h"
#include "SkyrayLock.h"

class ATL_NO_VTABLE CXRFNetwork :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CXRFNetwork, &CLSID_XRFNetwork>,
	public IDispatchImpl<IXRFNetwork, &IID_IXRFNetwork, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::INetKernelCallback,
	public NetLib::IEndPoint,
	public IEventListener
{
public:
	CXRFNetwork();
	~CXRFNetwork();

	DECLARE_REGISTRY_RESOURCEID(IDR_XRFNETWORK)

	BEGIN_COM_MAP(CXRFNetwork)
		COM_INTERFACE_ENTRY(IXRFNetwork)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

public:
	STDMETHOD(Connect)(const UCHAR* pIP, unsigned short uPort);
	STDMETHOD(Disconnect)(void);
	STDMETHOD(StartupRemoteServer)(const UCHAR* pIP, unsigned short uPort);
	STDMETHOD(ShutdownRemoteServer)(void);
	STDMETHOD(ConnectRemoteServer)(const UCHAR* pIP, unsigned short uPort);
	STDMETHOD(DisconnectRemoteServer)(void);
	STDMETHOD(ShowConsole)(BOOL bShow);
	STDMETHOD(GetRayTube)(IXRFRayTube** ppXRFRay);
	STDMETHOD(GetHighVotage)(IHighVoltage** ppHighVoltage);
	STDMETHOD(GetVacuumPump)(IVacuumPump** ppVacuumPump);
	STDMETHOD(GetMotor)(IMotorControl** ppMotorControl);
	STDMETHOD(GetElectromagnet)(IElectromagnet** ppElectromagnet);
	STDMETHOD(GetHeightLaser)(IHeightLaser** ppHeightLaser);
	STDMETHOD(GetSurfaceSource)(ISurfaceSource** ppSurfaceSource);
	STDMETHOD(GetDetector)(IDetector** ppDetector);
	STDMETHOD(SetCallback)(INetworkCallBack* pCallback);
	STDMETHOD(CheckVersion)(BOOL *pCanUse, UINT uTimeOut);
	STDMETHOD(ConsolePrint)(const UCHAR* pText);
	STDMETHOD(GetApparatus)(IApparatus** ppApparatus);
	STDMETHOD(OpenSmallCamera)(void);
	STDMETHOD(CloseSmallCamera)(void);
	STDMETHOD(GainSmallCameraLight)(void);
	STDMETHOD(ReduceSmallCameraLight)(void);
	STDMETHOD(GainLargeCameraLight)(void);
	STDMETHOD(ReduceLargeCameraLight)(void);
private:
	typedef NetLib::INetKernel* (*CreateNetKernel)();

private:
	UINT ID() { return e_iic; }
	const TCHAR* Name() { return g_strIICControl.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

private:
	void OnConnected();
	void OnShutdown();
	void OnRemoteConnected();
	void OnRemoteShutdown();
	void OnRemoteServerShutdown();

private:
	void Procedure(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam);

private:
	enum
	{
		e_ver = 0x10,		//!< 版本控制
	};

private:
	INetworkCallBack*	m_pCallback;

	IXRFRayTube			*m_pRayTube;
	IHighVoltage		*m_pHighVoltage;
	IVacuumPump			*m_pVacuumPump;
	IMotorControl		*m_pMotorControl;
	IElectromagnet		*m_pElectromagnet;
	IHeightLaser		*m_pHeightLaser;
	ISurfaceSource		*m_pSurfaceSource;
	IDetector			*m_pDetector;
	IApparatus			*m_pApparatus;

	HANDLE				m_hNetWork;		//!< 用户获取服务器端信息的同步
	UINT				m_uSignalCount;	//<! 服务器信息同步的引用计数
	Skyray::CLock		m_lock;			//<! 服务器信息同步的引用计数的同步锁
	tstring				m_strError;
};

OBJECT_ENTRY_AUTO(__uuidof(XRFNetwork), CXRFNetwork)
