#ifndef _I_NET_KERNEL_H_
#define _I_NET_KERNEL_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file INetKernel.h
* @brief �����ں˽ӿ�
*  
* ����ͨѶģ������Ľӿڣ����ӿ��Ǹ�����,��ҪΪ�˼�����ģ���ʹ��
*
* @version 1.0
* @author  ����
* @date    2010��8��3��
*  
* �޶�˵��������汾  
*/

#include "INetKernelCallback.h"
#include "ITransponder.h"
#include "IEndPointMgr.h"
#include "IPacking.h"

/** @mainpage ͨ������ͨѶϵͳ
*@section ����
*    ͨ������ͨѶϵͳPC����ʾ�����Ҫ�����紫��㡢Ӧ���߼��㡢UI��������ɡ���������ͨѶ�㸺���ṩ�ɿ������ն˵��ն�
*�����ݴ��书�ܣ�Ӧ���߼�����ݾ����Ӧ�����ն�Ϊ��������֯����Ӧ�õ����ݣ�UI����Ҫ�����û������Լ��Բ��Թ��̻�����
*�����������Ժ�����ϵͳ���������õ����㷨�����ɶ���ģ�飬���߼���������ʩ���ṩ����Դ�����UI��͸����
*@section ���紫���
*- ��Ҫְ���ṩһ���ɿ������ն˵��ն˵����ݴ��书�ܡ����ն˵�λ�ò����С�
*- ��Ҫ��ģ�顣
*	-# �նˣ���Ҫ����ͨ�õ��߼���������Ľ����ӿڣ��Ǹ������࣬���߼���ʵ�֣�����������������ӿڡ�
*	-# �ն˹��������ṩ�ն˽ӿڵĹ����ܣ���ӡ�ɾ�������ҡ�
*	-# ���������ṩ��ʵ�����ݴ���������������л��ͷ����л��ӿڵķ�ʽ���ݡ�
*	-# ������������ṩ�Դ������ӿڵĹ����ܣ���ӡ�ɾ�������ҡ�
*	-# ����̨���ṩһ�����Ե��ֶΣ�������ʾ��ǰ���ͺͽ��ܵ����ݰ������Ա༭�������ݰ���
*	-# �ܿ�ģ�飺�����Ǹ����壬�ṩ���ն˹�����������������������ڵ�ά���������������ӵĽ�����Ͽ����ṩ�����ն˹������ķ�����
*- ������ṩͨ�õ��������л��뷴���л��Ľӿڣ��Է����߼�����������ݵĴ��������
*- �������߼���ķ�����Ҫͨ�����߼���ʵ������㶨��Ļص��ӿ������С�
*@section Ӧ���߼���
*- ��Ҫְ��ʵ�������߼�����ն˽ӿڡ����л�������Լ��߼���Ķ��̻߳����µĻص���ʹ�乤����UI����̻߳����¡�
*- ��Ҫ��ģ��
*	-# �նˣ���Ҫʵ����X��ܡ�������ݲɼ���������������ȡ�
*	-# �¼��������������̻߳����µĻص����л���UI�̻߳�����ִ�С�
*- Ӧ�ò��UI��ķ�����Ҫͨ����UI��ʵ���߼��㶨��Ļص��ӿ������С�
*@section UI��
*- ��Ҫְ�𣺽����û����루���������Ԥ������չʾ��������
*- ��UI����Ҫ���ڲ��Ե�Ŀ�ģ���ֻʹ�ü򵥵Ľ���չʾ��
*@section ����ṹ
*	�����������ĸ���Ŀ���ɣ�ÿ������ʵ��һ�����档SkyrayLib��Ҫ��Щ������Ľ�ϣ�ʹ������ģ����Է����ʵ���ַ���ת�룬
*�����̣߳��߾��ȶ�ʱ�����׽��ֵȡ�NetLib��Ҫʵ�����紫��㡣XRFNet��Ҫʵ��Ӧ���߼��㡣NetWorkDemo��Ҫʵ��UI�㡣
*/

/** 
@brief ����ͨѶ��
*- �������ӽ���
*- �������л��뷴���л�
*- ��������·��
*- �ն˵Ķ���
*/
namespace NetLib
{
	/** 
	*@brief ����ͨѶ������
	*/
	class INetKernel
	{
	public:
		/** 
		*@brief		���ûص��ӿ�
		*@param		pCallback �����ں���Ļص��ӿ�
		*@return	�޷���ֵ
		*/
		virtual void SetCallback(INetKernelCallback *pCallback) = 0;

		/** 
		*@brief		����������������
		*@param		pIP		������IP��ַ		
		*@param		uPort	�����Ķ˿ں�
		*@return	
		*- TRUE		���ӳɹ� 
		*- FALSE	����ʧ��
		*/
		virtual BOOL Startup(const wchar_t *pIP, UINT uPort) = 0;
		
		/** 
		*@brief		�Ͽ�������������
		*@return	�޷���ֵ
		*/
		virtual void Shutdown() = 0;

		/** 
		*@brief		����Զ��Э��
		*@param		pIP		Զ��PC��IP��ַ		
		*@param		uPort	Զ��PC�Ķ˿ں�
		*@return	
		*- TRUE		���ӳɹ� 
		*- FALSE	����ʧ��
		*/
		virtual BOOL StartupRemote(const wchar_t *pIP, UINT uPort) = 0;
		
		/** 
		*@brief		�Ͽ�Զ��Э��
		*@return	�޷���ֵ
		*/
		virtual void ShutdownRemote() = 0;
		
		/** 
		*@brief		�����ṩԶ��Э���ķ���
		*@param		pIP		�����IP��ַ		
		*@param		uPort	����Ķ˿ں�
		*@return	
		*- TRUE		�������ɹ� 
		*- FALSE	������ʧ��
		*/
		virtual BOOL StartupRemoteServer(const wchar_t *pIP, UINT uPort) = 0;

		/** 
		*@brief		�ر�Զ��Э���ķ���
		*@return �޷���ֵ
		*/
		virtual void ShutdownRemoteServer() = 0;
		
		/** 
		*@brief		��ȡת����
		*@return	ת�����ӿ�
		*/
		virtual ITransponder* Transponder() = 0;

		/** 
		*@brief		��ȡ�ն˹�����
		*@return	�ն˹������ӿ�
		*/
		virtual IEndPointMgr* EndPointMgr() = 0;

		/** 
		*@brief		����һ���������л��ӿ�
		*@return	������ӿ�
		*/
		virtual IPacking* CreatePacking() = 0;
		
		/**
		*@brief		�򿪵��Կ���̨
		*@return �޷���ֵ
		*/
		virtual void OpenConsole() = 0;

		/**
		*@brief		�رյ��Կ���̨
		*@return �޷���ֵ
		*/
		virtual void CloseConsole() = 0;
		
		/**
		*@brief		�ڿ���̨��ӡ�ı�
		*@param	pText ��Ҫ�ڿ���̨����ʾ���ı�
		*@return �޷���ֵ
		*/
		virtual void ConsolePrint(const wchar_t *pText) = 0;
		
		/**
		*@brief		���ٽӿ�
		*@return �޷���ֵ
		*/
		virtual void Destroy() = 0;
	};
}


#ifdef NETLIB_EXPORTS
	extern "C" __declspec(dllexport) NetLib::INetKernel* CreateNetKernel();
#else
	extern "C" __declspec(dllimport) NetLib::INetKernel* CreateNetKernel();
#endif

#endif