#ifndef _REMOTE_SERVER_H_
#define _REMOTE_SERVER_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file RemoteServer.h
* @brief 远程协助服务器
*  
* @version 1.0
* @author  汤军
* @date    2010年8月6日
*  
*  
* 修订说明：最初版本  
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
	 @brief		启动服务
	 @param		pIP		服务的IP地址		
	 @param		uPort	服务的端口号
	 @return	TRUE连接成功 FALSE连接失败
	*/
	BOOL Startup(const TCHAR *pIP, UINT uPort);
	
	/** 
	@brief		关闭服务
	*/
	void Shutdown();

private:
	DWORD Run();

private:
	CTransponder		*m_pTransponder;
	Skyray::CSocket		m_socket;
};

#endif