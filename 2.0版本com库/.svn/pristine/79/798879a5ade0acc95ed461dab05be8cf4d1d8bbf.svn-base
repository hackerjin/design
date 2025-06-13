// DetectorDlg.cpp : Implementation of CDetectorDlg

#include "stdafx.h"
#include "Detector.h"
#include "EventDef.h"

// -----------------------------------------------------------------------------------------------------

CDetector::CDetector()
{
	m_uCount = 4096;
	m_pCallback = NULL;
	m_bGetVersion = FALSE;
	m_hNetWork = NULL;
	m_uSignalCount = 0;
}

// -----------------------------------------------------------------------------------------------------

HRESULT CDetector::FinalConstruct()
{
	if(NULL == g_pNetKernel)
		return E_ACCESSDENIED;

	NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

	ATLASSERT(pEndPointMgr);
	if(NULL == pEndPointMgr)
		return E_ACCESSDENIED;
	
	m_uCount = 4096;
	m_pCallback = NULL;
	m_bGetVersion = FALSE;
	m_uSignalCount = 0;
	if(!pEndPointMgr->Add(static_cast<NetLib::IEndPoint *>(this)))
		return E_FAIL;

	g_eventMgr.Hook(gEventReceiveDetectorData.c_str(), this);
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

void CDetector::FinalRelease()
{
	g_eventMgr.Unhook(gEventReceiveDetectorData.c_str(), this);

	if(m_pCallback)
	{
		m_pCallback->Release();
		m_pCallback = NULL;
	}

	if(NULL != g_pNetKernel)
	{
		NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

		pEndPointMgr->Remove(ID());
	}
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CDetector::BeginRead(void)
{
	if(g_uSPIVersion <= g_uLocalSPIVersion)
	{
		m_bDMCACatch=FALSE;
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_begin);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

// -----------------------------------------------------------------------------------------------------

//STDMETHODIMP CDetector::Config(UCHAR cBaseResume, UCHAR cBaseLimit, UCHAR cHeapUP, UCHAR cRate, UCHAR cCoarse, UINT uFine, UINT uTime, UCHAR cUPTime, UCHAR cWidthTime, UCHAR cSlowLimit)
//{
//	if(g_uSPIVersion <= g_uLocalSPIVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_config);
//		pPacking->Push((char)cBaseResume);
//		pPacking->Push((char)cBaseLimit);
//		pPacking->Push((char)cHeapUP);
//		pPacking->Push((char)cRate);
//		pPacking->Push((char)cCoarse);
//		pPacking->Push((int)uFine);
//		pPacking->Push((int)uTime);
//		pPacking->Push((char)cUPTime);
//		pPacking->Push((char)cWidthTime);
//		pPacking->Push((char)cSlowLimit);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}
STDMETHODIMP CDetector::Config(UCHAR cBaseResume, UCHAR cBaseLimit, UCHAR cHeapUP, UCHAR cRate, UCHAR cCoarse, UINT uFine, UINT uTime, UCHAR cUPTime, UCHAR cWidthTime, UCHAR cSlowLimit,double dEnCoef)
{
	if(g_uSPIVersion <= g_uLocalSPIVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_config);
		pPacking->Push((char)cBaseResume);
		pPacking->Push((char)cBaseLimit);
		pPacking->Push((char)cHeapUP);
		pPacking->Push((char)cRate);
		pPacking->Push((char)cCoarse);
		pPacking->Push((int)uFine);
		pPacking->Push((int)uTime);
		pPacking->Push((char)cUPTime);
		pPacking->Push((char)cWidthTime);
		pPacking->Push((char)cSlowLimit);
		BOOL ISLagerThanZero = dEnCoef > 0 ? TRUE : FALSE;
		int Coef = abs(int(dEnCoef*16384));
		char temp = ((char)(Coef/(256*256*256))&0x7F)|(!ISLagerThanZero?0x00:0x80);
		pPacking->Push(temp);
		temp = (char)(Coef/(256*256)%256) ;
		pPacking->Push(temp);
		temp = (char)(Coef/256%256) ;
		pPacking->Push(temp);
		temp = (char)(Coef%256) ;
		pPacking->Push(temp);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}
// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CDetector::SetChannelCount(USHORT uCount)
{
	m_uCount = uCount;
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CDetector::SetCallback(IDetectorCallBack* pCallback)
{
	if(m_pCallback)
	{
		m_pCallback->Release();
		m_pCallback = NULL;
	}

	if(NULL != pCallback)
	{
		m_pCallback = pCallback;
		pCallback->AddRef();
	}

	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CDetector::CheckVersion(BOOL *pCanUse, UINT uTimeOut)
{
	if(NULL == pCanUse)
		return E_INVALIDARG;
	
	*pCanUse = FALSE;

	if(0 == g_uSPIVersion)		//未取到SPI的版本号
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if(NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
			
			m_bGetVersion = TRUE;

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();
		
			pPacking->Push((char)e_ver);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else
		{
			m_uSignalCount++;
			m_lock.Unlock();
		}
		
		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			if(0 != g_uSPIVersion)
			{
				if(g_uSPIVersion <= g_uLocalSPIVersion)
					*pCanUse = TRUE;
			}
			hReturn = S_OK;
		}
		else
		{	
			g_uSPIVersion = 0;
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if(0 == m_uSignalCount)			//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uSignalCount--;
			if(S_OK == m_uSignalCount)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				::SetEvent(m_hNetWork);
		}
		m_lock.Unlock();

		return hReturn;
	}
	else
	{
		if(g_uSPIVersion <= g_uLocalSPIVersion)
			*pCanUse = TRUE;
	}

	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

void CDetector::OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking)
{
	if(NetLib::e_apparatus_transport == eID)
	{
		if(m_bGetVersion)
		{
			int				uVersion;

			pUnpacking->Pop(uVersion);
			g_uSPIVersion = (UINT)uVersion;

			::SetEvent(m_hNetWork);
		}
		else
		{
			UINT			uDataSize = pUnpacking->Size();
			if(uDataSize == (m_uCount*2+64))
			{
				if(m_bDMCACatch)
				{
					pUnpacking->PopBuffer(m_byteBuffers, uDataSize);
				    m_buferLen=uDataSize;
					::SetEvent(m_hNetWork);
				}
				else
				{
					char		acBuf[48];
					DataInfo	*pInfo = new DataInfo;
					int			nData32;
					short		nData16;
					UINT		nCount = 0;
					wchar_t		acDebug[256];

					pInfo->m_pData = new USHORT[m_uCount];
					pInfo->m_uDataLen = m_uCount;

					pUnpacking->PopBuffer(acBuf, 48);

					pUnpacking->Pop(nData32);
					pInfo->m_uQuickCount = (UINT)nData32;

					pUnpacking->Pop(nData32);
					pInfo->m_uSlowCount = (UINT)nData32;

					pUnpacking->Pop(nData32);
					pInfo->m_uSystemTime = (UINT)nData32;

					pUnpacking->Pop(nData32);
					pInfo->m_uLocalTime = (UINT)nData32;
					
					nCount = 0;
					for(USHORT i=0; i<m_uCount; i++)
					{
						pUnpacking->Pop(nData16);
						pInfo->m_pData[i] = (USHORT)nData16;
						nCount += pInfo->m_pData[i];
					}
					
					swprintf_s(acDebug, 250, L"%u %u %u", pInfo->m_uQuickCount, pInfo->m_uSlowCount, nCount);
					g_pNetKernel->ConsolePrint(acDebug);

				    g_eventMgr.Notify(gEventReceiveDetectorData.c_str(), (WPARAM)pInfo, (LPARAM)0);
				}
			}
			else
			{
				pUnpacking->PopBuffer(m_byteBuffers, uDataSize);
				m_buferLen=uDataSize;
				::SetEvent(m_hNetWork);
			}
		}
	}
}

// -----------------------------------------------------------------------------------------------------

void CDetector::Procedure(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam)
{
	if(gEventReceiveDetectorData == lpEventName)
	{
		DataInfo			*pInfo = (DataInfo *)wParam;

		if(m_pCallback)
		{
			IDetectData			*pData;

			::CoCreateInstance(CLSID_DetectData, NULL, CLSCTX_INPROC_SERVER, IID_IDetectData, (LPVOID *)&pData);
			ATLASSERT(pData);

			pData->Init(pInfo->m_pData, pInfo->m_uDataLen);
			m_pCallback->OnRead(pInfo->m_uQuickCount, pInfo->m_uSlowCount, pInfo->m_uSystemTime, pInfo->m_uLocalTime, pData);
			pData->Release();
		}

		delete []pInfo->m_pData;
		delete pInfo;
		return;
	}
}
STDMETHODIMP CDetector::SetDpp100Parameter(BYTE byteDpp100Cmd[], SHORT intCmdLen)
{
	// TODO: Add your implementation code here
   if(g_uSPIVersion <= g_uLocalSPIVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_dpp100Parameter);
		for(int i=0;i<intCmdLen;i++)
		{
			pPacking->Push((char)byteDpp100Cmd[i]);
		}
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}
	return E_ABORT;
}

STDMETHODIMP CDetector::GetDpp100Datas(BYTE byteDpp100Cmd[], SHORT intDpp100CmdLen,UINT uTimeOut, BYTE byteGetBytes[],SHORT* intGetBytesLen)
{
	// TODO: Add your implementation code here
	if(g_uSPIVersion <= g_uLocalSPIVersion)
	{
		HRESULT			hReturn;
		m_lock.Lock();
		memset(m_byteBuffers,0,16386*sizeof(BYTE));
		m_buferLen=0;
		if(NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_dpp100GetDatas);
			for(int i=0;i<intDpp100CmdLen;i++)
			{
				pPacking->Push((char)byteDpp100Cmd[i]);
			}
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);	
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uSignalCount++;
			m_lock.Unlock();
		}

		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			memcpy(byteGetBytes,m_byteBuffers,m_buferLen*sizeof(BYTE));
			*intGetBytesLen=m_buferLen;
			hReturn = S_OK;
		}
		else
		{			
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if(0 == m_uSignalCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uSignalCount--;
			if(S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				::SetEvent(m_hNetWork);
		}
		m_lock.Unlock();
		return S_OK;
	}
	return E_ABORT;
}
STDMETHODIMP CDetector::GetDMCADatas(UINT uTimeOut,BYTE byteGetBytes[],SHORT* intGetBytesLen)
{
	
	if(g_uSPIVersion <= g_uLocalSPIVersion)
	{
		HRESULT			hReturn;
		m_lock.Lock();
		m_bDMCACatch=TRUE;
		if(NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_begin);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);	
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uSignalCount++;
			m_lock.Unlock();
		}

		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			memcpy(byteGetBytes,m_byteBuffers,m_buferLen*sizeof(BYTE));
			*intGetBytesLen=m_buferLen;
			hReturn = S_OK;
		}
		else
		{			
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		//m_bDMCACatch=FALSE;
		if(0 == m_uSignalCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uSignalCount--;
			if(S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				::SetEvent(m_hNetWork);
		}
		m_lock.Unlock();
		return S_OK;
	}
	return E_ABORT;
}