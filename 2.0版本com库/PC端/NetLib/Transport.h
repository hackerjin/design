#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file ITransport.h
* @brief ������
*  
* ��Ҫְ��ʵ�ִ������ӿ�
*
* @version 1.0
* @author  ����
* @date    2010��8��4��
*  
*  
* �޶�˵��������汾  
*/

#include "ITransport.h"
#include "SkyraySocket.h"
#include "SendThread.h"
#include "RecvThread.h"
#include "SkyrayTimer.h"
#include "SkyrayThread.h"
#include "SkyrayUtil.h"

class CTransponder;
class CTransport : public NetLib::ITransport
				 , public Skyray::CTimer
				 , public Skyray::CThread
{
public:
	CTransport(NetLib::TransportID, const TCHAR *pName, CTransponder *pTransponder);
	CTransport(const Skyray::CSocket &acceptSocket, NetLib::TransportID id, const TCHAR *pName, CTransponder *pTransponder);
	~CTransport();

public:
	/** 
	 @brief		��ȡ��������ʶ��
	 @return	��������ʶ��
	*/
	NetLib::TransportID ID() { return m_id; }
	
	/** 
	@brief		��ȡ����������
	@return		����������
	*/
	const TCHAR* Name() { return m_name.c_str(); }

	/** 
	 @brief	��������
	 @param	pIP		���ӵ�Ŀ��˵�IP��ַ
	 @param	uPort	���ӵ�Ŀ��˵Ķ˿ں�
	 @return	== TRUE	���ӽ����ɹ�
				== FALSE	���ӽ���ʧ��
	*/
	BOOL Connect(const wchar_t *pIP, UINT uPort);
	
	/** 
	 @brief	��������
	 @param	cType		���������ݵ�����
	 @param uTo			���������ݵ�Ŀ�ĵ�ַ
	 @param	pPacking	������ӿڣ����������͵����ݣ�
	 @return	== TRUE		���ͳɹ��������Ƿ������ݽ����˷��Ͷ��У�����֤����һ������ͻ��ˣ�
				== FALSE	����ʧ��
	*/
	BOOL Send(char cType, UINT uTo, NetLib::IPacking *pPacking);
	
	/** 
	@brief	�����Ƿ��Ѿ�����
	@return == TRUE	�����Ѿ�����
	== FALSE	����δ����
	*/
	BOOL IsConnected() { return m_bContented; }

	/** 
	 @brief	���ٽӿ�
	*/
	void Destroy() { delete this; }
	
	/** 
	 @brief	���յ�һ�����ݰ�
	 @param uTo			���ݰ���Ŀ�ĵ�ַ
	 @param	pUnpacking	������ӿڣ��������ݰ���Ϣ
	*/
	void OnReceive(UINT uTo, NetLib::IUnpacking *pUnpacking);

	/** 
	 @brief	������ϵ������ӶϿ�
	*/
	void OnDisconnect();
	
	/** 
	@��ʱ��ִ���壬��һ�����󷽷�����������ʵ��
	@Return	�̵߳ķ���ֵ
	*/
	void TimerProc();

private:
	DWORD Run();

private:
	NetLib::TransportID				m_id;				//!< ����ͨ����ʶ��
	tstring							m_name;				//!< ����ͨ��������
	CTransponder					*m_pTransponder;	//!< ����ͨ��������
	std::wstring					m_strIP;			//!< ����ͨ��Ŀ�ĵصĵ�ַ
	UINT							m_uPort;			//!< ����ͨ��Ŀ�ĵصĶ˿�
	Skyray::CSocket					m_socket;			//!< ���������׽���
	BOOL							m_bContented;		//!< �����Ƿ���
	CSendThread						*m_pSendThread;		//!< ���ݷ����߳�
	CRecvThread						*m_pRecvThread;		//!< ���ݽ����߳�
};

#endif