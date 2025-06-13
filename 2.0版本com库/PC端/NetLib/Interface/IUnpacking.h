#ifndef _I_UNPACKING_H_
#define _I_UNPACKING_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file IUnpacking.h
* @brief 解包器接口
*  
* 主要方便从缓冲区中获取数据 隐藏字节顺序 字符编码等细节
*
* @version 1.0
* @author  汤军
* @date    2010年8月5日
*  
*  
* 修订说明：最初版本  
*/

#include "IPacking.h"

namespace NetLib
{
	/** 
	*@brief	数据反序列化接口
	*/
	class IUnpacking
	{
	public:
		/** 
		*@brief		弹出一字节的数据
		*@param		nValue 保存弹出的数据
		*@return	
		*- TRUE 成功
		*- FALSE 失败
		*/
		virtual BOOL Pop(char &nValue) = 0;
		
		/** 
		*@brief		弹出二字节的数据
		*@param		nValue 保存弹出的数据
		*@return	
		*- TRUE 成功
		*- FALSE 失败
		*/
		virtual BOOL Pop(short &nValue) = 0;
		
		/** 
		*@brief		弹出四字节的数据
		*@param		nValue 保存弹出的数据
		*@return	
		*- TRUE 成功
		*- FALSE 失败
		*/
		virtual BOOL Pop(int &nValue) = 0;
	
		
		/** 
		*@brief		弹出一个字符串
		*@param		pString 保存弹出的字符串，如果为空，表示通过nLen来获取需要的缓冲区的大小
		*@param		nLen 作为输入参数指示pString的大小，作为输出参数pString中保存的有效数据的长度
		*@return	
		*- TRUE 成功
		*- FALSE 失败
		*/
		virtual BOOL Pop(char *pString, UINT &nLen) = 0;
		
		/** 
		*@brief		弹出一个字符串
		*@param		pString 保存弹出的字符串，如果为空，表示通过nLen来获取需要的缓冲区的大小
		*@param		nLen 作为输入参数指示pString的大小，作为输出参数pString中保存的有效数据的长度
		*@return	
		*- TRUE 成功
		*- FALSE 失败
		*/
		virtual BOOL Pop(wchar_t *pString, UINT &nLen) = 0;

		/** 
		*@brief		弹出一个二进制串
		*@param		pData 保存弹出的二进制串
		*@param		希望弹出的二进制串的长度
		*@return	
		*- TRUE 成功
		*- FALSE 失败
		*/
		virtual BOOL PopBuffer(char *pData, UINT nDataLen) = 0;
		
		/** 
		*@brief		获取数据包的大小
		*@return	数据包大小
		*/
		virtual UINT Size() = 0;

		/** 
		*@brief		由解包器接口转换成一个封包器接口
		*@return	封包器接口
		*/
		virtual IPacking* CreatePacking() = 0;

		/** 
		*@brief	
		*@return 无返回值
		*/
		virtual void Destroy() = 0;
	};
}

#endif