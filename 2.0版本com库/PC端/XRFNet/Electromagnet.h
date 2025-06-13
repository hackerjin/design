// Electromagnet.h : Declaration of the CElectromagnet

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"
#include "IEndPoint.h"

// CElectromagnet
class ATL_NO_VTABLE CElectromagnet :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CElectromagnet, &CLSID_Electromagnet>,
	public IDispatchImpl<IElectromagnet, &IID_IElectromagnet, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::IEndPoint
{
public:
	CElectromagnet(){ }

	DECLARE_REGISTRY_RESOURCEID(IDR_ELECTROMAGNET)

	BEGIN_COM_MAP(CElectromagnet)
		COM_INTERFACE_ENTRY(IElectromagnet)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

private:
	UINT ID() { return e_electromagnet; }
	const TCHAR* Name() { return g_strElectromagnet.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

public:
	STDMETHOD(Open)(void);
	STDMETHOD(Close)(void);

private:
	enum
	{
		e_control	= 0x14,					//!< 控制电磁铁是否开启 
	};

private:
	tstring			m_strError;				//<! 最终的错误
};

OBJECT_ENTRY_AUTO(__uuidof(Electromagnet), CElectromagnet)
