#ifndef _I_ENDPOINT_MGR_H_
#define _I_ENDPOINT_MGR_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file IEndPointMgr.h
* @brief 终端管理器接口
*  
* 主要职责：管理终端接口
*
* @version 1.0
* @author  汤军
* @date    2010年8月3日
*  
*  
* 修订说明：最初版本  
*/

#include "IEndPoint.h"

namespace NetLib
{
	/** 
	*@brief 终端管理器
	*/
	class IEndPointMgr
	{
	public:
		/** 
		*@brief	添加一个终端
		*@param	pEndPoint 终端接口
		*@return	
		*- TRUE		添加终端成功
		*- FALSE	添加终端失败
		*/
		virtual BOOL Add(IEndPoint *pEndPoint) = 0;
		
		/** 
		*@brief	查找终端
		*@param	uID		终端描述符
		*@return	
		*- NULL	指定终端不存在
		*- 其他	终端接口
		*/
		virtual IEndPoint* Find(UINT uID) = 0; 
		
		/** 
		*@brief	移除终端
		*@param	uID		终端描述符
		*@return 无返回值
		*
		*/
		virtual void Remove(UINT uID) = 0;

		/** 
		*@brief	清空终端管理器
		*@return 无返回值
		*/
		virtual void Clear() = 0;
	};
}

#endif