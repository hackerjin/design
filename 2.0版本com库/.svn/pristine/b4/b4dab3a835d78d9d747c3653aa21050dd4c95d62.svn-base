#include "stdafx.h"
#include "EventMgr.h"

// -----------------------------------------------------------------------------------------------------

CEventMgr::CEventMgr()
{
	m_dwThreadID = 0;
	m_hThread = NULL;
	m_hWnd = NULL;
}

// -----------------------------------------------------------------------------------------------------

CEventMgr::~CEventMgr()
{
	if(m_hWnd)
	{
		::DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}

	if(m_hThread)
	{
		::CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

void CEventMgr::SetProcedureContext()
{
	if(NULL == m_hThread)
	{
		m_dwThreadID = ::GetCurrentThreadId();
		::DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);
		m_hWnd = CreateWindowEx(0, _T("STATIC"), NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
		SetWindowLongPtr(m_hWnd, GWL_WNDPROC, (LONG)(LONG_PTR)APCWndProc);
	}
}

// -----------------------------------------------------------------------------------------------------

BOOL CEventMgr::Register(LPCTSTR lpEventName)
{
	if((NULL == lpEventName) || (0 == _tcslen(lpEventName)))
		return FALSE;

	EventConstIt		it;
	tstring				strEventName(lpEventName);

	m_lock.Lock();
	it = m_events.find(strEventName);
	if(it == m_events.end())
		m_events[strEventName] = new ListenerList;
	m_lock.Unlock();

	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

void CEventMgr::Unregister(LPCTSTR lpEventName)
{
	if((NULL == lpEventName) || (0 == _tcslen(lpEventName)))
		return;

	EventConstIt		it;
	
	m_lock.Lock();
	it = m_events.find(tstring(lpEventName));
	if(it != m_events.end())
		m_events.erase(it);
	m_lock.Unlock();

	return;
}

// -----------------------------------------------------------------------------------------------------

BOOL CEventMgr::EventIsExist(LPCTSTR lpEventName)
{
	if((NULL == lpEventName) || (0 == _tcslen(lpEventName)))
		return FALSE;

	EventConstIt		it;
	BOOL				bFind;

	m_lock.Lock();
	it = m_events.find(tstring(lpEventName));
	bFind = (it != m_events.end());
	m_lock.Unlock();

	return bFind;
}

// -----------------------------------------------------------------------------------------------------

BOOL CEventMgr::Hook(LPCTSTR lpEventName, IEventListener *pListener)
{
	if((NULL == lpEventName) || (0 == _tcslen(lpEventName)) || (NULL == pListener))
		return FALSE;
	
	EventConstIt		it;
	tstring				strEventName(lpEventName);
	BOOL				bReturn = FALSE;

	m_lock.Lock();
	it = m_events.find(strEventName);
	if(it != m_events.end())
	{
		ListenerList	*pListenerList = it->second;
		ListenerIt		itListener;
		BOOL			bFind = FALSE;
		size_t			nSize = pListenerList->size();
		size_t			i;

		PushTraversal(strEventName);
		for(itListener = pListenerList->begin(), i = 0; (itListener != pListenerList->end()) && (i < nSize); itListener++, i++)
		{
			if(pListener == *itListener)
			{
				bFind = TRUE;
				break;
			}
		}
		PopTraversal();

		if(!bFind)
			pListenerList->push_back(pListener);
		bReturn = TRUE;
	}
	m_lock.Unlock();

	return bReturn;
}

// -----------------------------------------------------------------------------------------------------

void CEventMgr::Unhook(LPCTSTR lpEventName, IEventListener *pListener)
{
	if((NULL == lpEventName) || (0 == _tcslen(lpEventName)) || (NULL == pListener))
		return;

	EventConstIt		it;
	tstring				strEventName(lpEventName);

	m_lock.Lock();
	it = m_events.find(strEventName);
	if(it != m_events.end())
	{
		ListenerList	*pListenerList = it->second;
		ListenerIt		itListener;
		size_t			nSize = pListenerList->size();
		size_t			i;
		BOOL			bTraversal = IsTraversal(strEventName);
		

		PushTraversal(strEventName);
		for(itListener = pListenerList->begin(), i = 0; (itListener != pListenerList->end()) && (i < nSize); itListener++, i++)
		{
			if(pListener == *itListener)
			{
				if(bTraversal)
					*itListener = NULL;
				else
					pListenerList->erase(itListener);
				break;
			}
		}
		PopTraversal();
	}
	m_lock.Unlock();
}

// -----------------------------------------------------------------------------------------------------

BOOL CEventMgr::Notify(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam)
{
	if((NULL == m_hThread) || (NULL == lpEventName) || (0 == _tcslen(lpEventName)))
		return FALSE;
	
 	if(m_dwThreadID == ::GetCurrentThreadId())
 	{
 		return Procedure(lpEventName, wParam, lParam);
 	}
 	else
	{
		APCTask			*pTask = new APCTask;

		pTask->m_pEventMgr		= this;
		pTask->m_strEventName	= lpEventName;
		pTask->m_wParam			= wParam;
		pTask->m_lParam			= lParam;
		::QueueUserAPC(APCProc, m_hThread, (DWORD_PTR)pTask);
		::PostMessage(m_hWnd, WM_NULL, 0, 0);

		return TRUE;
	}
}


// -----------------------------------------------------------------------------------------------------

BOOL CEventMgr::Procedure(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam)
{
	EventConstIt		it;
	tstring				strEventName(lpEventName);
	BOOL				bReturn = FALSE;

	m_lock.Lock();
	it = m_events.find(strEventName);
	if(it != m_events.end())
	{
		ListenerList			*pListenerList = it->second;
		ListenerIt				itListener;
		IEventListener			*pListener = NULL;
		size_t					nSize = pListenerList->size();
		size_t					i;
		BOOL					bTraversal;

		PushTraversal(strEventName);
		for(itListener = pListenerList->begin(), i = 0; (itListener != pListenerList->end()) && (i < nSize); itListener++, i++)
		{
			pListener = *itListener;
			if(pListener)
				pListener->Procedure(lpEventName, wParam, lParam);
		}
		PopTraversal();
		
		bTraversal = IsTraversal(strEventName);
		if(!bTraversal)
		{
			for(itListener = pListenerList->begin(); itListener != pListenerList->end(); )
			{
				if(NULL == *itListener)
					itListener = pListenerList->erase(itListener);
				else
					itListener++;
			}
		}
		bReturn = TRUE;
	}
	m_lock.Unlock();

	return bReturn;
}

// -----------------------------------------------------------------------------------------------------

void CEventMgr::PushTraversal(const tstring &strName)
{
	m_traversalList.push_back(strName);
}

// -----------------------------------------------------------------------------------------------------

void CEventMgr::PopTraversal()
{
	m_traversalList.pop_back();
}

// -----------------------------------------------------------------------------------------------------

BOOL CEventMgr::IsTraversal(const tstring &strName)
{
	for(TraversalConstIt it = m_traversalList.begin(); it != m_traversalList.end(); it++)
	{
		if(strName == *it)
			return TRUE;
	}

	return FALSE;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CALLBACK CEventMgr::APCWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(msg==WM_NULL)
		SleepEx(0,TRUE);
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

// -----------------------------------------------------------------------------------------------------

void CALLBACK CEventMgr::APCProc(ULONG_PTR dwParam)
{
	APCTask			*pTask = (APCTask *)dwParam;

	if(pTask)
	{
		pTask->m_pEventMgr->Notify(pTask->m_strEventName.c_str(), pTask->m_wParam, pTask->m_lParam);
		delete pTask;
	}
}


