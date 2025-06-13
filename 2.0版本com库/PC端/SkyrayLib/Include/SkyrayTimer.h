#ifndef _SKYRAY_TIMER_H_
#define _SKYRAY_TIMER_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file Timer.h
* @brief 提供对高精度定时器的简单封装
*  
* 简化高精度定时器的创建过程。
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
	*@brief 高精度定时器 主要用于简化创建高进度定时器的复杂度。
	*/
	class CTimer
	{
	public:
		CTimer();
		~CTimer();

		/** 
		*@brief	开启定时器
		*@param	nElapse	定时器的定时间隔(单位 毫秒)
		*@param	bOnce		TRUE定时器是为一次触发; FALSE定时器按指定的间隔重复触发
		*@return	
		*- TRUE		定时器创建成功
		*- FALSE	定时器创建失败
		*/
		BOOL StartTimer(DWORD nElapse, BOOL bOnce = FALSE);	

		/** 
		*@brief	关闭定时器
		*@return	无返回值
		*/
		void KillTimer();

		/** 
		*@定时器是否开启
		*@return	
		*- TRUE		开启
		*- FALSE	没有开启
		*/
		BOOL IsRun();

		/** 
		*@定时器执行体，是一个抽象方法，由派生类实现
		*@return 线程的返回值
		*/
		virtual void TimerProc()=0;

	private:
		static void PASCAL TimerProc(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);	

	private:
		UINT			m_timerID;		//!< 定时器编号
	};
}

#endif