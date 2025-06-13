// Apparatus.cpp : Implementation of CApparatus

#include "stdafx.h"
#include "Apparatus.h"

#include "SkyrayUtil.h"
#pragma comment(lib, "Ws2_32.lib") 

// -----------------------------------------------------------------------------------------------------

CApparatus::CApparatus()
{
	m_uCount=0;
	m_hNetWork=NULL;
	
}

// -----------------------------------------------------------------------------------------------------

HRESULT CApparatus::FinalConstruct()
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

void CApparatus::FinalRelease()
{
	if(NULL != g_pNetKernel)
	{
		NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

		pEndPointMgr->Remove(ID());
	}
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CApparatus::Config(const UCHAR* pIP, const UCHAR* pSubnetMask, const UCHAR* pGateway, const UCHAR* pDNS)
{
	if(g_uIICVersion <= g_uLocalIICVersion)
	{
		if((NULL != pIP) && (NULL != pSubnetMask) && (NULL != pGateway) && (NULL != pDNS))
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
			short						nSpace = 0;

			pPacking->Push((char)e_ip_config);
			PushIP(pPacking, pIP);
			PushIP(pPacking, pSubnetMask);
			PushIP(pPacking, pGateway);
			PushIP(pPacking, pDNS);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
			
			return S_OK;
		}
		else
		{
			return E_INVALIDARG;
		}
	}

	return E_ABORT;
}


// -----------------------------------------------------------------------------------------------------

void CApparatus::PushIP(NetLib::IPacking *pPacking, const UCHAR *pIP)
{
	in_addr			addr;

	addr.s_addr = ::inet_addr((const char*)pIP);
	pPacking->Push((char)addr.S_un.S_un_b.s_b1);
	pPacking->Push((char)addr.S_un.S_un_b.s_b2);
	pPacking->Push((char)addr.S_un.S_un_b.s_b3);
	pPacking->Push((char)addr.S_un.S_un_b.s_b4);
}


// -----------------------------------------------------------------------------------------------------

void CApparatus::OnReceive(NetLib::TransportID eID, NetLib::IUnpacking* pUnpacking)
{
	if(NetLib::e_apparatus_transport == eID)
	{
		char				cOperator;

		pUnpacking->Pop(cOperator);
		if (e_com_ver==(unsigned char)cOperator)
		{
			char	uVersion;

			pUnpacking->Pop(uVersion);
			g_uIICVersion = uVersion;

			::SetEvent(m_hNetWork);
		}
	}

}
STDMETHODIMP CApparatus::CheckVersion(UINT* pVersion, UINT uTimeOut)
{

    // TODO: 在此添加实现代码
	if(NULL == pVersion)
		return E_INVALIDARG;

	*pVersion = 0;
    g_uIICVersion = 0;
	if(0 == g_uIICVersion)		//未取到IIC的版本号
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

			pPacking->Push((char)e_com_ver);
			pPacking->Push((char)0x01);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else
		{
			m_uCount++;
			m_lock.Unlock();
		}

		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			if(0 != g_uIICVersion)
			{
				/*if(g_uIICVersion <= g_uLocalIICVersion)
					*pCanUse = TRUE;*/
				*pVersion=g_uIICVersion;
			}

			hReturn = S_OK;
		}
		else
		{	
			g_uIICVersion = 0;
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if(0 == m_uCount)			//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if(S_OK == m_uCount)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				::SetEvent(m_hNetWork);
		}
		m_lock.Unlock();

		return hReturn;
	}
	else
	{
		/*if(g_uIICVersion <= g_uLocalIICVersion)
			*pCanUse = TRUE;*/
		*pVersion=g_uIICVersion;
	}
	return S_OK;
}
