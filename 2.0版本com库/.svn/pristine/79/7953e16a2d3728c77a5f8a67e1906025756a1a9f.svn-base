#ifndef _TRANSPONDER_H_
#define _TRANSPONDER_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file ICapability.h
* @brief 转发器
*  
* 主要职责：实现转发器接口
*
* @version 1.0
* @author  汤军
* @date    2010年8月4日
*  
*  
* 修订说明：最初版本  
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
	 @brief 增添传输器
	 @param	pTransport	传输器接口
	*/
	void Add(NetLib::ITransport *pTransport);
	
	/**
	 @brief 移除传输器
	 @param	id	传输器标识符
	*/
	void Remove(NetLib::TransportID id);

	/** 
	 @brief	移除所有传输器
	*/
	void RemoveAll();

	/**
	 @brief	发送数据
	 @param  id			发送数据应该使用的传输器的标识符
	 @param  uTo		接收数据的终端标识符
	 @param	 pPacking	封包器接口(包含待发的数据）
	 @return == TRUE 发送成功（仅仅是发送数据进入了发送队列，不保证数据一定到达客户端）
			 == FALSE 发送失败
	*/
	BOOL Send(NetLib::TransportID id, UINT uTo, NetLib::IPacking *pPacking);
	
	/** 
	 @brief	接收到一个数据包
	 @param id			数据包是由标识为id的传输器收到
	 @param uTo			数据包的目的地址
	 @param	pUnpacking	解包器接口，包含数据包信息
	*/
	void OnReceive(NetLib::TransportID id, UINT uTo, NetLib::IUnpacking *pUnpacking);
	
	/** 
	@brief	网络成功连接
	@param id 传输器的标识符	
	*/
	void OnConnected(NetLib::TransportID id);

	/** 
	 @brief	网络故障导致连接断开
	 @param id 传输器的标识符
	*/
	void OnDisconnect(NetLib::TransportID id);
	
	/** 
	 @brief		设置回调接口
	 @param		pCallback 网络内核类的回调接口
	*/
	void SetCallback(NetLib::INetKernelCallback *pCallback) { m_cb = pCallback; }
	
	/** 
	 @brief		获取控制台线程
	 @param		控制台线程对象
	*/
	CConsoleThread* ConsoleThread() { return m_pConsoleThread; }
	
private:
	typedef std::list<NetLib::ITransport *>		TransportList;
	typedef TransportList::iterator				TransportIt;

public:
	NetLib::ITransport* FindTransport(NetLib::TransportID id);
	NetLib::ITransport* FindTransport(LPCTSTR lpName);

private:
	CConsoleThread					*m_pConsoleThread;	//!< 控制台线程
	NetLib::INetKernelCallback		*m_cb;				//!< 回调接口
	NetLib::IEndPointMgr			*m_pEndPointMgr;	//!< 终端管理器接口
	TransportList					m_transports;		//!< 传输器接口
};

#endif