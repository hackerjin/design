#ifndef _I_PACKING_H_
#define _I_PACKING_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file IPacking.h
* @brief 封包器接口
*  
* 主要方便数据包的建立过程。将数据序列化到缓冲区。隐藏字节顺序 字符编码等细节
*
* @version 1.0
* @author  汤军
* @date    2010年8月5日
*  
*  
* 修订说明：最初版本  
*/

namespace NetLib
{
	/** 
	*@brief	数据序列化接口
	*/
	class IPacking
	{
	public:
		/** 
		*@brief	压入一个字节的数据
		*@param	nValue	待压入数据
		*@return 无返回值
		*/
		virtual void Push(char nValue) = 0;
		
		/** 
		*@brief	压入二个字节的数据
		*@param	nValue	待压入数据
		*@return 无返回值
		*/
		virtual void Push(short nValue) = 0;

		/** 
		*@brief	压入四个字节的数据
		*@param	nValue	待压入数据
		*@return 无返回值
		*/
		virtual void Push(int nValue) = 0;

		/** 
		*@brief	压入一个字符串
		*@param	nValue	待压入字符串
		*@return 无返回值
		*/
		virtual void Push(const char *pValue) = 0;
		
		/** 
		*@brief	压入一个字符串
		*@param	nValue	待压入字符串
		*@return 无返回值
		*/
		virtual void Push(const wchar_t *pValue) = 0;

		/** 
		*@brief	压入一串二进制数
		*@param	pData	待压入二进制串的首地址
		*@param	uDataLen二进制串的长度
		*@return 无返回值
		*/
		virtual void Push(const char *pData, UINT uDataLen) = 0;

		/** 
		*@brief 获取序列化后的缓冲区的首地址
		*@return 缓冲区首地址
		*@return 无返回值
		*/
		virtual const char* Buffer() = 0;

		/** 
		*@brief	获取序列化后的缓冲区的长度
		*@return 缓冲区长度
		*/
		virtual UINT BufferLen() = 0;

		/** 
		*@brief	销毁接口
		*/
		virtual void Destroy() = 0;
	};
}

#endif