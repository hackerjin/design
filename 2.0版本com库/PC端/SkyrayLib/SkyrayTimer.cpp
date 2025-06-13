#include "SkyrayTimer.h"
#include <Mmsystem.h>

#pragma comment(lib, "Winmm.lib") 

namespace Skyray
{
	// -----------------------------------------------------------------------------------------------------

	CTimer::CTimer()
	{
		m_timerID		= NULL;
	}

	// -----------------------------------------------------------------------------------------------------

	CTimer::~CTimer()
	{
		if(NULL != m_timerID)
			timeKillEvent(m_timerID);
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CTimer::StartTimer(DWORD nElapse, BOOL bOnce)
	{
		TIMECAPS			tc;
		UINT				wAccuracy;

		if(m_timerID)
			return FALSE;

		if(timeGetDevCaps(&tc, sizeof(TIMECAPS)) == TIMERR_NOERROR)
		{
			wAccuracy = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
			timeBeginPeriod(wAccuracy);		

			if(bOnce)
				m_timerID = timeSetEvent(nElapse, wAccuracy, CTimer::TimerProc, (DWORD)this, TIME_ONESHOT);
			else
				m_timerID = timeSetEvent(nElapse, wAccuracy, CTimer::TimerProc, (DWORD)this, TIME_PERIODIC);

			if(NULL == m_timerID)
				return FALSE;
			else
				return TRUE;
		} 

		return FALSE;
	}

	// -----------------------------------------------------------------------------------------------------

	void CTimer::KillTimer()
	{
		if(NULL != m_timerID)
		{
			timeKillEvent(m_timerID);
			m_timerID = NULL;
		}
	}

	// -----------------------------------------------------------------------------------------------------

	void PASCAL CTimer::TimerProc(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
	{
		CTimer			*pTimer;

		pTimer = (CTimer *)dwUser;	
		pTimer->TimerProc();	
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CTimer::IsRun()
	{
		return (NULL != m_timerID);	
	}
}
