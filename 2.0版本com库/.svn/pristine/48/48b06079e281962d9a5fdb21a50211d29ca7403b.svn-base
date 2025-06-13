#ifndef _RECV_THREAD_H_
#define _RECV_THREAD_H_
/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file CSendThread.h
* @brief 数据接收线程
*  
* 负责接受来至以太网的数据，并以包的形式提供给传输。
*
* @version 1.0
* @author  汤军
* @date    2010年8月4日
*  
*  
* 修订说明：最初版本  
*/

#include "SkyrayThread.h"
#include "SkyrayUtil.h"
#include "SkyraySocket.h"

class CTransport;
class CConsoleThread;
class CRecvThread : public Skyray::CThread
{
public:
	CRecvThread(Skyray::CSocket	*pSocket, CTransport *pTransport, CConsoleThread *pConsoleThread);
	~CRecvThread();

private:
	DWORD Run();
	
	void AddData(char *pData, UINT uDataLen);
	void RemoveData(UINT uDataLen);
	void Parse();
	
	void OnDisconnect();

private:
	static const UINT m_uDefaultBufferSize = 10240;
	static const UINT m_nPacketHeadLen = 9;		//('A'+四字节的目的地址+四字节的包长度)

private:
	Skyray::CSocket			*m_pSocket;
	CTransport				*m_pTransport;
	CConsoleThread			*m_pConsoleThread;

	char					m_acDefaultBuffer[m_uDefaultBufferSize];
	
	char					*m_pBuffer;
	UINT					m_nBufferIndex;
	UINT					m_nBufferSize;
};

#endif