#ifndef _UNPACKING_H_
#define _UNPACKING_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file IUnpacking.h
* @brief �����
*  
* ʵ�ֽ�����ӿ�
*
* @version 1.0
* @author  ����
* @date    2010��8��5��
*  
*  
* �޶�˵��������汾  
*/

#include "IUnpacking.h"

class CUnpacking : public NetLib::IUnpacking
{
public:
	CUnpacking(const char *pData, UINT nDataLen);
	~CUnpacking();

	/** 
	 @brief		����һ�ֽڵ�����
	 @param		nValue ���浯��������
	 @return	TRUE �ɹ���FALSE ʧ��
	*/
	BOOL Pop(char &nValue);

	/** 
	 @brief		�������ֽڵ�����
	 @param		nValue ���浯��������
	 @return	TRUE �ɹ���FALSE ʧ��
	*/
	BOOL Pop(short &nValue);

	/** 
	 @brief		�������ֽڵ�����
	 @param		nValue ���浯��������
	 @return	TRUE �ɹ���FALSE ʧ��
	*/
	BOOL Pop(int &nValue);


	/** 
	 @brief		����һ���ַ���
	 @param		pString ���浯�����ַ��������Ϊ�գ���ʾͨ��nLen����ȡ��Ҫ�Ļ������Ĵ�С
	 @param		nLen ��Ϊ�������ָʾpString�Ĵ�С����Ϊ�������pString�б������Ч���ݵĳ���
	 @return	TRUE �ɹ���FALSE ʧ��
	*/
	BOOL Pop(char *pString, UINT &nLen);
	
	/** 
	 @brief		����һ���ַ���
	 @param		pString ���浯�����ַ��������Ϊ�գ���ʾͨ��nLen����ȡ��Ҫ�Ļ������Ĵ�С
	 @param		nLen ��Ϊ�������ָʾpString�Ĵ�С����Ϊ�������pString�б������Ч���ݵĳ���
	 @return	TRUE �ɹ���FALSE ʧ��
	*/
	BOOL Pop(wchar_t *pString, UINT &nLen);

	/** 
	 @brief		����һ�������ƴ�
	 @param		pData ���浯���Ķ����ƴ�
	 @param		ϣ�������Ķ����ƴ��ĳ���
	 @return	TRUE �ɹ���FALSE ʧ��
	*/
	BOOL PopBuffer(char *pData, UINT nDataLen);
	
	/** 
	 @brief		��ȡ���ݰ��Ĵ�С
	 @return	���ݰ���С
	*/
	UINT Size() { return m_nBufferSize; }

	/** 
	@brief		�ɽ�����ӿ�ת����һ��������ӿ�
	@return	������ӿ�
	*/
	NetLib::IPacking* CreatePacking();

	/** 
	 @brief	
	*/
	void Destroy() { delete this; }

private:
	char			*m_pBuffer;
	UINT			m_nBufferSize;
	UINT			m_nBufferIndex;
};

#endif