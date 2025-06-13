#include "stdafx.h"
#include "ConsoleThread.h"

// -----------------------------------------------------------------------------------------------------

CConsoleThread::CConsoleThread()
{

}

// -----------------------------------------------------------------------------------------------------

CConsoleThread::~CConsoleThread()
{
	Destroy();
	while(IsRuning())
		Sleep(10);
}

// -----------------------------------------------------------------------------------------------------

void CConsoleThread::SetTransponder(NetLib::ITransponder *pTransponder)
{
	m_console.SetTransponder(pTransponder);
}

// -----------------------------------------------------------------------------------------------------

void CConsoleThread::AddType(NetLib::TransportID eID, const TCHAR *pName)
{
	if(pName && (_tcslen(pName) > 0))
	{
		size_t				nCount = m_types.size();
		
		m_lock.Lock();
		for(size_t i=0; i<nCount; i++)
		{
			if(m_types[i].m_eID == eID)
			{
				m_lock.Unlock();			
				return;
			}
		}

		TypeItem			item;

		item.m_eID = eID;
		item.m_strName = pName ? pName : _T("");
		m_types.push_back(item);
		m_lock.Unlock();

		if(IsRuning() && m_console.m_hWnd)
		{
			tstring			*pTransportName = new tstring(pName);

			::SendMessage(m_console.m_hWnd, WM_INSERT_TYPE, (WPARAM)eID, (LPARAM)pTransportName);
		}
	}
}

// -----------------------------------------------------------------------------------------------------

void CConsoleThread::RemoveType(NetLib::TransportID eID)
{
	size_t				nCount = m_types.size();
	
	m_lock.Lock();
	for(size_t i=0; i<nCount; i++)
	{
		if(m_types[i].m_eID == eID)
		{
			TypeConstIt		it = m_types.begin();

			std::advance(it, i);
			m_types.erase(it);
			break;
		}
	}
	m_lock.Unlock();

	if(IsRuning() && m_console.m_hWnd)
		::SendMessage(m_console.m_hWnd, WM_REMOVE_TYPE, (WPARAM)eID, 0);
}

// -----------------------------------------------------------------------------------------------------

void CConsoleThread::ShowConsole(BOOL bShow)
{
	if(bShow)
	{
		if(IsRuning() && m_console.m_hWnd)
			m_console.ShowWindow(SW_SHOW);
		else
			Start();
	}
	else
	{
		if(IsRuning() && m_console.m_hWnd)
			m_console.ShowWindow(SW_HIDE);
	}
}

// -----------------------------------------------------------------------------------------------------

void CConsoleThread::AddData(const TCHAR *pName, UINT uTo, const char *pData, UINT uDataLen, BOOL bSend)
{
	if(IsOPenConsole())
	{
		ConsoleData			*pInfo = new ConsoleData;

		pInfo->m_strTransport = pName ? pName : _T("");
		pInfo->m_uTo = uTo;

		pInfo->m_pData = new char[uDataLen];
		memcpy_s(pInfo->m_pData, uDataLen, pData, uDataLen);
		pInfo->m_uDataLen	= uDataLen;

		pInfo->m_bSend = bSend;
		
		::PostMessage(m_console.m_hWnd, WM_INSERT_DATA, 0, (LPARAM)pInfo);
	}
}

// -----------------------------------------------------------------------------------------------------

void CConsoleThread::AddText(const TCHAR *pText)
{
	if(pText && (0 != _tcslen(pText)) && IsOPenConsole())
	{
		ConsoleText			*pInfo = new ConsoleText;

		pInfo->m_strTitle = pText;
		pInfo->m_dwThreadID = GetCurrentThreadId();
		::PostMessage(m_console.m_hWnd, WM_INSERT_TEXT, 0, (LPARAM)pInfo);
	}
}

// -----------------------------------------------------------------------------------------------------

DWORD CConsoleThread::Run()
{
	CMessageLoop		theLoop;
	size_t				nCount = m_types.size();

	m_console.Create(NULL);
	m_console.ShowWindow(SW_SHOW);
	
	m_lock.Lock();
	for(size_t i=0; i<nCount; i++)
		m_console.AddType(m_types[i].m_eID, m_types[i].m_strName);
	m_lock.Unlock();

	theLoop.Run();
	return 0;
}

// -----------------------------------------------------------------------------------------------------

void CConsoleThread::Destroy()
{
	if(IsRuning() && m_console.m_hWnd)
		::PostMessage(m_console.m_hWnd, WM_COMMAND, MAKEWPARAM(IDCANCEL, BN_CLICKED), (LPARAM)NULL);	
}

// -----------------------------------------------------------------------------------------------------

BOOL CConsoleThread::IsOPenConsole()
{
	if(IsRuning() && m_console.m_hWnd)
		return TRUE;

	return FALSE;
}