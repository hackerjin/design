#ifndef _I_PACKING_H_
#define _I_PACKING_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file IPacking.h
* @brief ������ӿ�
*  
* ��Ҫ�������ݰ��Ľ������̡����������л����������������ֽ�˳�� �ַ������ϸ��
*
* @version 1.0
* @author  ����
* @date    2010��8��5��
*  
*  
* �޶�˵��������汾  
*/

namespace NetLib
{
	/** 
	*@brief	�������л��ӿ�
	*/
	class IPacking
	{
	public:
		/** 
		*@brief	ѹ��һ���ֽڵ�����
		*@param	nValue	��ѹ������
		*@return �޷���ֵ
		*/
		virtual void Push(char nValue) = 0;
		
		/** 
		*@brief	ѹ������ֽڵ�����
		*@param	nValue	��ѹ������
		*@return �޷���ֵ
		*/
		virtual void Push(short nValue) = 0;

		/** 
		*@brief	ѹ���ĸ��ֽڵ�����
		*@param	nValue	��ѹ������
		*@return �޷���ֵ
		*/
		virtual void Push(int nValue) = 0;

		/** 
		*@brief	ѹ��һ���ַ���
		*@param	nValue	��ѹ���ַ���
		*@return �޷���ֵ
		*/
		virtual void Push(const char *pValue) = 0;
		
		/** 
		*@brief	ѹ��һ���ַ���
		*@param	nValue	��ѹ���ַ���
		*@return �޷���ֵ
		*/
		virtual void Push(const wchar_t *pValue) = 0;

		/** 
		*@brief	ѹ��һ����������
		*@param	pData	��ѹ������ƴ����׵�ַ
		*@param	uDataLen�����ƴ��ĳ���
		*@return �޷���ֵ
		*/
		virtual void Push(const char *pData, UINT uDataLen) = 0;

		/** 
		*@brief ��ȡ���л���Ļ��������׵�ַ
		*@return �������׵�ַ
		*@return �޷���ֵ
		*/
		virtual const char* Buffer() = 0;

		/** 
		*@brief	��ȡ���л���Ļ������ĳ���
		*@return ����������
		*/
		virtual UINT BufferLen() = 0;

		/** 
		*@brief	���ٽӿ�
		*/
		virtual void Destroy() = 0;
	};
}

#endif