#ifndef _I_ENDPOINT_H_
#define _I_ENDPOINT_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file IEndPoint.h
* @brief �ն˽ӿ�
*  
* ��ν�ն˾��Ǳ������ģ����Է����л��������ݵ�ָ��Ӧ�õ�ģ��
*
* @version 1.0
* @author  ����
* @date    2010��8��3��
*  
*  
* �޶�˵��������汾  
*/

#include "IUnpacking.h"
#include "ITransport.h"

namespace NetLib
{
	/** 
	*@brief �ն˽ӿڶ���
	*/
	class IEndPoint
	{
	public:
		/** 
		*@brief	�����ı�ʶ��
		*@return	��ʶ��
		*/
		virtual UINT ID() = 0;

		/** 
		*@brief	��ȡ����������
		*@return	��������
		*/
		virtual const wchar_t* Name() = 0;
		
		/** 
		*@brief	ʹ��Զ��Э��������£��Ƿ���Ҫ�ѷ��͸����ն˵������м̸���λ��
		*@return	
		*- TRUE ��Ҫ 
		*- FALSE ����Ҫ
		*/
		virtual BOOL IsRelay() = 0;

		/** 
		*@brief	���յ�һ�����ݰ�
		*@param eID			���ݰ��Ǵӱ�ʶ��ΪeID�Ĵ������ϻ�ȡ
		*@param	pUnpacking	������ӿڣ��������ݰ���Ϣ
		*/
		virtual void OnReceive(TransportID eID, IUnpacking *pUnpacking) = 0;
		
		/** 
		*@brief		�õ�����ĳ�����Ϣ
		*@return	������Ϣ
		*/
		virtual const wchar_t* GetLastError() = 0;
		
		/** 
		*@brief	���ٽӿ�
		*/
		virtual void Destroy() = 0;
	};
}

#endif