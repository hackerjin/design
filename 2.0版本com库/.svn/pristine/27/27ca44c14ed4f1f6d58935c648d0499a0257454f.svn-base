// LaserAltimeter.h : Declaration of the CLaserAltimeter

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"
#include "IEndPoint.h"

// CLaserAltimeter
class ATL_NO_VTABLE CHeightLaser :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CHeightLaser, &CLSID_HeightLaser>,
	public IDispatchImpl<IHeightLaser, &IID_IHeightLaser, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::IEndPoint
{
public:
	CHeightLaser(){}

	DECLARE_REGISTRY_RESOURCEID(IDR_LASERALTIMETER)

	BEGIN_COM_MAP(CHeightLaser)
		COM_INTERFACE_ENTRY(IHeightLaser)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

private:
	UINT ID() { return e_height_laser; }
	const TCHAR* Name() { return g_strHeightLaser.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

public:
	//STDMETHOD(Open)(void);//!控制电磁铁的功能(固件实际用在电磁铁)
	//STDMETHOD(Close)(void);//!控制电磁铁的功能(固件实际用在电磁铁)
	//STDMETHOD(LaserControl)(BYTE byteOpen);//!< 控制高度激光是否开启
 //   STDMETHOD(SetLaserMode)(BYTE bManual);

private:
	//enum
	//{
	//	e_control	= 0x15,					//!< 控制高度激光是否开启--->控制电磁铁的功能(固件实际用在电磁铁)
	//	e_controlLaser=0x32,				//!< 控制高度激光是否开启
	//    e_LaserMode=0x34,				    //!< 控制高度激光的模式
	//};

private:
	tstring			m_strError;				//<! 最终的错误
};

OBJECT_ENTRY_AUTO(__uuidof(HeightLaser), CHeightLaser)
