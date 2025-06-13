// VacuumPump.cpp : Implementation of CVacuumPump
#include "stdafx.h"
#include "VacuumPump.h"

// -----------------------------------------------------------------------------------------------------

CVacuumPump::CVacuumPump()
{ 
	m_uCount = 0;
	m_vacuum = 0;
	m_vacuumDown=0;
	m_vacuumUp=0;
	m_hNetWork = NULL; 
}

// -----------------------------------------------------------------------------------------------------

HRESULT CVacuumPump::FinalConstruct()
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

void CVacuumPump::FinalRelease()
{
	if(NULL != g_pNetKernel)
	{
		NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

		pEndPointMgr->Remove(ID());
	}
}

//// -----------------------------------------------------------------------------------------------------
//
//STDMETHODIMP CVacuumPump::Open(void)
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
//STDMETHODIMP CVacuumPump::Close(void)
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

void CVacuumPump::OnReceive(NetLib::TransportID eID, NetLib::IUnpacking* pUnpacking)
{
	//if(NetLib::e_apparatus_transport == eID)
	//{
	//	char				cOperator;

	//	pUnpacking->Pop(cOperator);
	//	if(e_get_vacuum == (unsigned char)cOperator)
	//	{
	//		int			uValue;
	//		
	//		pUnpacking->Pop(uValue);
	//		m_vacuum = uValue;

	//		::SetEvent(m_hNetWork);
	//	}
	//	/*if (e_get_doublevacuum==(unsigned char)cOperator)
	//	{
	//		int uValue;
	//		pUnpacking->Pop(uValue);
	//		m_vacuumUp=uValue;
	//		pUnpacking->Pop(uValue);
	//		m_vacuumDown=uValue;
	//		::SetEvent(m_hNetWork);
	//	}*/
	//}
}

// -----------------------------------------------------------------------------------------------------

//STDMETHODIMP CVacuumPump::GetVacuum(UINT uType, UINT* pVacuum,  UINT uTimeOut)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		HRESULT			hReturn;
//
//		m_lock.Lock();
//		if(NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
//		{
//			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
//			ATLASSERT(m_hNetWork);
//			m_lock.Unlock();
//
//			pPacking->Push((char)e_get_vacuum);
//			pPacking->Push((int)uType);
//			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);	
//		}
//		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
//		{
//			m_uCount++;
//			m_lock.Unlock();
//		}
//
//		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
//		{
//			hReturn = S_OK;
//			if(pVacuum)
//				*pVacuum = m_vacuum;
//		}
//		else
//		{			
//			hReturn = E_FAIL;
//		}
//
//		m_lock.Lock();
//		if(0 == m_uCount)		//没有其他的同步请求需要通知
//		{
//			::CloseHandle(m_hNetWork);
//			m_hNetWork = NULL;
//		}
//		else
//		{
//			m_uCount--;
//			if(S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
//				::SetEvent(m_hNetWork);
//		}
//		m_lock.Unlock();
//
//		return hReturn;
//	}
//
//	return E_ABORT;
//}
