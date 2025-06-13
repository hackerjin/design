#include "stdafx.h"
#include "Transport.h"

#include "Transponder.h"

// -----------------------------------------------------------------------------------------------------

CTransport::CTransport(NetLib::TransportID id, const TCHAR *pName, CTransponder *pTransponder)
{
	m_pSendThread = NULL;
	m_pRecvThread = NULL;

	m_id = id;
	m_name = pName ? pName : _T("");

	m_uPort = 0;

	m_pTransponder = pTransponder;
	m_bContented = FALSE;
}

// -----------------------------------------------------------------------------------------------------

CTransport::CTransport(const Skyray::CSocket &acceptSocket, NetLib::TransportID id, const TCHAR *pName, CTransponder *pTransponder) : m_socket(acceptSocket)
{
	m_id = id;
	m_name = pName ? pName : _T("");
	m_pTransponder = pTransponder;
	m_bContented = TRUE;

	m_pSendThread = new CSendThread(&m_socket, this, m_pTransponder ? m_pTransponder->ConsoleThread() : NULL);
	m_pSendThread->Start();

	m_pRecvThread = new CRecvThread(&m_socket, this, m_pTransponder ? m_pTransponder->ConsoleThread() : NULL);
	m_pRecvThread->Start();
	
	if(!IsRun())
		StartTimer(10*1000);
}

// -----------------------------------------------------------------------------------------------------

CTransport::~CTransport()
{
	m_socket.Close();
	
	KillTimer();

	if(m_pSendThread)
	{
		while(m_pSendThread->IsRuning())
			m_pSendThread->Sleep(10);

		delete m_pSendThread;
		m_pSendThread = NULL;
	}

	if(m_pRecvThread)
	{
		while(m_pRecvThread->IsRuning())
			m_pRecvThread->Sleep(10);

		delete m_pRecvThread;
		m_pRecvThread = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

BOOL CTransport::Connect(const wchar_t *pIP, UINT uPort)
{
	if(m_socket.IsValid() && m_bContented)
		return TRUE;
	
	if((NULL == pIP) || (0 == wcslen(pIP)))
		return FALSE;

	m_strIP = pIP;
	m_uPort = uPort;
	
	return Start();
}

// -----------------------------------------------------------------------------------------------------

BOOL CTransport::Send(char cType, UINT uTo, NetLib::IPacking *pPacking)
{
	if(NULL == m_pSendThread)
		return FALSE;
	else
		return m_pSendThread->Send(cType, uTo, pPacking);
}

// -----------------------------------------------------------------------------------------------------

void CTransport::OnReceive(UINT uTo, NetLib::IUnpacking *pUnpacking)
{
	if(m_pTransponder)
		m_pTransponder->OnReceive(m_id, uTo, pUnpacking);
}

// -----------------------------------------------------------------------------------------------------

void CTransport::OnDisconnect()
{
	m_bContented = FALSE;
	if(m_socket.IsValid())
	{
		m_socket.Close();
		if(m_pTransponder)
			m_pTransponder->OnDisconnect(m_id);
	}
}

// -----------------------------------------------------------------------------------------------------

DWORD CTransport::Run()
{
	m_socket.Create();
	if(m_socket.Connect(m_strIP.c_str(), m_uPort))
	{
		m_bContented = TRUE;

		if(NULL == m_pSendThread)
			m_pSendThread = new CSendThread(&m_socket, this, m_pTransponder ? m_pTransponder->ConsoleThread() : NULL);
		m_pSendThread->Start();

		if(NULL == m_pRecvThread)
			m_pRecvThread = new CRecvThread(&m_socket, this, m_pTransponder ? m_pTransponder->ConsoleThread() : NULL);
		m_pRecvThread->Start();

		if(m_pTransponder)
			m_pTransponder->OnConnected(m_id);

		if(!IsRun())
			StartTimer(10*1000);
	}
	else
	{
		m_socket.Close();

		if(m_pTransponder)
			m_pTransponder->OnDisconnect(m_id);
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

void CTransport::TimerProc()
{
	if(m_socket.IsValid())
		Send(_T('H'), 0, NULL);
}