#ifndef _REMOTE_SERVER_H_
#define _REMOTE_SERVER_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file RemoteServer.h
* @brief Զ��Э��������
*  
* @version 1.0
* @author  ����
* @date    2010��8��6��
*  
*  
* �޶�˵��������汾  
*/

#include "SkyrayThread.h"
#include "SkyraySocket.h"

class CTransponder;
class CRemoteServer : public Skyray::CThread
{
public:
	CRemoteServer(CTransponder *pTransponder);
	~CRemoteServer();
	
	/** 
	 @brief		��������
	 @param		pIP		�����IP��ַ		
	 @param		uPort	����Ķ˿ں�
	 @return	TRUE���ӳɹ� FALSE����ʧ��
	*/
	BOOL Startup(const TCHAR *pIP, UINT uPort);
	
	/** 
	@brief		�رշ���
	*/
	void Shutdown();

private:
	DWORD Run();

private:
	CTransponder		*m_pTransponder;
	Skyray::CSocket		m_socket;
};

#endif