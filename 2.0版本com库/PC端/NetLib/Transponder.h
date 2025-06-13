#ifndef _TRANSPONDER_H_
#define _TRANSPONDER_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file ICapability.h
* @brief ת����
*  
* ��Ҫְ��ʵ��ת�����ӿ�
*
* @version 1.0
* @author  ����
* @date    2010��8��4��
*  
*  
* �޶�˵��������汾  
*/

#include "ITransponder.h"
#include "IEndPointMgr.h"
#include "INetKernelCallback.h"

class CConsoleThread;
class CTransponder : public NetLib::ITransponder
{
public:
	CTransponder(NetLib::IEndPointMgr *pEndPointMgr, CConsoleThread *pConsoleThread);
	~CTransponder();

public:
	/**
	 @brief ��������
	 @param	pTransport	�������ӿ�
	*/
	void Add(NetLib::ITransport *pTransport);
	
	/**
	 @brief �Ƴ�������
	 @param	id	��������ʶ��
	*/
	void Remove(NetLib::TransportID id);

	/** 
	 @brief	�Ƴ����д�����
	*/
	void RemoveAll();

	/**
	 @brief	��������
	 @param  id			��������Ӧ��ʹ�õĴ������ı�ʶ��
	 @param  uTo		�������ݵ��ն˱�ʶ��
	 @param	 pPacking	������ӿ�(�������������ݣ�
	 @return == TRUE ���ͳɹ��������Ƿ������ݽ����˷��Ͷ��У�����֤����һ������ͻ��ˣ�
			 == FALSE ����ʧ��
	*/
	BOOL Send(NetLib::TransportID id, UINT uTo, NetLib::IPacking *pPacking);
	
	/** 
	 @brief	���յ�һ�����ݰ�
	 @param id			���ݰ����ɱ�ʶΪid�Ĵ������յ�
	 @param uTo			���ݰ���Ŀ�ĵ�ַ
	 @param	pUnpacking	������ӿڣ��������ݰ���Ϣ
	*/
	void OnReceive(NetLib::TransportID id, UINT uTo, NetLib::IUnpacking *pUnpacking);
	
	/** 
	@brief	����ɹ�����
	@param id �������ı�ʶ��	
	*/
	void OnConnected(NetLib::TransportID id);

	/** 
	 @brief	������ϵ������ӶϿ�
	 @param id �������ı�ʶ��
	*/
	void OnDisconnect(NetLib::TransportID id);
	
	/** 
	 @brief		���ûص��ӿ�
	 @param		pCallback �����ں���Ļص��ӿ�
	*/
	void SetCallback(NetLib::INetKernelCallback *pCallback) { m_cb = pCallback; }
	
	/** 
	 @brief		��ȡ����̨�߳�
	 @param		����̨�̶߳���
	*/
	CConsoleThread* ConsoleThread() { return m_pConsoleThread; }
	
private:
	typedef std::list<NetLib::ITransport *>		TransportList;
	typedef TransportList::iterator				TransportIt;

public:
	NetLib::ITransport* FindTransport(NetLib::TransportID id);
	NetLib::ITransport* FindTransport(LPCTSTR lpName);

private:
	CConsoleThread					*m_pConsoleThread;	//!< ����̨�߳�
	NetLib::INetKernelCallback		*m_cb;				//!< �ص��ӿ�
	NetLib::IEndPointMgr			*m_pEndPointMgr;	//!< �ն˹������ӿ�
	TransportList					m_transports;		//!< �������ӿ�
};

#endif