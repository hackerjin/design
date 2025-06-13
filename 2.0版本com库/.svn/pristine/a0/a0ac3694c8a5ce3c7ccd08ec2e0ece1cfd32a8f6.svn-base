#include "stdafx.h"
#include "Transponder.h"
#include "ConsoleThread.h"

#include "Packing.h"

// -----------------------------------------------------------------------------------------------------

CTransponder::CTransponder(NetLib::IEndPointMgr *pEndPointMgr, CConsoleThread *pConsoleThread)
{
	m_cb = NULL;
	m_pEndPointMgr	= pEndPointMgr;
	m_pConsoleThread = pConsoleThread;
}

// -----------------------------------------------------------------------------------------------------

CTransponder::~CTransponder()
{

}

// -----------------------------------------------------------------------------------------------------

void CTransponder::Add(NetLib::ITransport *pTransport)
{
	if(pTransport)
		m_transports.push_back(pTransport);

	if(m_pConsoleThread)
		m_pConsoleThread->AddType(pTransport->ID(), pTransport->Name());
}

// -----------------------------------------------------------------------------------------------------

void CTransponder::Remove(NetLib::TransportID id)
{
	NetLib::ITransport *pTransport = NULL;

	for(TransportIt it=m_transports.begin(); it != m_transports.end(); )
	{
		if((*it)->ID() == id)
		{
			pTransport = *it;
			pTransport->Destroy();
			it = m_transports.erase(it);

			if(m_pConsoleThread)
				m_pConsoleThread->RemoveType(id);
		}
		else
		{
			it++;
		}
	}
}

// -----------------------------------------------------------------------------------------------------

void CTransponder::RemoveAll()
{
	NetLib::ITransport *pTransport = NULL;

	for(TransportIt it=m_transports.begin(); it != m_transports.end(); it++)
	{
		pTransport = *it;
		
		if(m_pConsoleThread)
			m_pConsoleThread->RemoveType(pTransport->ID());

		pTransport->Destroy();
	}

	m_transports.clear();
}

// -----------------------------------------------------------------------------------------------------

BOOL CTransponder::Send(NetLib::TransportID id, UINT uTo, NetLib::IPacking *pPacking)
{
	assert(pPacking);
	
	NetLib::ITransport *pTransport = FindTransport(id);

	if(pTransport)
	{
		return pTransport->Send('A', uTo, pPacking);	
	}
	else
	{	
		if(NetLib::e_apparatus_transport == id)
			pTransport = FindTransport(NetLib::e_assistance_transport);

		if(pTransport)
			return pTransport->Send('A', uTo, pPacking);
		else
			return FALSE;
	}
}

// -----------------------------------------------------------------------------------------------------

void CTransponder::OnReceive(NetLib::TransportID id, UINT uTo, NetLib::IUnpacking *pUnpacking)
{
	NetLib::IEndPoint		*pEndPoint = m_pEndPointMgr->Find(uTo);	

	if(NULL == pEndPoint)
		return;

	do
	{
		if(id == NetLib::e_remote_transport)
		{
			if(pEndPoint->IsRelay())
				Send(NetLib::e_apparatus_transport, uTo, pUnpacking->CreatePacking());
			else
				pEndPoint->OnReceive(id, pUnpacking);
			break;
		}

		if(id == NetLib::e_apparatus_transport)
		{
			if(FindTransport(NetLib::e_remote_transport))
				Send(NetLib::e_remote_transport, uTo, pUnpacking->CreatePacking());
			
			pEndPoint->OnReceive(id, pUnpacking);
			break;
		}

		pEndPoint->OnReceive(id, pUnpacking);
	}while(false);
}

// -----------------------------------------------------------------------------------------------------

void CTransponder::OnConnected(NetLib::TransportID id)
{
	if(m_cb)
	{
		switch(id)
		{
			case NetLib::e_remote_transport:			//Ô¶¶ËPC
				m_cb->OnRemoteConnected();
				break;
			case NetLib::e_apparatus_transport:			//ÒÇÆ÷
				m_cb->OnConnected();
				break;
		}
	}
}

// -----------------------------------------------------------------------------------------------------

void CTransponder::OnDisconnect(NetLib::TransportID id)
{
	if(m_cb)
	{
		if(m_pConsoleThread)
			m_pConsoleThread->RemoveType(id);

		switch(id)
		{
			case NetLib::e_remote_transport:			//Ô¶¶ËPC
				m_cb->OnRemoteShutdown();
				break;
			case NetLib::e_apparatus_transport:			//ÒÇÆ÷
				m_cb->OnShutdown();
				break;
			case NetLib::e_assistance_transport:		//Ô¶³Ì·þÎñ
				m_cb->OnRemoteServerShutdown();
				break;
		}
	}
}

// -----------------------------------------------------------------------------------------------------

NetLib::ITransport* CTransponder::FindTransport(NetLib::TransportID id)
{
	NetLib::ITransport *pTransport = NULL;

	
	for(TransportIt it=m_transports.begin(); it != m_transports.end(); it++)
	{
		if((*it)->ID() == id)
		{
			pTransport = *it;
			break;
		}
	}

	return pTransport;
}

// -----------------------------------------------------------------------------------------------------

NetLib::ITransport* CTransponder::FindTransport(LPCTSTR lpName)
{
	NetLib::ITransport *pTransport = NULL;


	for(TransportIt it=m_transports.begin(); it != m_transports.end(); it++)
	{
		if(0 == _tcscmp((*it)->Name(), lpName))
		{
			pTransport = *it;
			break;
		}
	}

	return pTransport;
}