#include "stdafx.h"
#include "EndPointMgr.h"

// -----------------------------------------------------------------------------------------------------

CEndPointMgr::CEndPointMgr()
{

}

// -----------------------------------------------------------------------------------------------------

CEndPointMgr::~CEndPointMgr()
{
	EndPointIt			it;
	
	m_lock.Lock();
	for(it = m_list.begin(); it != m_list.end(); it++)
		(*it)->Destroy();
	
	m_list.clear();
	m_lock.Unlock();
}

// -----------------------------------------------------------------------------------------------------

BOOL CEndPointMgr::Add(NetLib::IEndPoint *pEndPoint)
{
	BOOL		bReturn = TRUE;

	if(pEndPoint)
	{
		UINT		uID = pEndPoint->ID();
		
		m_lock.Lock();
		for(EndPointIt it = m_list.begin(); it != m_list.end(); it++)
		{
			if(uID == (*it)->ID())
			{
				bReturn = FALSE;
				break;
			}
		}

		if(bReturn)
			m_list.push_back(pEndPoint);

		m_lock.Unlock();
	}
	else
	{
		bReturn = FALSE;
	}

	return bReturn;
}

// -----------------------------------------------------------------------------------------------------

NetLib::IEndPoint* CEndPointMgr::Find(UINT uID)
{
	NetLib::IEndPoint *pEndPoint = NULL;

	m_lock.Lock();
	for(EndPointIt it = m_list.begin(); it != m_list.end(); it++)
	{
		if(uID == (*it)->ID())
		{
			pEndPoint = *it;
			break;
		}
	}
	m_lock.Unlock();

	return pEndPoint;
}

// -----------------------------------------------------------------------------------------------------

void CEndPointMgr::Remove(UINT uID)
{
	m_lock.Lock();
	for(EndPointIt it = m_list.begin(); it != m_list.end(); it++)
	{
		if(uID == (*it)->ID())
		{
			m_list.erase(it);		
			break;
		}
	}
	m_lock.Unlock();
}

// -----------------------------------------------------------------------------------------------------

void CEndPointMgr::Clear()
{
	EndPointIt			it;

	m_lock.Lock();
	for(it = m_list.begin(); it != m_list.end(); it++)
		(*it)->Destroy();

	m_list.clear();
	m_lock.Unlock();
}