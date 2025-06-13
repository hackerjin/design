// HighVoltage.cpp : Implementation of CHighVoltage

#include "stdafx.h"
#include "HighVoltage.h"

// -----------------------------------------------------------------------------------------------------

HRESULT CHighVoltage::FinalConstruct()
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

void CHighVoltage::FinalRelease()
{
	if(NULL != g_pNetKernel)
	{
		NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

		pEndPointMgr->Remove(ID());
	}
}

//// -----------------------------------------------------------------------------------------------------
//
//STDMETHODIMP CHighVoltage::Open(void)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_control);
//		pPacking->Push((char)0x01);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}
//
//// -----------------------------------------------------------------------------------------------------
//
//STDMETHODIMP CHighVoltage::Close(void)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_control);
//		pPacking->Push((char)0x00);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}
//
//// -----------------------------------------------------------------------------------------------------
//
//STDMETHODIMP CHighVoltage::AllowUncover(void)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_cover);
//		pPacking->Push((char)0x01);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}
//
//// -----------------------------------------------------------------------------------------------------
//
//STDMETHODIMP CHighVoltage::ForbidUncover(void)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_cover);
//		pPacking->Push((char)0x00);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}
//
//// -----------------------------------------------------------------------------------------------------
//
//STDMETHODIMP CHighVoltage::OpenPilotLamp(void)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_pilot_lamp);
//		pPacking->Push((char)0x01);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}
//
//// -----------------------------------------------------------------------------------------------------
//
//STDMETHODIMP CHighVoltage::ClosePilotLamp(void)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_pilot_lamp);
//		pPacking->Push((char)0x00);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}

// -----------------------------------------------------------------------------------------------------

void CHighVoltage::OnReceive(NetLib::TransportID /*eID*/, NetLib::IUnpacking* /*pUnpacking*/)
{

}
