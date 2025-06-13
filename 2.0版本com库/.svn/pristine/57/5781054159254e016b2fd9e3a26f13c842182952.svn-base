#include "StdAfx.h"
#include "NetworkCallBack.h"

// -----------------------------------------------------------------------------------------------------

CNetworkCallBack::CNetworkCallBack(void)
{
}

// -----------------------------------------------------------------------------------------------------

CNetworkCallBack::~CNetworkCallBack(void)
{
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CNetworkCallBack::QueryInterface(const struct _GUID& iid,void** ppv)
{
	if(iid == IID_INetworkCallBack)
	{
		*ppv=this;
		return S_OK;
	}

	return S_FALSE;
}

// -----------------------------------------------------------------------------------------------------

ULONG __stdcall CNetworkCallBack::AddRef(void)
{	
	//仅仅为了测试，此处为权宜之策，因为反正这个对象在程序结束前是不会退出的
	return 1;	
}

// -----------------------------------------------------------------------------------------------------

ULONG __stdcall CNetworkCallBack::Release(void)
{	
	//仅仅为了测试，此处为权宜之策，因为反正这个对象在程序结束前是不会退出的
	return 0;	
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CNetworkCallBack::OnDisconnect()
{
	::MessageBox(NULL, _T("与服务器的链接断开"), _T(""), MB_OK);
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CNetworkCallBack::OnRemoteDisconnected()
{
	::MessageBox(NULL, _T("与远程协助服务器的链接断开"), _T(""), MB_OK);
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CNetworkCallBack::OnRemoteServerDisconnected()
{
	::MessageBox(NULL, _T("与中转PC的连接断开"), _T(""), MB_OK);
	return S_OK;
}