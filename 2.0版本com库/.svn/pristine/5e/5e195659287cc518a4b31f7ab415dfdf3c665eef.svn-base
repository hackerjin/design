// SurfaceSource.cpp : Implementation of CSurfaceSource

#include "stdafx.h"
#include "SurfaceSource.h"

// -----------------------------------------------------------------------------------------------------

HRESULT CSurfaceSource::FinalConstruct()
{
	if(NULL == g_pNetKernel)
		return E_ACCESSDENIED;

	NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

	ATLASSERT(pEndPointMgr);
	if(NULL == pEndPointMgr)
		return E_ACCESSDENIED;

	if(!pEndPointMgr->Add(static_cast<NetLib::IEndPoint *>(this)))
		return E_FAIL;

	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

void CSurfaceSource::FinalRelease()
{
	if(NULL != g_pNetKernel)
	{
		NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

		pEndPointMgr->Remove(ID());
	}
}

// -----------------------------------------------------------------------------------------------------

//STDMETHODIMP CSurfaceSource::SetLight(USHORT uFirstLight, USHORT uSecondLight, USHORT uThirdLight, USHORT uFourthLight)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_control);
//		pPacking->Push((short)uFirstLight);
//		pPacking->Push((short)uSecondLight);
//		pPacking->Push((short)uThirdLight);
//		pPacking->Push((short)uFourthLight);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}

// -----------------------------------------------------------------------------------------------------

void CSurfaceSource::OnReceive(NetLib::TransportID /*eID*/, NetLib::IUnpacking* /*pUnpacking*/)
{

}