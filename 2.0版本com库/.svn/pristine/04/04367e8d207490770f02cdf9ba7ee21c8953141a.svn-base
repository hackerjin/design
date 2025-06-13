#include "stdafx.h"
#include "RemoteServer.h"

#include "Transponder.h"
#include "Transport.h"

// -----------------------------------------------------------------------------------------------------

CRemoteServer::CRemoteServer(CTransponder *pTransponder)
{
	assert(pTransponder);
	m_pTransponder = pTransponder;
}

// -----------------------------------------------------------------------------------------------------

CRemoteServer::~CRemoteServer()
{

}

// -----------------------------------------------------------------------------------------------------

BOOL CRemoteServer::Startup(const TCHAR *pIP, UINT uPort)
{
	if(m_socket.IsValid())
		return FALSE;

	m_socket.Create(SOCK_STREAM, pIP, uPort);
	m_socket.Listen(5);
	
	Start();
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

void CRemoteServer::Shutdown()
{
	if(m_socket.IsValid())
		m_socket.Close();
}

// -----------------------------------------------------------------------------------------------------

DWORD CRemoteServer::Run()
{
	Skyray::CSocket		acceptSocket;

	while(m_socket.IsValid())
	{
		if(m_socket.CanRead(10))
		{
			NetLib::ITransport	*pTransport;
			CTransport			*pAssistance;

			m_socket.Accept(acceptSocket);
			
			pTransport = m_pTransponder->FindTransport(NetLib::e_assistance_transport);
			if(NULL == pTransport)
			{
				pTransport = new CTransport(acceptSocket, NetLib::e_assistance_transport, _T("中转PC通道"), m_pTransponder);
				m_pTransponder->Add(pTransport);

				acceptSocket.Detach();
			}
			else
			{
				pAssistance = static_cast<CTransport *>(pTransport);
				
				if(pAssistance->IsConnected())
				{
					acceptSocket.Close();
				}
				else
				{
					m_pTransponder->Remove(NetLib::e_assistance_transport);

					pTransport = new CTransport(acceptSocket, NetLib::e_assistance_transport, _T("中转PC通道"), m_pTransponder);
					m_pTransponder->Add(pTransport);
					acceptSocket.Detach();
				}
			}
		}
		else
		{
			Sleep(100);
		}
	}

	m_pTransponder->Remove(NetLib::e_assistance_transport);
	return 0;
}