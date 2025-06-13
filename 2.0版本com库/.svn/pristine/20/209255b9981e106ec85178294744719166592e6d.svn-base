// DetectData.h : Declaration of the CDetectData

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"

class ATL_NO_VTABLE CDetectData :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDetectData, &CLSID_DetectData>,
	public IDispatchImpl<IDetectData, &IID_IDetectData, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDetectData() {}
	
	DECLARE_REGISTRY_RESOURCEID(IDR_DETECTDATA)

	BEGIN_COM_MAP(CDetectData)
		COM_INTERFACE_ENTRY(IDetectData)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

public:
	STDMETHOD(Init)(const USHORT *pData, USHORT uDataLen);
	STDMETHOD(Count)(USHORT *pCount);
	STDMETHOD(At)(USHORT uIndex, USHORT *pData);
	
public:
	USHORT*					m_pData;
	USHORT					m_uDataLen;
};

OBJECT_ENTRY_AUTO(__uuidof(DetectData), CDetectData)