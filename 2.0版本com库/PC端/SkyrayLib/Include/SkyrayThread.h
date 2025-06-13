#ifndef _SKYRAY_THREAD_H_
#define _SKYRAY_THREAD_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file Thread.h
* @brief �ṩ���̵߳ļ򵥷�װ
*  
* ���̵߳Ĵ������̡�
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
	*@brief �߳� ��Ҫ���ڼ򻯿��̵߳ĸ��Ӷȡ�
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
		*@brief	�����߳�
		*@return	
		*- TRUE	�߳̿����ɹ�
		*- FALSE	�߳̿���ʧ��
		*/
		BOOL Start();

		/**
		*@brief	�̶߳�������װ���߳��Ƿ�͵��ø÷������߳�Ϊͬһ�̡߳�
		*@return	
		*- TRUE	��
		*- FALSE	��
		*/
		BOOL IsCurrent();

		/** 
		*@brief	�̶߳�������װ���߳��Ƿ���������
		*@return	
		*- TRUE	��������
		*- FALSE	�Ѿ�ֹͣ����
		*/
		BOOL IsRuning();

		/** 
		*@brief	��ֹһ���߳�
		*@return	
		*- ERROR_SUCCESS �ɹ�
		*- ���� ʹ��GetLastError() API��ȡ�������
		*/
		DWORD Terminate();

		/** 
		*@brief	���ߵ����߳�
		*@param	msec		�߳����ߵ�ʱ��(��λ ����)
		*@return �޷���ֵ
		*/
		static void Sleep(int msec);

		/** 
		*@brief	�õ������߳�ID
		*@return �߳�ID
		*/
		static DWORD Self();

		/**
		*@brief	�߳�ִ���壬��һ�����󷽷�����������ʵ��
		*@return �̵߳ķ���ֵ
		*/
		virtual DWORD Run() = 0;

		/**
		*@brief	�߳̽�����ʱ�򱻵��õķ���, �ɾ���������������ô����
		*@return �޷���ֵ
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
