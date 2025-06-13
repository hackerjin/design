// HighVoltage.h : Declaration of the CHighVoltage

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"
#include "IEndPoint.h"

// CHighVoltage
class ATL_NO_VTABLE CHighVoltage :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CHighVoltage, &CLSID_HighVoltage>,
	public IDispatchImpl<IHighVoltage, &IID_IHighVoltage, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::IEndPoint
{
public:
	CHighVoltage(){}

	DECLARE_REGISTRY_RESOURCEID(IDR_HIGHVOLTAGE)

	BEGIN_COM_MAP(CHighVoltage)
		COM_INTERFACE_ENTRY(IHighVoltage)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();
	
private:
	UINT ID() { return e_high_voltage; }
	const TCHAR* Name() { return g_strHighVoltage.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

public:
	//STDMETHOD(Open)(void);
	//STDMETHOD(Close)(void);
	//STDMETHOD(AllowUncover)(void);
	//STDMETHOD(ForbidUncover)(void);
	//STDMETHOD(OpenPilotLamp)(void);
	//STDMETHOD(ClosePilotLamp)(void);

private:
	//enum
	//{
	//	//e_control		= 0x11,		//!< 控制高压是否开启
	//	//e_pilot_lamp	= 0x13,		//!< 控制高压指示灯是否开启
	//	//e_cover			= 0x18,		//!< 是否允许开盖的情况下开启高压
	//};

private:
	tstring			m_strError;				//<! 最终的错误	
};

OBJECT_ENTRY_AUTO(__uuidof(HighVoltage), CHighVoltage)
