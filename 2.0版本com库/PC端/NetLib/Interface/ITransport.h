#ifndef _I_TRANSPORT_H_
#define _I_TRANSPORT_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file ITransport.h
* @brief �������ӿ�
*  
* ��Ҫְ�����ݰ��ɿ�����Ľ����뷢��
*
* @version 1.0
* @author  ����
* @date    2010��8��3��
*  
*  
* �޶�˵��������汾  
*/

#include "IPacking.h"
#include "IUnpacking.h"

namespace NetLib
{
	enum TransportID
	{
		e_remote_transport,		//!< Զ��PC
		e_apparatus_transport,	//!< ����
		e_assistance_transport,	//!< Զ��Э��������IP
	};
	
	class ITransponder;
	
	/**
	*@brief ����ͨ��
	*/
	class ITransport
	{
	public:
		/** 
		*@brief		��ȡ��������ʶ��
		*@return	��������ʶ��
		*/
		virtual TransportID ID() = 0;
		
		/** 
		*@brief		��ȡ����������
		*@return	����������
		*/
		virtual const wchar_t* Name() = 0;

		/** 
		*@brief	��������
		*@param	pIP		���ӵ�Ŀ��˵�IP��ַ
		*@param	uPort	���ӵ�Ŀ��˵Ķ˿ں�
		*@return
		*- TRUE	���ӽ����ɹ�
		*- FALSE ���ӽ���ʧ��
		*/
		virtual BOOL Connect(const wchar_t *pIP, UINT uPort) = 0;
		
		/** 
		*@brief	��������
		*@param	cType		���������ݵ�����
		*@param uTo			���������ݵ�Ŀ�ĵ�ַ
		*@param	pPacking	������ӿڣ����������͵����ݣ�
		*@return
		*- TRUE		���ͳɹ��������Ƿ������ݽ����˷��Ͷ��У�����֤����һ������ͻ��ˣ�
		*- FALSE	����ʧ��
		*/
		virtual BOOL Send(char cType, UINT uTo, IPacking *pPacking) = 0;
		
		/** 
		*@brief	�����Ƿ��Ѿ�����
		*@return
		*- TRUE	�����Ѿ�����
		*- FALSE ����δ����
		*/
		virtual BOOL IsConnected() = 0;

		/** 
		*@brief	���ٽӿ�
		*return �޷���ֵ
		*/
		virtual void Destroy() = 0;
	};
}

#endif