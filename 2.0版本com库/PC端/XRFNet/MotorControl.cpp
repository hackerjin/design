// MotorControl.cpp : Implementation of CMotorControl

#include "stdafx.h"
#include "MotorControl.h"

// -----------------------------------------------------------------------------------------------------

HRESULT CMotorControl::FinalConstruct()
{
	if(NULL == g_pNetKernel)
		return E_ACCESSDENIED;

	NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

	ATLASSERT(pEndPointMgr);
	if(NULL == pEndPointMgr)
		return E_ACCESSDENIED;
	
	m_hNetWork = NULL;
	m_uCount = 0;
	if(!pEndPointMgr->Add(static_cast<NetLib::IEndPoint *>(this)))
		return E_FAIL;

	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

void CMotorControl::FinalRelease()
{
	if(NULL != m_hNetWork)
	{
		CloseHandle(m_hNetWork);
		m_hNetWork = NULL;
	}

	if(NULL != g_pNetKernel)
	{
		NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

		pEndPointMgr->Remove(ID());
	}
}

// -----------------------------------------------------------------------------------------------------

//STDMETHODIMP CMotorControl::GetState(UCHAR *pState, UINT uTimeOut)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		HRESULT			hReturn;
//		
//		m_lock.Lock();
//		if(NULL == m_hNetWork)	//ͬ�����󲻴��ڣ���Ϊ��û��ͬ����ͨѶ����
//		{
//			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
//			ATLASSERT(m_hNetWork);
//			m_lock.Unlock();
//
//			pPacking->Push((char)e_state);
//
//			g_pNetKernel->ConsolePrint(_T("���ͻ�ȡ�����Ϣ״̬������"));
//
//			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		}
//		else					//ͬ��������ڣ�����һ��ͬ����ͨѶ�������ڴ�������һ���̷߳���)
//		{
//			m_uCount++;
//			m_lock.Unlock();
//		}
//		
//		g_pNetKernel->ConsolePrint(_T("�ȴ���λ��Ӧ��"));
//
//		//�ȴ�ͬ���źű�֪ͨ
//		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
//		{
//			g_pNetKernel->ConsolePrint(_T("��ȡ���������Ϣ״̬"));
//			hReturn = S_OK;
//			if(pState)
//				*pState = m_cState;
//		}
//		else
//		{	
//			g_pNetKernel->ConsolePrint(_T("�ȴ���ʱ"));
//			hReturn = E_FAIL;
//		}
//
//		m_lock.Lock();
//		if(0 == m_uCount)		//û��������ͬ��������Ҫ֪ͨ
//		{
//			::CloseHandle(m_hNetWork);
//			m_hNetWork = NULL;
//		}
//		else
//		{
//			m_uCount--;
//			if(S_OK == hReturn)	//���ͬ������ɹ�������ɹ����źţ����������Լ��ȴ���ʱ
//			{
//				g_pNetKernel->ConsolePrint(_T("֪ͨ������Ҫ��ȡ���״̬��Ϣ���߳�"));
//				::SetEvent(m_hNetWork);
//			}
//		}
//		m_lock.Unlock();
//
//		return hReturn;
//	}
//
//	return E_ABORT;
//}

// -----------------------------------------------------------------------------------------------------

//STDMETHODIMP CMotorControl::Move(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_control);
//		pPacking->Push((char)cID);
//		pPacking->Push((char)cDirection);
//		pPacking->Push((short)uStep);
//		pPacking->Push((char)cSwitch);
//		pPacking->Push((char)cRate);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}
//2012-07-24 ׷��z��������
//STDMETHODIMP CMotorControl::Move(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate,USHORT uDutyRatio)
//2014-10-10 ׷��z��������-->��Ʒǻ����ƫ��  ׷����Ʒǻ�ĸ�ƫ��
//STDMETHODIMP CMotorControl::Move(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate,USHORT uDutyRatio,USHORT uChamberCoef2)
//{
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_control);
//		pPacking->Push((char)cID);
//		pPacking->Push((char)cDirection);
//		pPacking->Push((short)uStep);
//		pPacking->Push((char)cSwitch);
//		pPacking->Push((char)cRate);
//		pPacking->Push((short)uDutyRatio);
//		pPacking->Push((short)uChamberCoef2);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//
//	return E_ABORT;
//}

// -----------------------------------------------------------------------------------------------------

void CMotorControl::OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking)
{
	//if(NetLib::e_apparatus_transport == eID)
	//{
	//	char				cOperator;

	//	pUnpacking->Pop(cOperator);
	//	if(e_state == (unsigned char)cOperator)
	//	{
	//		char			cValue;

	//		pUnpacking->Pop(cValue);
	//		m_cState = (UCHAR)cValue;

	//		g_pNetKernel->ConsolePrint(_T("�յ����״̬�������յ���Ϣ���ź�"));
	//		::SetEvent(m_hNetWork);
	//	}
	//	else if(e_chamber==(unsigned char)cOperator)
	//	{
	//		char			cValue;

	//		pUnpacking->Pop(cValue);
	//		m_cChamState[0] = (UCHAR)cValue;
	//		pUnpacking->Pop(cValue);
	//		m_cChamState[1] = (UCHAR)cValue;
	//		g_pNetKernel->ConsolePrint(_T("�յ����״̬�������յ���Ϣ���ź�"));
	//		::SetEvent(m_hNetWork);
	//	}
	//	else if(e_switchinfo == (unsigned char)cOperator)
	//	{
	//		short cValue1;
	//		pUnpacking->Pop(cValue1);
	//		m_info = cValue1;


	//		g_pNetKernel->ConsolePrint(_T("�յ���翪��״̬�������յ���Ϣ���ź�"));
	//		::SetEvent(m_hNetWork);

	//	}
	///*	else if(e_pushButton == (unsigned char)cOperator)
	//	{
	//		char			cValue;

	//		pUnpacking->Pop(cValue);
	//		m_cPushButton = (UCHAR)cValue;

	//		g_pNetKernel->ConsolePrint(_T("�յ���ť״̬�������յ���Ϣ���ź�"));
	//		::SetEvent(m_hNetWork);

	//	}*/
	//}	
}

//STDMETHODIMP CMotorControl::GetChamberState(UCHAR pState[], UINT pStateLen, UINT uTimeOut)
//{
//	// TODO: Add your implementation code here
//	memset(m_cChamState,0,2*sizeof(UCHAR));
//	if(g_uIICVersion <= g_uLocalIICVersion)
//		{
//			HRESULT			hReturn;
//			
//			m_lock.Lock();
//			if(NULL == m_hNetWork)	//ͬ�����󲻴��ڣ���Ϊ��û��ͬ����ͨѶ����
//			{
//				NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//				NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//				m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
//				ATLASSERT(m_hNetWork);
//				m_lock.Unlock();
//
//				pPacking->Push((char)e_chamber);
//
//				g_pNetKernel->ConsolePrint(_T("���ͻ�ȡ�����Ϣ״̬������"));
//
//				pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//			}
//			else					//ͬ��������ڣ�����һ��ͬ����ͨѶ�������ڴ�������һ���̷߳���)
//			{
//				m_uCount++;
//				m_lock.Unlock();
//			}
//			
//			g_pNetKernel->ConsolePrint(_T("�ȴ���λ��Ӧ��"));
//
//			//�ȴ�ͬ���źű�֪ͨ
//			if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
//			{
//				memcpy(pState,m_cChamState,2*sizeof(UCHAR));
//				g_pNetKernel->ConsolePrint(_T("��ȡ���������Ϣ״̬"));
//				hReturn = S_OK;
//				
//			}
//			else
//			{	
//				g_pNetKernel->ConsolePrint(_T("�ȴ���ʱ"));
//				hReturn = E_FAIL;
//			}
//
//			m_lock.Lock();
//			if(0 == m_uCount)		//û��������ͬ��������Ҫ֪ͨ
//			{
//				::CloseHandle(m_hNetWork);
//				m_hNetWork = NULL;
//			}
//			else
//			{
//				m_uCount--;
//				if(S_OK == hReturn)	//���ͬ������ɹ�������ɹ����źţ����������Լ��ȴ���ʱ
//				{
//					g_pNetKernel->ConsolePrint(_T("֪ͨ������Ҫ��ȡ���״̬��Ϣ���߳�"));
//					::SetEvent(m_hNetWork);
//				}
//			}
//			m_lock.Unlock();
//
//			return hReturn;
//		}
//	return S_OK;
//	return S_OK;
//}

//STDMETHODIMP CMotorControl::MoveZAutoMotor(UCHAR cRate)
//{
//	// TODO: Add your implementation code here
//	if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_controlZAutoMoter);
//		pPacking->Push((char)cRate);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		return S_OK;
//	}
//	return E_ABORT;
//}

//STDMETHODIMP CMotorControl::GetSwitchInfo(SHORT* pInfo, UINT uTimeOut)
//{
//   if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		HRESULT			hReturn;
//		
//		m_lock.Lock();
//		if(NULL == m_hNetWork)	//ͬ�����󲻴��ڣ���Ϊ��û��ͬ����ͨѶ����
//		{
//			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();	
//
//			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
//			ATLASSERT(m_hNetWork);
//			m_lock.Unlock();
//
//			pPacking->Push((char)e_switchinfo);
//
//			g_pNetKernel->ConsolePrint(_T("���ͻ�ȡ���״̬������"));
//
//			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		}
//		else					//ͬ��������ڣ�����һ��ͬ����ͨѶ�������ڴ�������һ���̷߳���)
//		{
//			m_uCount++;
//			m_lock.Unlock();
//		}
//		
//		g_pNetKernel->ConsolePrint(_T("�ȴ���λ��Ӧ��"));
//
//		//�ȴ�ͬ���źű�֪ͨ
//		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
//		{
//			g_pNetKernel->ConsolePrint(_T("��ȡ����λ����Ϣ״̬"));
//			hReturn = S_OK;
//			if(pInfo)
//				*pInfo = m_info;
//		}
//		else
//		{	
//			g_pNetKernel->ConsolePrint(_T("�ȴ���ʱ"));
//			hReturn = E_FAIL;
//		}
//
//		m_lock.Lock();
//		if(0 == m_uCount)		//û��������ͬ��������Ҫ֪ͨ
//		{
//			::CloseHandle(m_hNetWork);
//			m_hNetWork = NULL;
//		}
//		else
//		{
//			m_uCount--;
//			if(S_OK == hReturn)	//���ͬ������ɹ�������ɹ����źţ����������Լ��ȴ���ʱ
//			{
//				g_pNetKernel->ConsolePrint(_T("֪ͨ������Ҫ��ȡ���״̬��Ϣ���߳�"));
//				::SetEvent(m_hNetWork);
//			}
//		}
//		m_lock.Unlock();
//
//		return hReturn;
//	}
//
//	return E_ABORT;
//}

//STDMETHODIMP CMotorControl::GetPushButtonInfo(UCHAR * pInfo, UINT uTimeOut)
//{
//    if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		HRESULT			hReturn;
//		
//		m_lock.Lock();
//		if(NULL == m_hNetWork)	//ͬ�����󲻴��ڣ���Ϊ��û��ͬ����ͨѶ����
//		{
//			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();	
//
//			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
//			ATLASSERT(m_hNetWork);
//			m_lock.Unlock();
//
//			pPacking->Push((char)e_pushButton);
//
//			g_pNetKernel->ConsolePrint(_T("���ͻ�ȡ���״̬������"));
//
//			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//		}
//		else					//ͬ��������ڣ�����һ��ͬ����ͨѶ�������ڴ�������һ���̷߳���)
//		{
//			m_uCount++;
//			m_lock.Unlock();
//		}
//		
//		g_pNetKernel->ConsolePrint(_T("�ȴ���λ��Ӧ��"));
//
//		//�ȴ�ͬ���źű�֪ͨ
//		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
//		{
//			g_pNetKernel->ConsolePrint(_T("��ȡ����λ����Ϣ״̬"));
//			hReturn = S_OK;
//			if(pInfo)
//				*pInfo = m_cPushButton;
//		}
//		else
//		{	
//			g_pNetKernel->ConsolePrint(_T("�ȴ���ʱ"));
//			hReturn = E_FAIL;
//		}
//
//		m_lock.Lock();
//		if(0 == m_uCount)		//û��������ͬ��������Ҫ֪ͨ
//		{
//			::CloseHandle(m_hNetWork);
//			m_hNetWork = NULL;
//		}
//		else
//		{
//			m_uCount--;
//			if(S_OK == hReturn)	//���ͬ������ɹ�������ɹ����źţ����������Լ��ȴ���ʱ
//			{
//				g_pNetKernel->ConsolePrint(_T("֪ͨ������Ҫ��ȡ���״̬��Ϣ���߳�"));
//				::SetEvent(m_hNetWork);
//			}
//		}
//		m_lock.Unlock();
//
//		return hReturn;
//	}
//
//	return E_ABORT;
//}
//STDMETHODIMP CMotorControl::ClearPushButtonInfo()
//{
//		if(g_uIICVersion <= g_uLocalIICVersion)
//	{
//		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
//
//		pPacking->Push((char)e_clearpushStatus);
//		pPacking->Push((char)0x01);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
//
//        Sleep(10);
//        NetLib::ITransponder		*pTransponder1 = g_pNetKernel->Transponder();
//		NetLib::IPacking			*pPacking1 = g_pNetKernel->CreatePacking();
//		pPacking1->Push((char)e_clearpushStatus);
//		pPacking1->Push((char)0x00);
//		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking1);
//
//		return S_OK;
//	}
//
//	return E_ABORT;
//}