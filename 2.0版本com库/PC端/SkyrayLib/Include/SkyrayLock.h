/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file SkyrayLock.h
* @brief �ṩ�ؼ��������ķ�װ
*  
* �򵥷�װ�ؼ����������Է���ʹ�á�
*
* @version 1.0
* @author  ����
* @date    2010��8��2��
*  
*  
* �޶�˵��������汾  
*/
#ifndef _SKYRAY_LOCK_H_
#define _SKYRAY_LOCK_H_

#include "SkyrayLib.h"

/** 
@brief ������һ�鳣��ģ��
*- �ַ������봦��
*- �׽���
*- �߳�
*- �߾��ȶ�ʱ��
*- �ؼ�������
*/
namespace Skyray
{
	/**
	@brief ������ �򻯹ؼ���������ʹ�ø��Ӷȡ�
	*/
	class CLock
	{
	public:
		CLock() { InitializeCriticalSection(&m_cs); }
		~CLock() { DeleteCriticalSection(&m_cs); }
		
		/**
		*@brief	����
		*@return �޷���ֵ
		*/
		void Lock() { EnterCriticalSection(&m_cs); }
		
		/**
		*@brief	����
		*@return �޷���ֵ	
		*/
		void Unlock() { LeaveCriticalSection(&m_cs); }

	private:
		CRITICAL_SECTION	m_cs;
	};
}

#endif