// MotorControl.cpp : Implementation of CMotorControl

#include "stdafx.h"
#include "MotorControl.h"

// -----------------------------------------------------------------------------------------------------

HRESULT CMotorControl::FinalConstruct()
{
	if(NULL == g_pNetKernel)
		return E_ACCESSDENIED;

	NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

	ATLASSERT(pEndPointMgr);
	if(NULL == pEndPointMgr)
		return E_ACCESSDENIED;
	
	m_hNetWork = NULL;
	m_uCount = 0;
	if(!pEndPointMgr->Add(static_cast<NetLib::IEndPoint *>(this)))
		return E_FAIL;

	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

void CMotorControl::FinalRelease()
{
	if(NULL != m_hNetWork)
	{
		CloseHandle(m_hNetWork);
		m_hNetWork = NULL;
	}

	if(NULL != g_pNetKernel)
	{
		NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

		pEndPointMgr->Remove(ID());
	}
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CMotorControl::GetState(UCHAR *pState, UINT uTimeOut)
{
	if(g_uIICVersion <= g_uLocalIICVersion)
	{
		HRESULT			hReturn;
		
		m_lock.Lock();
		if(NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_state);

			g_pNetKernel->ConsolePrint(_T("发送获取电机信息状态的请求"));

			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uCount++;
			m_lock.Unlock();
		}
		
		g_pNetKernel->ConsolePrint(_T("等待下位机应答"));

		//等待同步信号被通知
		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			g_pNetKernel->ConsolePrint(_T("获取到电机的信息状态"));
			hReturn = S_OK;
			if(pState)
				*pState = m_cState;
		}
		else
		{	
			g_pNetKernel->ConsolePrint(_T("等待超时"));
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if(0 == m_uCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if(S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
			{
				g_pNetKernel->ConsolePrint(_T("通知其他需要获取电机状态信息的线程"));
				::SetEvent(m_hNetWork);
			}
		}
		m_lock.Unlock();

		return hReturn;
	}

	return E_ABORT;
}

// -----------------------------------------------------------------------------------------------------

//STDMETHODIMP CMotorControl::Move(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_control);
//		pPacking->Push((char)cID);
//		pPacking->Push((char)cDirection);
//		pPacking->Push((short)uStep);
//		pPacking->Push((char)cSwitch);
//		pPacking->Push((char)cRate);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}
//2012-07-24 追加z轴电机比率
STDMETHODIMP CMotorControl::Move(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate,USHORT uDutyRatio)
{
	if(g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_control);
		pPacking->Push((char)cID);
		pPacking->Push((char)cDirection);
		pPacking->Push((short)uStep);
		pPacking->Push((char)cSwitch);
		pPacking->Push((char)cRate);
		pPacking->Push((short)uDutyRatio);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

// -----------------------------------------------------------------------------------------------------

void CMotorControl::OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking)
{
	if(NetLib::e_apparatus_transport == eID)
	{
		char				cOperator;

		pUnpacking->Pop(cOperator);
		if(e_state == (unsigned char)cOperator)
		{
			char			cValue;

			pUnpacking->Pop(cValue);
			m_cState = (UCHAR)cValue;

			g_pNetKernel->ConsolePrint(_T("收到电机状态，发出收到信息的信号"));
			::SetEvent(m_hNetWork);
		}
		else if(e_chamber==(unsigned char)cOperator)
		{
			char			cValue;

			pUnpacking->Pop(cValue);
			m_cChamState[0] = (UCHAR)cValue;
			pUnpacking->Pop(cValue);
			m_cChamState[1] = (UCHAR)cValue;
			g_pNetKernel->ConsolePrint(_T("收到电机状态，发出收到信息的信号"));
			::SetEvent(m_hNetWork);
		}
	}	
}

STDMETHODIMP CMotorControl::GetChamberState(UCHAR pState[],SHORT pStateLen, UINT uTimeOut)
{
	// TODO: Add your implementation code here
	memset(m_cChamState,0,2*sizeof(UCHAR));
	if(g_uIICVersion <= g_uLocalIICVersion)
		{
			HRESULT			hReturn;
			
			m_lock.Lock();
			if(NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
			{
				NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
				NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

				m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
				ATLASSERT(m_hNetWork);
				m_lock.Unlock();

				pPacking->Push((char)e_chamber);

				g_pNetKernel->ConsolePrint(_T("发送获取电机信息状态的请求"));

				pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
			}
			else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
			{
				m_uCount++;
				m_lock.Unlock();
			}
			
			g_pNetKernel->ConsolePrint(_T("等待下位机应答"));

			//等待同步信号被通知
			if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
			{
				memcpy(pState,m_cChamState,2*sizeof(UCHAR));
				g_pNetKernel->ConsolePrint(_T("获取到电机的信息状态"));
				hReturn = S_OK;
				
			}
			else
			{	
				g_pNetKernel->ConsolePrint(_T("等待超时"));
				hReturn = E_FAIL;
			}

			m_lock.Lock();
			if(0 == m_uCount)		//没有其他的同步请求需要通知
			{
				::CloseHandle(m_hNetWork);
				m_hNetWork = NULL;
			}
			else
			{
				m_uCount--;
				if(S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				{
					g_pNetKernel->ConsolePrint(_T("通知其他需要获取电机状态信息的线程"));
					::SetEvent(m_hNetWork);
				}
			}
			m_lock.Unlock();

			return hReturn;
		}
	return S_OK;
}
