#include "stdafx.h"
#include "RecvThread.h"

#include "Unpacking.h"
#include "Transport.h"
#include "SkyrayUtil.h"

#include "ConsoleThread.h"

// -----------------------------------------------------------------------------------------------------

CRecvThread::CRecvThread(Skyray::CSocket *pSocket, CTransport *pTransport, CConsoleThread *pConsoleThread)
{
	assert(pSocket);

	m_pSocket = pSocket;
	m_pTransport = pTransport;
	m_pConsoleThread = pConsoleThread;

	m_pBuffer = m_acDefaultBuffer;
	m_nBufferIndex = 0;
	m_nBufferSize = m_uDefaultBufferSize;
}

// -----------------------------------------------------------------------------------------------------

CRecvThread::~CRecvThread()
{
	if(m_pBuffer != m_acDefaultBuffer)
	{
		delete []m_pBuffer;
		m_pBuffer = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

DWORD CRecvThread::Run()
{
	int				nRecvLen;
	char			acBuffer[1024];

	while(m_pSocket->IsValid())
	{
		if(m_pSocket->CanRead(10))
		{
			nRecvLen = (UINT)m_pSocket->Receive(acBuffer, 1024, 0);
			if(nRecvLen <= 0)
			{
				OnDisconnect();
			}
			else
			{
				AddData(acBuffer, (UINT)nRecvLen);
				Parse();
			}
		}
		else
		{
			Sleep(100);
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

void CRecvThread::AddData(char *pData, UINT uDataLen)
{
	UINT				nBufferSize;		

	nBufferSize = m_nBufferIndex+uDataLen;
	if(nBufferSize > m_nBufferSize)
	{
		UINT			nNewBufferLen = 2*nBufferSize;
		char			*pNewBuffer = new char[nNewBufferLen];

		memcpy_s(pNewBuffer, nNewBufferLen, m_pBuffer, m_nBufferIndex);
		if(m_pBuffer != m_acDefaultBuffer)
			delete []m_pBuffer;
		
		m_pBuffer = pNewBuffer;
		m_nBufferSize = nNewBufferLen;
	}

	memcpy_s(&m_pBuffer[m_nBufferIndex], (m_nBufferSize - m_nBufferIndex), pData, uDataLen);
	m_nBufferIndex += uDataLen;
}

// -----------------------------------------------------------------------------------------------------

void CRecvThread::RemoveData(UINT uDataLen)
{
	if(uDataLen > m_nBufferIndex)
		uDataLen = m_nBufferIndex;

	for(UINT i=uDataLen; i<m_nBufferIndex; i++)
		m_pBuffer[i-uDataLen] = m_pBuffer[i];

	m_nBufferIndex -= uDataLen;

	if((m_pBuffer != m_acDefaultBuffer) && (m_nBufferIndex < m_uDefaultBufferSize/2))
	{
		memcpy_s(m_acDefaultBuffer, m_uDefaultBufferSize, m_pBuffer, m_nBufferIndex);
		delete []m_pBuffer;

		m_pBuffer = m_acDefaultBuffer;
		m_nBufferSize = m_uDefaultBufferSize;
	}
}

// -----------------------------------------------------------------------------------------------------

void CRecvThread::Parse()
{
	BOOL			bExit = FALSE;

	do
	{
		if(m_nBufferIndex <= 0)
		{
			bExit = TRUE;
		}
		else
		{
			switch(m_pBuffer[0])
			{
				case 'A':
					if(m_nBufferIndex > m_nPacketHeadLen)
					{
						UINT			nPacketLen;

						memcpy_s((char *)&nPacketLen, sizeof(UINT), &m_pBuffer[5], sizeof(UINT));
						nPacketLen = ::ntohl(nPacketLen);
						if(m_nBufferIndex >= (m_nPacketHeadLen+nPacketLen))
						{
							if(m_pTransport)
							{
								NetLib::IUnpacking *pUnpacking= new CUnpacking(&m_pBuffer[m_nPacketHeadLen], nPacketLen);
								UINT				uTo;
								
								memcpy_s((char *)&uTo, sizeof(UINT), &m_pBuffer[1], sizeof(UINT));
								uTo = ::ntohl(uTo);

								if(m_pConsoleThread && m_pConsoleThread->IsOPenConsole())
									m_pConsoleThread->AddData(m_pTransport->Name(), uTo, &m_pBuffer[m_nPacketHeadLen], nPacketLen, FALSE);
								m_pTransport->OnReceive(uTo, pUnpacking);
								pUnpacking->Destroy();
							}

							RemoveData(m_nPacketHeadLen+nPacketLen);
						}
						else
						{
							bExit = TRUE;
						}
					}
					else
					{
						bExit = TRUE;
					}
					break;
				case 'H':	//!< ÐÄÌø°ü
					if(m_nBufferIndex >= m_nPacketHeadLen)
						RemoveData(m_nPacketHeadLen);
					break;
				default:
					assert(false);
					break;
			}
		}
	}while(!bExit);
}

// -----------------------------------------------------------------------------------------------------

void CRecvThread::OnDisconnect()
{
	if(m_pTransport)
		m_pTransport->OnDisconnect();
	
	if(m_pBuffer != m_acDefaultBuffer)
	{
		delete []m_pBuffer;
		m_pBuffer = NULL;
	}

	m_pBuffer = m_acDefaultBuffer;
	m_nBufferIndex = 0;
	m_nBufferSize = m_uDefaultBufferSize;
}