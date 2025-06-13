#ifndef _I_TRANSPONDER_H_
#define _I_TRANSPONDER_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file ICapability.h
* @brief ת�����ӿ�
*  
* ת������Ҫְ���ն�����Դ�������ն�����
*
* @version 1.0
* @author  ����
* @date    2010��8��3��
*  
*  
* �޶�˵��������汾  
*/

#include "IPacking.h"
#include "ITransport.h"
#include "IEndPoint.h"

namespace NetLib
{
	/**
	*@brief ����ͨ��������
	*/
	class ITransponder
	{
	public:
		/**
		*@brief ��������
		*@param	pTransport	�������ӿ�
		*@return �޷���ֵ
		*/
		virtual void Add(ITransport *pTransport) = 0;
		
		/**
		*@brief �Ƴ�������
		*@param	id	��������ʶ��
		*@return �޷���ֵ
		*/
		virtual void Remove(TransportID id) = 0;
		
		/** 
		*@brief	�Ƴ����д�����
		*@return �޷���ֵ
		*/
		virtual void RemoveAll() = 0;

		/**
		*@brief	��������
		*@param  id			��������Ӧ��ʹ�õĴ������ı�ʶ��
		*@param  uTo		�������ݵ��ն˱�ʶ��
		*@param	 pPacking	������ӿ�(�������������ݣ�
		*@return
		*- TRUE ���ͳɹ��������Ƿ������ݽ����˷��Ͷ��У�����֤����һ������ͻ��ˣ�
		*- FALSE ����ʧ��
		*/
		virtual BOOL Send(TransportID id, UINT uTo, IPacking *pPacking) = 0;
	};
}

#endif