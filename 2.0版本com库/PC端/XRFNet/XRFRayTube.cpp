// XRFRay.cpp : Implementation of CXRFRay

#include "stdafx.h"
#include "XRFRayTube.h"

// -----------------------------------------------------------------------------------------------------

CXRFRayTube::CXRFRayTube()
{
	m_uVoltage = 0;
	m_uCurrent = 0;
	m_bUncover = FALSE;
	m_hNetWork = NULL;
	m_uCount = 0;

	memset(m_uIICVersion, 0, 4 * sizeof(UINT));
}

// -----------------------------------------------------------------------------------------------------

CXRFRayTube::~CXRFRayTube()
{

}

// -----------------------------------------------------------------------------------------------------

HRESULT CXRFRayTube::FinalConstruct()
{
	if (NULL == g_pNetKernel)
		return E_ACCESSDENIED;

	NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

	ATLASSERT(pEndPointMgr);
	if (NULL == pEndPointMgr)
		return E_ACCESSDENIED;

	m_uCount = 0;
	if (!pEndPointMgr->Add(static_cast<NetLib::IEndPoint *>(this)))
		return E_FAIL;

	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

void CXRFRayTube::FinalRelease()
{
	if (NULL != g_pNetKernel)
	{
		NetLib::IEndPointMgr		*pEndPointMgr = g_pNetKernel->EndPointMgr();

		pEndPointMgr->Remove(ID());
	}
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFRayTube::Open(void)//暂时未用
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_operator);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFRayTube::Close(void)//暂时未用
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_operator);
		pPacking->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

// -----------------------------------------------------------------------------------------------------

void CXRFRayTube::OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking)
{
	if (NetLib::e_apparatus_transport == eID)
	{
		char				cOperator;

		pUnpacking->Pop(cOperator);
		if (e_get_info == (unsigned char)cOperator)
		{
			short			uValue;
			char			cValue;

			pUnpacking->Pop(uValue);
			m_uVoltage = uValue;

			pUnpacking->Pop(uValue);
			m_uCurrent = uValue;

			pUnpacking->Pop(uValue);
			pUnpacking->Pop(uValue);

			pUnpacking->Pop(cValue);
			m_bUncover = cValue ? TRUE : FALSE;

			::SetEvent(m_hNetWork);
		}
		else if (e_ver == (unsigned char)cOperator)
		{
			char	uVersion;

			pUnpacking->Pop(uVersion);
			m_uIICVersion[0] = uVersion;//年1
			pUnpacking->Pop(uVersion);
			m_uIICVersion[1] = uVersion;//年2
			pUnpacking->Pop(uVersion);
			m_uIICVersion[2] = uVersion;//月
			pUnpacking->Pop(uVersion);
			m_uIICVersion[3] = uVersion;//日

			::SetEvent(m_hNetWork);
		}
		else if (e_get_doublevacuum == (unsigned char)cOperator)
		{
			int uValue;
			pUnpacking->Pop(uValue);
			m_vacuumUp = uValue;
			pUnpacking->Pop(uValue);
			m_vacuumDown = uValue;
			::SetEvent(m_hNetWork);
		}
		else if (e_pushButton == (unsigned char)cOperator)
		{
			char			cValue;

			pUnpacking->Pop(cValue);
			m_cPushButton = (UCHAR)cValue;

			g_pNetKernel->ConsolePrint(_T("收到按钮状态，发出收到信息的信号"));
			::SetEvent(m_hNetWork);

		}
		else if (e_get_vacuum == (unsigned char)cOperator)
		{
			int			uValue;

			pUnpacking->Pop(uValue);
			m_vacuum = uValue;

			::SetEvent(m_hNetWork);
		}
		else if (e_state_Motor == (unsigned char)cOperator)
		{
			char			cValue;

			pUnpacking->Pop(cValue);
			m_cState = (UCHAR)cValue;

			g_pNetKernel->ConsolePrint(_T("收到电机状态，发出收到信息的信号"));
			::SetEvent(m_hNetWork);
		}
		else if (e_chamber == (unsigned char)cOperator)
		{
			char			cValue;

			pUnpacking->Pop(cValue);
			m_cChamState[0] = (UCHAR)cValue;
			pUnpacking->Pop(cValue);
			m_cChamState[1] = (UCHAR)cValue;
			g_pNetKernel->ConsolePrint(_T("收到电机状态，发出收到信息的信号"));
			::SetEvent(m_hNetWork);
		}
		else if (e_switchinfo == (unsigned char)cOperator)
		{
			short cValue1;
			pUnpacking->Pop(cValue1);
			m_info = cValue1;


			g_pNetKernel->ConsolePrint(_T("收到光电开关状态，发出收到信息的信号"));
			::SetEvent(m_hNetWork);

		}
	}
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFRayTube::GetConfig(USHORT* pVoltage, USHORT* pCurrent, BOOL* pUncover, UINT uTimeOut)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if (NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_get_info);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uCount++;
			m_lock.Unlock();
		}

		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			hReturn = S_OK;
			if (pVoltage)
				*pVoltage = m_uVoltage;

			if (pCurrent)
				*pCurrent = m_uCurrent;

			if (pUncover)
				*pUncover = m_bUncover;
		}
		else
		{
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if (0 == m_uCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if (S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				::SetEvent(m_hNetWork);
		}
		m_lock.Unlock();

		return hReturn;
	}

	return E_ABORT;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFRayTube::SetConfig(USHORT uVoltage, USHORT uCurrent)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		if ((0 != uVoltage) && (0 != uCurrent))
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();
			short						nSpace = 0;

			pPacking->Push((char)e_set_info);
			pPacking->Push((short)uVoltage);
			pPacking->Push((short)uCurrent);
			pPacking->Push(nSpace);
			pPacking->Push(nSpace);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}

		return S_OK;
	}

	return E_ABORT;
}


STDMETHODIMP CXRFRayTube::CheckVersion(UINT pVersion[], UINT uTimeOut)
{
	// TODO: 在此添加实现代码
	if (NULL == pVersion)
		return E_INVALIDARG;

	//*pVersion = 0;
	memset(pVersion, 0, 4 * sizeof(UINT));
	if (0 == m_uIICVersion[0])		//未取到IIC的版本号
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if (NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_ver);
			pPacking->Push((char)0x01);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else
		{
			m_uCount++;
			m_lock.Unlock();
		}

		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			if (0 != m_uIICVersion[0])
			{
				/*if(g_uIICVersion <= g_uLocalIICVersion)
				*pCanUse = TRUE;*/
				pVersion[0] = m_uIICVersion[0];
				pVersion[1] = m_uIICVersion[1];
				pVersion[2] = m_uIICVersion[2];
				pVersion[3] = m_uIICVersion[3];
			}

			hReturn = S_OK;
		}
		else
		{
			m_uIICVersion[0] = 0;
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if (0 == m_uCount)			//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if (S_OK == m_uCount)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				::SetEvent(m_hNetWork);
		}
		m_lock.Unlock();

		return hReturn;
	}
	else
	{
		/*if(g_uIICVersion <= g_uLocalIICVersion)
		*pCanUse = TRUE;*/
		pVersion[0] = m_uIICVersion[0];
		pVersion[1] = m_uIICVersion[1];
		pVersion[2] = m_uIICVersion[2];
		pVersion[3] = m_uIICVersion[3];
	}
	return S_OK;
}

STDMETHODIMP CXRFRayTube::bXRayTubeSel(UINT index)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_xray_sel);
		pPacking->Push((char)index);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}
	return E_ABORT;
}
//真空度------------------begin------------------------------------
STDMETHODIMP CXRFRayTube::OpenVacuumPump(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)0x15);
		pPacking->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::CloseVacuumPump(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)0x15);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}
STDMETHODIMP CXRFRayTube::GetVacuum(UINT uType, UINT* pVacuum, UINT uTimeOut)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if (NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_get_vacuum);
			pPacking->Push((int)uType);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uCount++;
			m_lock.Unlock();
		}

		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			hReturn = S_OK;
			if (pVacuum)
				*pVacuum = m_vacuum;
		}
		else
		{
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if (0 == m_uCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if (S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				::SetEvent(m_hNetWork);
		}
		m_lock.Unlock();

		return hReturn;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::GetDoubleVacuum(UINT uType, UINT* pUpVacuum, UINT* pDownVacuum, UINT uTimeOut)
{
	// TODO: 在此添加实现代码
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if (NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_get_doublevacuum);
			pPacking->Push((int)uType);
			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uCount++;
			m_lock.Unlock();
		}

		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			hReturn = S_OK;
			if (pDownVacuum)
			{
				*pDownVacuum = m_vacuumDown;
			}
			if (pUpVacuum)
			{
				*pUpVacuum = m_vacuumUp;
			}
		}
		else
		{
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if (0 == m_uCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if (S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
				::SetEvent(m_hNetWork);
		}
		m_lock.Unlock();

		return hReturn;
	}
	return E_ABORT;
}


//真空度-----------------------------end-------------------------

//按键---------------------------begin---------------------------------------
STDMETHODIMP CXRFRayTube::GetPushButtonInfo(UCHAR * pInfo, UINT uTimeOut)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if (NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_pushButton);

			g_pNetKernel->ConsolePrint(_T("发送获取光电状态的请求"));

			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uCount++;
			m_lock.Unlock();
		}

		g_pNetKernel->ConsolePrint(_T("等待下位机应答"));

		//等待同步信号被通知
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			g_pNetKernel->ConsolePrint(_T("获取光电的位置信息状态"));
			hReturn = S_OK;
			if (pInfo)
				*pInfo = m_cPushButton;
		}
		else
		{
			g_pNetKernel->ConsolePrint(_T("等待超时"));
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if (0 == m_uCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if (S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
			{
				g_pNetKernel->ConsolePrint(_T("通知其他需要获取电机状态信息的线程"));
				::SetEvent(m_hNetWork);
			}
		}
		m_lock.Unlock();

		return hReturn;
	}

	return E_ABORT;
}
STDMETHODIMP CXRFRayTube::ClearPushButtonInfo()
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_clearpushStatus);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);

		Sleep(10);
		NetLib::ITransponder		*pTransponder1 = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking1 = g_pNetKernel->CreatePacking();
		pPacking1->Push((char)e_clearpushStatus);
		pPacking1->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking1);

		return S_OK;
	}

	return E_ABORT;
}
//按键---------------------------end---------------------------------------


//高压----------------------------begin---------------------------------------

STDMETHODIMP CXRFRayTube::OpenHighVoltage(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_control_HighVoltage);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::CloseHighVoltage(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_control_HighVoltage);
		pPacking->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::AllowUncover(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_cover_HighVoltage);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::ForbidUncover(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_cover_HighVoltage);
		pPacking->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::OpenPilotLamp(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_pilot_lamp_HighVoltage);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::ClosePilotLamp(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_pilot_lamp_HighVoltage);
		pPacking->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

//高压----------------------------end-------------------------------------------

//激光-------------------------begin---------------------------
STDMETHODIMP CXRFRayTube::OpenElectromagnet(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_controlElectromagnet);
		pPacking->Push((char)0x01);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CXRFRayTube::CloseElectromagnet(void)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_controlElectromagnet);
		pPacking->Push((char)0x00);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::OpenLaserControl(BYTE byteOpen)
{
	// TODO: Add your implementation code here
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_controlLaser);
		pPacking->Push((char)byteOpen);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}
	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::SetLaserMode(BYTE bManual)
{
	// TODO: Add your implementation code here
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_LaserMode);
		pPacking->Push((char)bManual);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}
	return E_ABORT;
}


//激光----------------------end----------------------------------------

//-----------------------面光源----------------------------------
STDMETHODIMP CXRFRayTube::SetSurfaceLight(USHORT uFirstLight, USHORT uSecondLight, USHORT uThirdLight, USHORT uFourthLight)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_control_SurfaceSource);
		pPacking->Push((short)uFirstLight);
		pPacking->Push((short)uSecondLight);
		pPacking->Push((short)uThirdLight);
		pPacking->Push((short)uFourthLight);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}
//--------------------------------电机--------------------------
STDMETHODIMP CXRFRayTube::GetMotorState(UCHAR *pState, UINT uTimeOut)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if (NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_state_Motor);

			g_pNetKernel->ConsolePrint(_T("发送获取电机信息状态的请求"));

			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uCount++;
			m_lock.Unlock();
		}

		g_pNetKernel->ConsolePrint(_T("等待下位机应答"));

		//等待同步信号被通知
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			g_pNetKernel->ConsolePrint(_T("获取到电机的信息状态"));
			hReturn = S_OK;
			if (pState)
				*pState = m_cState;
		}
		else
		{
			g_pNetKernel->ConsolePrint(_T("等待超时"));
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if (0 == m_uCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if (S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
			{
				g_pNetKernel->ConsolePrint(_T("通知其他需要获取电机状态信息的线程"));
				::SetEvent(m_hNetWork);
			}
		}
		m_lock.Unlock();

		return hReturn;
	}

	return E_ABORT;
}


// 追加z轴电机比率-->样品腔的正偏移  追加样品腔的负偏移
STDMETHODIMP CXRFRayTube::MotorMove(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate, USHORT uDutyRatio, USHORT uChamberCoef2)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_control_Motor);
		pPacking->Push((char)cID);
		pPacking->Push((char)cDirection);
		pPacking->Push((short)uStep);
		pPacking->Push((char)cSwitch);
		pPacking->Push((char)cRate);
		pPacking->Push((short)uDutyRatio);
		pPacking->Push((short)uChamberCoef2);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}

	return E_ABORT;
}


STDMETHODIMP CXRFRayTube::GetChamberState(UCHAR pState[], UINT pStateLen, UINT uTimeOut)
{
	// TODO: Add your implementation code here
	memset(m_cChamState, 0, 2 * sizeof(UCHAR));
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if (NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_chamber);

			g_pNetKernel->ConsolePrint(_T("发送获取电机信息状态的请求"));

			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uCount++;
			m_lock.Unlock();
		}

		g_pNetKernel->ConsolePrint(_T("等待下位机应答"));

		//等待同步信号被通知
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			memcpy(pState, m_cChamState, 2 * sizeof(UCHAR));
			g_pNetKernel->ConsolePrint(_T("获取到电机的信息状态"));
			hReturn = S_OK;

		}
		else
		{
			g_pNetKernel->ConsolePrint(_T("等待超时"));
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if (0 == m_uCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if (S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
			{
				g_pNetKernel->ConsolePrint(_T("通知其他需要获取电机状态信息的线程"));
				::SetEvent(m_hNetWork);
			}
		}
		m_lock.Unlock();

		return hReturn;
	}
	return S_OK;
}

STDMETHODIMP CXRFRayTube::MoveZAutoMotor(UCHAR cRate)
{
	// TODO: Add your implementation code here
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
		NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

		pPacking->Push((char)e_controlZAutoMoter);
		pPacking->Push((char)cRate);
		pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		return S_OK;
	}
	return E_ABORT;
}

STDMETHODIMP CXRFRayTube::GetSwitchInfo(SHORT* pInfo, UINT uTimeOut)
{
	if (g_uIICVersion <= g_uLocalIICVersion)
	{
		HRESULT			hReturn;

		m_lock.Lock();
		if (NULL == m_hNetWork)	//同步对象不存在，以为着没有同步的通讯请求
		{
			NetLib::ITransponder		*pTransponder = g_pNetKernel->Transponder();
			NetLib::IPacking			*pPacking = g_pNetKernel->CreatePacking();

			m_hNetWork = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			ATLASSERT(m_hNetWork);
			m_lock.Unlock();

			pPacking->Push((char)e_switchinfo);

			g_pNetKernel->ConsolePrint(_T("发送获取光电状态的请求"));

			pTransponder->Send(NetLib::e_apparatus_transport, ID(), pPacking);
		}
		else					//同步对象存在，存在一个同步的通讯请求正在处理（由另一个线程发起)
		{
			m_uCount++;
			m_lock.Unlock();
		}

		g_pNetKernel->ConsolePrint(_T("等待下位机应答"));

		//等待同步信号被通知
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hNetWork, (0 == uTimeOut) ? INFINITE : uTimeOut))
		{
			g_pNetKernel->ConsolePrint(_T("获取光电的位置信息状态"));
			hReturn = S_OK;
			if (pInfo)
				*pInfo = m_info;
		}
		else
		{
			g_pNetKernel->ConsolePrint(_T("等待超时"));
			hReturn = E_FAIL;
		}

		m_lock.Lock();
		if (0 == m_uCount)		//没有其他的同步请求需要通知
		{
			::CloseHandle(m_hNetWork);
			m_hNetWork = NULL;
		}
		else
		{
			m_uCount--;
			if (S_OK == hReturn)	//如果同步处理成功发处理成功的信号，否则让其自己等待超时
			{
				g_pNetKernel->ConsolePrint(_T("通知其他需要获取电机状态信息的线程"));
				::SetEvent(m_hNetWork);
			}
		}
		m_lock.Unlock();

		return hReturn;
	}

	return E_ABORT;
}