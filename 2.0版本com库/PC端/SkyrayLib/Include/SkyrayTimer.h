#ifndef _SKYRAY_TIMER_H_
#define _SKYRAY_TIMER_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file Timer.h
* @brief �ṩ�Ը߾��ȶ�ʱ���ļ򵥷�װ
*  
* �򻯸߾��ȶ�ʱ���Ĵ������̡�
*
* @version 1.0
* @author  ����
* @date    2010��8��3��
*  
*  
* �޶�˵��������汾  
*/

#include "SkyrayLib.h"

namespace Skyray
{
	/**
	*@brief �߾��ȶ�ʱ�� ��Ҫ���ڼ򻯴����߽��ȶ�ʱ���ĸ��Ӷȡ�
	*/
	class CTimer
	{
	public:
		CTimer();
		~CTimer();

		/** 
		*@brief	������ʱ��
		*@param	nElapse	��ʱ���Ķ�ʱ���(��λ ����)
		*@param	bOnce		TRUE��ʱ����Ϊһ�δ���; FALSE��ʱ����ָ���ļ���ظ�����
		*@return	
		*- TRUE		��ʱ�������ɹ�
		*- FALSE	��ʱ������ʧ��
		*/
		BOOL StartTimer(DWORD nElapse, BOOL bOnce = FALSE);	

		/** 
		*@brief	�رն�ʱ��
		*@return	�޷���ֵ
		*/
		void KillTimer();

		/** 
		*@��ʱ���Ƿ���
		*@return	
		*- TRUE		����
		*- FALSE	û�п���
		*/
		BOOL IsRun();

		/** 
		*@��ʱ��ִ���壬��һ�����󷽷�����������ʵ��
		*@return �̵߳ķ���ֵ
		*/
		virtual void TimerProc()=0;

	private:
		static void PASCAL TimerProc(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);	

	private:
		UINT			m_timerID;		//!< ��ʱ�����
	};
}

#endif