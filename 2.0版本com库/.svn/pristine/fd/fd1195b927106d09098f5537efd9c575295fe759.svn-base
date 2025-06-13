#include "SkyrayThread.h"
#include <process.h>

namespace Skyray
{
	// -----------------------------------------------------------------------------------------------------

	CThread::CThread()
	{
		m_hThread		= NULL;
		m_dwThreadID	= 0;
	}

	// -----------------------------------------------------------------------------------------------------

	CThread::~CThread()
	{
		try {
			Terminate();
		}
		catch (...)
		{}
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CThread::Start()
	{
		if (IsRuning())
			Terminate();

		m_hThread = (HANDLE)_beginthreadex(NULL, 0, (PTHREAD_START)Runner, (void *)this, 0, (unsigned int *)&m_dwThreadID);
		return m_hThread ? TRUE : FALSE;
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CThread::IsCurrent() 
	{
		return (m_dwThreadID == Self());
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CThread::IsRuning()
	{
		return (NULL != m_hThread);
	}

	// -----------------------------------------------------------------------------------------------------

	DWORD CThread::Terminate()
	{
		DWORD dwExitCode	= 0;

		if (m_hThread != NULL)
			::TerminateThread(m_hThread, dwExitCode);

		if (m_hThread != NULL)
		{
			::CloseHandle(m_hThread);
			m_hThread = NULL;
			m_dwThreadID = 0;
		}
		
		return dwExitCode;
	}

	// -----------------------------------------------------------------------------------------------------

	void CThread::Sleep(int msec) 
	{
		::Sleep(msec);
	}

	// -----------------------------------------------------------------------------------------------------

	DWORD CThread::Self() 
	{
		return ::GetCurrentThreadId();
	}

	// -----------------------------------------------------------------------------------------------------

	DWORD __stdcall Runner(void* arg)
	{
		DWORD			dwResult;
		CThread*		t;

		t = (CThread*)arg;
		dwResult = t->Run();

		t->m_hThread	= NULL;
		t->m_dwThreadID	= 0;

		t->OnTerminate();
		return dwResult;
	}
}
