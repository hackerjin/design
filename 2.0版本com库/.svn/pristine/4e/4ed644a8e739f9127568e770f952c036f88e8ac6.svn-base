#ifndef _I_TRANSPORT_H_
#define _I_TRANSPORT_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file ITransport.h
* @brief 传输器接口
*  
* 主要职责：数据包可靠有序的接收与发送
*
* @version 1.0
* @author  汤军
* @date    2010年8月3日
*  
*  
* 修订说明：最初版本  
*/

#include "IPacking.h"
#include "IUnpacking.h"

namespace NetLib
{
	enum TransportID
	{
		e_remote_transport,		//!< 远端PC
		e_apparatus_transport,	//!< 仪器
		e_assistance_transport,	//!< 远程协助的请求IP
	};
	
	class ITransponder;
	
	/**
	*@brief 传输通道
	*/
	class ITransport
	{
	public:
		/** 
		*@brief		获取传输器标识符
		*@return	传输器标识符
		*/
		virtual TransportID ID() = 0;
		
		/** 
		*@brief		获取传输器名称
		*@return	传输器名称
		*/
		virtual const wchar_t* Name() = 0;

		/** 
		*@brief	建立连接
		*@param	pIP		连接的目标端的IP地址
		*@param	uPort	连接的目标端的端口号
		*@return
		*- TRUE	连接建立成功
		*- FALSE 连接建立失败
		*/
		virtual BOOL Connect(const wchar_t *pIP, UINT uPort) = 0;
		
		/** 
		*@brief	发送数据
		*@param	cType		待发送数据的类型
		*@param uTo			待发送数据的目的地址
		*@param	pPacking	封包器接口（包含待发送的数据）
		*@return
		*- TRUE		发送成功（仅仅是发送数据进入了发送队列，不保证数据一定到达客户端）
		*- FALSE	发送失败
		*/
		virtual BOOL Send(char cType, UINT uTo, IPacking *pPacking) = 0;
		
		/** 
		*@brief	连接是否已经建立
		*@return
		*- TRUE	连接已经建立
		*- FALSE 连接未建立
		*/
		virtual BOOL IsConnected() = 0;

		/** 
		*@brief	销毁接口
		*return 无返回值
		*/
		virtual void Destroy() = 0;
	};
}

#endif