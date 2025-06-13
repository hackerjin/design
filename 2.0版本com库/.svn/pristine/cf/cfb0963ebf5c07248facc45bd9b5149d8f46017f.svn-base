/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file SkyrayLock.h
* @brief 提供关键代码锁的封装
*  
* 简单封装关键代码锁，以方便使用。
*
* @version 1.0
* @author  汤军
* @date    2010年8月2日
*  
*  
* 修订说明：最初版本  
*/
#ifndef _SKYRAY_LOCK_H_
#define _SKYRAY_LOCK_H_

#include "SkyrayLib.h"

/** 
@brief 定义了一组常用模块
*- 字符串编码处理
*- 套接字
*- 线程
*- 高精度定时器
*- 关键代码锁
*/
namespace Skyray
{
	/**
	@brief 代码锁 简化关键代码锁的使用复杂度。
	*/
	class CLock
	{
	public:
		CLock() { InitializeCriticalSection(&m_cs); }
		~CLock() { DeleteCriticalSection(&m_cs); }
		
		/**
		*@brief	加锁
		*@return 无返回值
		*/
		void Lock() { EnterCriticalSection(&m_cs); }
		
		/**
		*@brief	解锁
		*@return 无返回值	
		*/
		void Unlock() { LeaveCriticalSection(&m_cs); }

	private:
		CRITICAL_SECTION	m_cs;
	};
}

#endif