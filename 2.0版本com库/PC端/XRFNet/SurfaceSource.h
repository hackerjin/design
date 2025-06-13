// SurfaceSource.h : Declaration of the CSurfaceSource

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"
#include "IEndPoint.h"

// CSurfaceSource
class ATL_NO_VTABLE CSurfaceSource :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CSurfaceSource, &CLSID_SurfaceSource>,
	public IDispatchImpl<ISurfaceSource, &IID_ISurfaceSource, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::IEndPoint
{
public:
	CSurfaceSource(){ }

	DECLARE_REGISTRY_RESOURCEID(IDR_SURFACESOURCE)

	BEGIN_COM_MAP(CSurfaceSource)
		COM_INTERFACE_ENTRY(ISurfaceSource)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

private:
	UINT ID() { return e_surface_source; }
	const TCHAR* Name() { return g_strSurfaceSource.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

public:
	/*STDMETHOD(SetLight)(USHORT uFirstLight, USHORT uSecondLight, USHORT uThirdLight, USHORT uFourthLight);*/

private:
	enum
	{
		e_control	= 0x20,					//!< 设置面光源
	};

private:
	tstring			m_strError;				//<! 最终的错误
public:
	
};

OBJECT_ENTRY_AUTO(__uuidof(SurfaceSource), CSurfaceSource)
