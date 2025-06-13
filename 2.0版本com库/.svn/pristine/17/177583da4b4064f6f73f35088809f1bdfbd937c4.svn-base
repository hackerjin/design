#pragma once

#include "XRFNet_i.h"

class CNetworkCallBack : public INetworkCallBack
{
public:
	CNetworkCallBack(void);
	~CNetworkCallBack(void);

	HRESULT __stdcall QueryInterface(const struct _GUID& iid,void** ppv);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	
	HRESULT __stdcall OnDisconnect();
	HRESULT __stdcall OnRemoteDisconnected();
	HRESULT __stdcall OnRemoteServerDisconnected();
};
