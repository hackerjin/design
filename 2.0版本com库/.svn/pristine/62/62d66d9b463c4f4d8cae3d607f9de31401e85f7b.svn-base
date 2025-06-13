#ifndef _I_TRANSPONDER_H_
#define _I_TRANSPONDER_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file ICapability.h
* @brief 转发器接口
*  
* 转发器主要职责：终端数据源、发送终端数据
*
* @version 1.0
* @author  汤军
* @date    2010年8月3日
*  
*  
* 修订说明：最初版本  
*/

#include "IPacking.h"
#include "ITransport.h"
#include "IEndPoint.h"

namespace NetLib
{
	/**
	*@brief 传输通道管理器
	*/
	class ITransponder
	{
	public:
		/**
		*@brief 增添传输器
		*@param	pTransport	传输器接口
		*@return 无返回值
		*/
		virtual void Add(ITransport *pTransport) = 0;
		
		/**
		*@brief 移除传输器
		*@param	id	传输器标识符
		*@return 无返回值
		*/
		virtual void Remove(TransportID id) = 0;
		
		/** 
		*@brief	移除所有传输器
		*@return 无返回值
		*/
		virtual void RemoveAll() = 0;

		/**
		*@brief	发送数据
		*@param  id			发送数据应该使用的传输器的标识符
		*@param  uTo		接收数据的终端标识符
		*@param	 pPacking	封包器接口(包含待发的数据）
		*@return
		*- TRUE 发送成功（仅仅是发送数据进入了发送队列，不保证数据一定到达客户端）
		*- FALSE 发送失败
		*/
		virtual BOOL Send(TransportID id, UINT uTo, IPacking *pPacking) = 0;
	};
}

#endif