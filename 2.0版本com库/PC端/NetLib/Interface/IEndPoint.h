#ifndef _I_ENDPOINT_H_
#define _I_ENDPOINT_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file IEndPoint.h
* @brief 终端接口
*  
* 所谓终端就是被命名的，可以反序列化网络数据到指定应用的模块
*
* @version 1.0
* @author  汤军
* @date    2010年8月3日
*  
*  
* 修订说明：最初版本  
*/

#include "IUnpacking.h"
#include "ITransport.h"

namespace NetLib
{
	/** 
	*@brief 终端接口定义
	*/
	class IEndPoint
	{
	public:
		/** 
		*@brief	能力的标识符
		*@return	标识符
		*/
		virtual UINT ID() = 0;

		/** 
		*@brief	获取能力的名称
		*@return	能力名称
		*/
		virtual const wchar_t* Name() = 0;
		
		/** 
		*@brief	使用远程协助的情况下，是否需要把发送给该终端的数据中继给下位机
		*@return	
		*- TRUE 需要 
		*- FALSE 不需要
		*/
		virtual BOOL IsRelay() = 0;

		/** 
		*@brief	接收到一个数据包
		*@param eID			数据包是从标识符为eID的传输器上获取
		*@param	pUnpacking	解包器接口，包含数据包信息
		*/
		virtual void OnReceive(TransportID eID, IUnpacking *pUnpacking) = 0;
		
		/** 
		*@brief		得到最近的出错信息
		*@return	出错信息
		*/
		virtual const wchar_t* GetLastError() = 0;
		
		/** 
		*@brief	销毁接口
		*/
		virtual void Destroy() = 0;
	};
}

#endif