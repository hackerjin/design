#include "stdafx.h"
#include "SendThread.h"
#include "Transport.h"
#include "ConsoleThread.h"
#include "SkyrayUtil.h"

// -----------------------------------------------------------------------------------------------------

CSendThread::CSendThread(Skyray::CSocket *pSocket, CTransport *pTransport, CConsoleThread *pConsoleThread)
{
	assert(pSocket);

	m_pSocket = pSocket;
	m_pTransport = pTransport;
	m_pConsoleThread = pConsoleThread;
}

// -----------------------------------------------------------------------------------------------------

CSendThread::~CSendThread()
{

}

// -----------------------------------------------------------------------------------------------------

BOOL CSendThread::Send(char cType, UINT uTo, NetLib::IPacking *pPacking)
{
	if(m_pSocket->IsValid())
	{
		Task			info;

		info.m_cType	= cType;
		info.m_uTo		= uTo;
		info.m_pPacking	= pPacking;

		m_lock.Lock();
		m_tasks.push_back(info);
		m_lock.Unlock();

		return TRUE;
	}

	return FALSE;
}

// -----------------------------------------------------------------------------------------------------

DWORD CSendThread::Run()
{
	Task			info;
	const char		*pData;
	UINT			uTo;
	UINT			uDataLen;
	UINT			uSendLen;
	char			acHead[m_nPacketHeadLen];

	while(m_pSocket->IsValid())
	{
		if(GetTask(info))
		{
			switch(info.m_cType)
			{
				case 'A':
					acHead[0] = 'A';
					uTo = ::htonl(info.m_uTo);
					memcpy_s(&acHead[1], sizeof(UINT), (char *)&uTo, sizeof(UINT));

					uDataLen = info.m_pPacking->BufferLen();
					uDataLen = ::htonl(uDataLen);
					memcpy_s(&acHead[5], sizeof(UINT), (char *)&uDataLen, sizeof(UINT));
					
					uDataLen = m_nPacketHeadLen;
					uSendLen = (UINT)m_pSocket->Send(acHead, uDataLen, 0);
					if(uSendLen != uDataLen)
					{
						OnDisconnect();
						break;
					}
					
					pData = info.m_pPacking->Buffer();
					uDataLen = info.m_pPacking->BufferLen();
					uSendLen = (UINT)m_pSocket->Send(pData, uDataLen, 0);
					if(uSendLen != uDataLen)
					{
						OnDisconnect();
						break;
					}
					else
					{
						if(m_pConsoleThread->IsOPenConsole())
							m_pConsoleThread->AddData(m_pTransport->Name(), info.m_uTo, pData, uDataLen, TRUE);
					}
					break;
				case 'H':
					acHead[0] = 'H';
					uTo = 0;
					memcpy_s(&acHead[1], sizeof(UINT), (char *)&uTo, sizeof(UINT));

					uDataLen = 0;
					memcpy_s(&acHead[5], sizeof(UINT), (char *)&uDataLen, sizeof(UINT));

					uDataLen = m_nPacketHeadLen;
					uSendLen = (UINT)m_pSocket->Send(acHead, uDataLen, 0);
					if(uSendLen != uDataLen)
					{
						OnDisconnect();
						break;
					}

// 					uDataLen = 1;
// 					uSendLen = (UINT)m_pSocket->Send("H", uDataLen, 0);
// 					if(uSendLen != uDataLen)
// 						OnDisconnect();
					break;
			}
			
			if(info.m_pPacking)
				info.m_pPacking->Destroy();
		}
		else
		{
			Sleep(100);
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

void CSendThread::OnDisconnect()
{
	if(m_pTransport)
		m_pTransport->OnDisconnect();

	m_lock.Lock();
	for(TaskIt it=m_tasks.begin(); it != m_tasks.end(); it++)
	{
		if(it->m_pPacking)
		{
			it->m_pPacking->Destroy();
			it->m_pPacking = NULL;
		}
	}
	m_tasks.clear();
	m_lock.Unlock();
}

// -----------------------------------------------------------------------------------------------------

BOOL CSendThread::GetTask(Task &info)
{
	BOOL		bReturn = FALSE;
	TaskIt		it;

	m_lock.Lock();
	it = m_tasks.begin();
	if(it != m_tasks.end())
	{
		info.m_cType	= it->m_cType;
		info.m_uTo		= it->m_uTo;
		info.m_pPacking	= it->m_pPacking;

		m_tasks.erase(it);
		bReturn = TRUE;
	}
	m_lock.Unlock();

	return bReturn;
}