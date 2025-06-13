#ifndef _SKYRAY_THREAD_H_
#define _SKYRAY_THREAD_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file Thread.h
* @brief 提供对线程的简单封装
*  
* 简化线程的创建过程。
*
* @version 1.0
* @author  汤军
* @date    2010年8月3日
*  
*  
* 修订说明：最初版本  
*/

#include "SkyrayLib.h"

namespace Skyray
{
	/**
	*@brief 线程 主要用于简化开线程的复杂度。
	*/
	class CThread
	{
	public:
		CThread();
		virtual ~CThread();

	public:
		HANDLE		m_hThread;

	public:
		/**
		*@brief	开启线程
		*@return	
		*- TRUE	线程开启成功
		*- FALSE	线程开启失败
		*/
		BOOL Start();

		/**
		*@brief	线程对象所封装的线程是否和调用该方法的线程为同一线程。
		*@return	
		*- TRUE	是
		*- FALSE	否
		*/
		BOOL IsCurrent();

		/** 
		*@brief	线程对象所封装的线程是否在运行中
		*@return	
		*- TRUE	在运行中
		*- FALSE	已经停止运行
		*/
		BOOL IsRuning();

		/** 
		*@brief	终止一个线程
		*@return	
		*- ERROR_SUCCESS 成功
		*- 其他 使用GetLastError() API获取出错代码
		*/
		DWORD Terminate();

		/** 
		*@brief	休眠调用线程
		*@param	msec		线程休眠的时间(单位 毫秒)
		*@return 无返回值
		*/
		static void Sleep(int msec);

		/** 
		*@brief	得到调用线程ID
		*@return 线程ID
		*/
		static DWORD Self();

		/**
		*@brief	线程执行体，是一个抽象方法，由派生类实现
		*@return 线程的返回值
		*/
		virtual DWORD Run() = 0;

		/**
		*@brief	线程结束的时候被调用的方法, 由具体的派生类决定怎么处理
		*@return 无返回值
		*/
		virtual void OnTerminate(){}
	
	private:
		typedef unsigned (__stdcall *PTHREAD_START) (void *);

	private:
		friend DWORD __stdcall Runner(void* arg);

	private:
		DWORD 		m_dwThreadID;
	};
}

#endif 
