#ifndef _I_UNPACKING_H_
#define _I_UNPACKING_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file IUnpacking.h
* @brief ������ӿ�
*  
* ��Ҫ����ӻ������л�ȡ���� �����ֽ�˳�� �ַ������ϸ��
*
* @version 1.0
* @author  ����
* @date    2010��8��5��
*  
*  
* �޶�˵��������汾  
*/

#include "IPacking.h"

namespace NetLib
{
	/** 
	*@brief	���ݷ����л��ӿ�
	*/
	class IUnpacking
	{
	public:
		/** 
		*@brief		����һ�ֽڵ�����
		*@param		nValue ���浯��������
		*@return	
		*- TRUE �ɹ�
		*- FALSE ʧ��
		*/
		virtual BOOL Pop(char &nValue) = 0;
		
		/** 
		*@brief		�������ֽڵ�����
		*@param		nValue ���浯��������
		*@return	
		*- TRUE �ɹ�
		*- FALSE ʧ��
		*/
		virtual BOOL Pop(short &nValue) = 0;
		
		/** 
		*@brief		�������ֽڵ�����
		*@param		nValue ���浯��������
		*@return	
		*- TRUE �ɹ�
		*- FALSE ʧ��
		*/
		virtual BOOL Pop(int &nValue) = 0;
	
		
		/** 
		*@brief		����һ���ַ���
		*@param		pString ���浯�����ַ��������Ϊ�գ���ʾͨ��nLen����ȡ��Ҫ�Ļ������Ĵ�С
		*@param		nLen ��Ϊ�������ָʾpString�Ĵ�С����Ϊ�������pString�б������Ч���ݵĳ���
		*@return	
		*- TRUE �ɹ�
		*- FALSE ʧ��
		*/
		virtual BOOL Pop(char *pString, UINT &nLen) = 0;
		
		/** 
		*@brief		����һ���ַ���
		*@param		pString ���浯�����ַ��������Ϊ�գ���ʾͨ��nLen����ȡ��Ҫ�Ļ������Ĵ�С
		*@param		nLen ��Ϊ�������ָʾpString�Ĵ�С����Ϊ�������pString�б������Ч���ݵĳ���
		*@return	
		*- TRUE �ɹ�
		*- FALSE ʧ��
		*/
		virtual BOOL Pop(wchar_t *pString, UINT &nLen) = 0;

		/** 
		*@brief		����һ�������ƴ�
		*@param		pData ���浯���Ķ����ƴ�
		*@param		ϣ�������Ķ����ƴ��ĳ���
		*@return	
		*- TRUE �ɹ�
		*- FALSE ʧ��
		*/
		virtual BOOL PopBuffer(char *pData, UINT nDataLen) = 0;
		
		/** 
		*@brief		��ȡ���ݰ��Ĵ�С
		*@return	���ݰ���С
		*/
		virtual UINT Size() = 0;

		/** 
		*@brief		�ɽ�����ӿ�ת����һ��������ӿ�
		*@return	������ӿ�
		*/
		virtual IPacking* CreatePacking() = 0;

		/** 
		*@brief	
		*@return �޷���ֵ
		*/
		virtual void Destroy() = 0;
	};
}

#endif