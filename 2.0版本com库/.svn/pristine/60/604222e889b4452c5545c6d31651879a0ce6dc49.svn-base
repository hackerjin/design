#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file ITransport.h
* @brief 传输器
*  
* 主要职责：实现传输器接口
*
* @version 1.0
* @author  汤军
* @date    2010年8月4日
*  
*  
* 修订说明：最初版本  
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
	 @brief		获取传输器标识符
	 @return	传输器标识符
	*/
	NetLib::TransportID ID() { return m_id; }
	
	/** 
	@brief		获取传输器名称
	@return		传输器名称
	*/
	const TCHAR* Name() { return m_name.c_str(); }

	/** 
	 @brief	建立连接
	 @param	pIP		连接的目标端的IP地址
	 @param	uPort	连接的目标端的端口号
	 @return	== TRUE	连接建立成功
				== FALSE	连接建立失败
	*/
	BOOL Connect(const wchar_t *pIP, UINT uPort);
	
	/** 
	 @brief	发送数据
	 @param	cType		待发送数据的类型
	 @param uTo			待发送数据的目的地址
	 @param	pPacking	封包器接口（包含待发送的数据）
	 @return	== TRUE		发送成功（仅仅是发送数据进入了发送队列，不保证数据一定到达客户端）
				== FALSE	发送失败
	*/
	BOOL Send(char cType, UINT uTo, NetLib::IPacking *pPacking);
	
	/** 
	@brief	连接是否已经建立
	@return == TRUE	连接已经建立
	== FALSE	连接未建立
	*/
	BOOL IsConnected() { return m_bContented; }

	/** 
	 @brief	销毁接口
	*/
	void Destroy() { delete this; }
	
	/** 
	 @brief	接收到一个数据包
	 @param uTo			数据包的目的地址
	 @param	pUnpacking	解包器接口，包含数据包信息
	*/
	void OnReceive(UINT uTo, NetLib::IUnpacking *pUnpacking);

	/** 
	 @brief	网络故障导致连接断开
	*/
	void OnDisconnect();
	
	/** 
	@定时器执行体，是一个抽象方法，由派生类实现
	@Return	线程的返回值
	*/
	void TimerProc();

private:
	DWORD Run();

private:
	NetLib::TransportID				m_id;				//!< 传输通道标识符
	tstring							m_name;				//!< 传输通道的名字
	CTransponder					*m_pTransponder;	//!< 传输通道管理器
	std::wstring					m_strIP;			//!< 传输通道目的地的地址
	UINT							m_uPort;			//!< 传输通道目的地的端口
	Skyray::CSocket					m_socket;			//!< 传输所用套接字
	BOOL							m_bContented;		//!< 连接是否建立
	CSendThread						*m_pSendThread;		//!< 数据发送线程
	CRecvThread						*m_pRecvThread;		//!< 数据接收线程
};

#endif