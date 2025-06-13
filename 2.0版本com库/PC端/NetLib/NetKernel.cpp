#include "stdafx.h"
#include "NetKernel.h"
#include "SkyrayUtil.h"

// -----------------------------------------------------------------------------------------------------

NetLib::INetKernel* CNetKernel::Instance()
{
	static CNetKernel		netKernel;

	return &netKernel;
}

// -----------------------------------------------------------------------------------------------------

CNetKernel::CNetKernel() : m_transponder(&m_endPointMgr, &m_consoleThread), m_remoteServer(&m_transponder)
{
	m_consoleThread.SetTransponder(&m_transponder);
}

// -----------------------------------------------------------------------------------------------------

CNetKernel::~CNetKernel()
{

}

// -----------------------------------------------------------------------------------------------------

BOOL CNetKernel::Startup(const wchar_t *pIP, UINT uPort)
{
	NetLib::ITransport	*pTransport;
	CTransport			*pApparatus;

	pTransport = m_transponder.FindTransport(NetLib::e_apparatus_transport);
	if(NULL == pTransport)
		pApparatus = new CTransport(NetLib::e_apparatus_transport, _T("下位机通道"), &m_transponder);
	else
		pApparatus = static_cast<CTransport *>(pTransport);

	if(pApparatus->Connect(pIP, uPort))
	{
		m_transponder.Add(pApparatus);
		return TRUE;
	}

	return FALSE;
}

// -----------------------------------------------------------------------------------------------------

void CNetKernel::Shutdown()
{
	m_transponder.RemoveAll();
}

// -----------------------------------------------------------------------------------------------------

BOOL CNetKernel::StartupRemote(const wchar_t *pIP, UINT uPort)
{
	NetLib::ITransport	*pTransport;
	CTransport			*pOtherPC;
	
	pTransport = m_transponder.FindTransport(NetLib::e_remote_transport);
	if(NULL == pTransport)
		pOtherPC = new CTransport(NetLib::e_remote_transport, _T("远端PC通道"), &m_transponder);
	else
		pOtherPC = static_cast<CTransport *>(pTransport);

	if(pOtherPC->Connect(pIP, uPort))
	{
		m_transponder.Add(pOtherPC);
		return TRUE;
	}

	return FALSE;
}

// -----------------------------------------------------------------------------------------------------

void CNetKernel::ShutdownRemote()
{
	m_transponder.Remove(NetLib::e_remote_transport);
}

// -----------------------------------------------------------------------------------------------------

BOOL CNetKernel::StartupRemoteServer(const wchar_t *pIP, UINT uPort)
{
	return m_remoteServer.Startup(pIP, uPort);
}

// -----------------------------------------------------------------------------------------------------

void CNetKernel::ShutdownRemoteServer()
{
	m_transponder.Remove(NetLib::e_assistance_transport);
	return m_remoteServer.Shutdown();
}

// -----------------------------------------------------------------------------------------------------

void CNetKernel::OpenConsole()
{
	m_consoleThread.ShowConsole(TRUE);
}

// -----------------------------------------------------------------------------------------------------

void CNetKernel::ConsolePrint(const wchar_t *pText)
{
	tstring			strText;

#ifdef _UNICODE
	strText = pText;
#else
	Skyray::Unicode2Ansi(pText, strText);
#endif

	m_consoleThread.AddText(strText.c_str());
}

// -----------------------------------------------------------------------------------------------------

void CNetKernel::CloseConsole()
{
	m_consoleThread.ShowConsole(FALSE);
}

// -----------------------------------------------------------------------------------------------------

void CNetKernel::Destroy()
{
	m_transponder.RemoveAll();
	m_remoteServer.Shutdown();
	m_endPointMgr.Clear();
	m_consoleThread.Destroy();
}