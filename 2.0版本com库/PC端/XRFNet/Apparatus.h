// Apparatus.h : Declaration of the CApparatus

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"
#include "IEndPoint.h"
#include "SkyrayLock.h"

// CApparatus
class ATL_NO_VTABLE CApparatus :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CApparatus, &CLSID_Apparatus>,
	public IDispatchImpl<IApparatus, &IID_IApparatus, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::IEndPoint
{
public:
	CApparatus();
	
	DECLARE_REGISTRY_RESOURCEID(IDR_APPARATUS)

	BEGIN_COM_MAP(CApparatus)
		COM_INTERFACE_ENTRY(IApparatus)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

public:

private:
	UINT ID() { return e_apparatus; }
	const TCHAR* Name() { return g_strApparatus.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

public:
	STDMETHOD(Config)(const UCHAR* pIP, const UCHAR* pSubnetMask, const UCHAR* pGateway, const UCHAR* pDNS);
	
private:
	void PushIP(NetLib::IPacking *pPacking, const UCHAR *pIP);

private:
	enum
	{
		e_ip_config = 0x04,	//!< 配置下位机的提供服务的地址
		e_com_ver = 0x05,	//版本号,Arm中读取2012-03-26
	};

private:
	tstring			m_strError;				//!< 最终的错误
	USHORT			m_uCount;//版本号,Arm中读取2012-03-26
	Skyray::CLock	m_lock;					//!< 服务器信息同步的引用计数的同步锁
	HANDLE			m_hNetWork;	//版本号,Arm中读取2012-03-26	
public:
	STDMETHOD(CheckVersion)(UINT* pVersion, UINT uTimeOut);
};

OBJECT_ENTRY_AUTO(__uuidof(Apparatus), CApparatus)
