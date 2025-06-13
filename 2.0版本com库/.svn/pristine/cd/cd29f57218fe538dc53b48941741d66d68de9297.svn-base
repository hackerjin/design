#ifndef _SEND_THREAD_H_
#define _SEND_THREAD_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file CSendThread.h
* @brief 数据发送线程
*  
* 负责来至于不同终端（可能不在一个线程中）数据的依次发送。
*
* @version 1.0
* @author  汤军
* @date    2010年8月4日
*  
*  
* 修订说明：最初版本  
*/

#include "IPacking.h"

#include "SkyrayThread.h"
#include "SkyrayLock.h"
#include "SkyraySocket.h"

class CTransport;
class CConsoleThread;
class CSendThread : public Skyray::CThread
{
public:
	CSendThread(Skyray::CSocket	*pSocket, CTransport *pTransport, CConsoleThread *pConsoleThread);
	~CSendThread();
	

	/** 
	 @brief	发送数据
	 @param	cType		待发送数据的类型
	 @param uTo			待发送数据的目的地址
	 @param	pPacking	封包器接口（包含待发送的数据）
	 @return	== TRUE		发送成功（仅仅是发送数据进入了发送队列，不保证数据一定到达客户端）
				== FALSE	发送失败
	*/
	BOOL Send(char cType, UINT uTo, NetLib::IPacking *pPacking);

private:
	DWORD Run();
	void OnDisconnect();

private:
	static const UINT m_nPacketHeadLen = 9;		//('A'+四字节的目的地址+四字节的包长度)

private:
	struct Task
	{
		char				m_cType;
		UINT				m_uTo;
		NetLib::IPacking	*m_pPacking;
	};
	
	typedef std::list<Task>	TaskList;
	typedef TaskList::iterator TaskIt;

private:
	BOOL GetTask(Task &info);
	
private:
	Skyray::CSocket			*m_pSocket;
	CTransport				*m_pTransport;
	CConsoleThread			*m_pConsoleThread;

	Skyray::CLock			m_lock;
	TaskList				m_tasks;
};

#endif