#ifndef _I_NET_KERNEL_CALLBACK_H_
#define _I_NET_KERNEL_CALLBACK_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file INetKernelCallback.h
* @brief 网络内核接口的回调接口
*  
* 主要向逻辑层发布网络断开的通知
*
* @version 1.0
* @author  汤军
* @date    2010年8月10日
*  
*  
* 修订说明：最初版本  
*/

namespace NetLib
{
	/** 
	*@brief 网络层的回调接口
	*/
	class INetKernelCallback
	{
	public:
		/** 
		*@brief	成功连接到仪器
		*@return 无返回值
		*/
		virtual void OnConnected() = 0;

		/** 
		*@brief	与仪器的连接断开
		*@return 无返回值
		*/
		virtual void OnShutdown() = 0;
		
		/** 
		*@brief	成功连接到远端协助服务器
		*@return 无返回值
		*/
		virtual void OnRemoteConnected() = 0;

		/** 
		*@brief	远端协助断开
		*@return 无返回值
		*/
		virtual void OnRemoteShutdown() = 0;

		/** 
		*@brief	远端协助的服务被关闭
		*@return 无返回值
		*/
		virtual void OnRemoteServerShutdown() = 0;
	};
}
#endif