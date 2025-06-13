#ifndef _PACKING_H_
#define _PACKING_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file IPacking.h
* @brief 封包器
*  
* 实现封包器接口
*
* @version 1.0
* @author  汤军
* @date    2010年8月5日
*  
*  
* 修订说明：最初版本  
*/

#include "IPacking.h"

class CPacking : public NetLib::IPacking
{
public:
	CPacking();
	~CPacking();

	/** 
	 @brief		压入一个字节的数据
	 @param		nValue	待压入数据
	*/
	void Push(char nValue);
	
	/** 
	 @brief	压入二个字节的数据
	 @param		nValue	待压入数据
	*/
	void Push(short nValue);

	/** 
	 @brief	压入四个字节的数据
	 @param		nValue	待压入数据
	*/
	void Push(int nValue);

	/** 
	 @brief	压入一个字符串
	 @param		nValue	待压入字符串
	*/
	void Push(const char *pValue);
	
	/** 
	 @brief	压入一个字符串
	 @param		nValue	待压入字符串
	*/
	void Push(const wchar_t *pValue);

	/** 
	 @brief	压入一串二进制数
	 @param		pData	待压入二进制串的首地址
	 @param		uDataLen二进制串的长度
	*/
	void Push(const char *pData, UINT uDataLen);

	/** 
	 @brief	获取序列化后的缓冲区的首地址
	 @return	缓冲区首地址
	*/
	const char* Buffer() { return m_pBuffer; }

	/** 
	 @brief	获取序列化后的缓冲区的长度
	 @return	缓冲区长度
	*/
	UINT BufferLen() { return m_nBufferIndex; }

	/** 
	 @brief	销毁接口
	*/
	void Destroy() { delete this; }

private:
	static const UINT m_uDefaultBufferSize = 512;

private:
	void AddData(const char *pData, UINT uDataLen);

private:
	char	m_acDefaultBuffer[m_uDefaultBufferSize];

	char	*m_pBuffer;
	UINT	m_nBufferIndex;
	UINT	m_nBufferSize;
};

#endif