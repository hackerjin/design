// FreeDemo.h : Declaration of the CFreeDemo

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"




// CFreeDemo

class ATL_NO_VTABLE CFreeDemo :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFreeDemo, &CLSID_FreeDemo>,
	public IFreeDemo
{
public:
	CFreeDemo()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_FREEDEMO)


	BEGIN_COM_MAP(CFreeDemo)
	COM_INTERFACE_ENTRY(IFreeDemo)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

};

OBJECT_ENTRY_AUTO(__uuidof(FreeDemo), CFreeDemo)
