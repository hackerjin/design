#ifndef _SKYRAY_UTIL_H_
#define _SKYRAY_UTIL_H_

#include "SkyrayLib.h"

namespace Skyray
{
	extern const std::string g_strDigitxA;	//!< 组成16进制数的字符集
	extern const std::wstring g_strDigitxU;	//!< 组成16进制数的字符集

	/** 
	*@brief 将当前字符串转换成UTF-8的格式
	*@param lpInput 等待转换的字符串
	*@param strOutPut 转换后的UTF-8字符串
	*/
	void UTF8Encode(const char *pInput, std::string &strOutput);
	
	/** 
	*@brief 将当前字符串转换成UTF-8的格式
	*@param lpInput 等待转换的字符串
	*@param strOutPut 转换后的UTF-8字符串
	*/
	void UTF8Encode(const wchar_t *pInput, std::string &strOutput);

	/** 
	*@brief 将UTF-8的格式的字符串转换成当前格式
	*@param lpInput 等待转换的字符串
	*@param strOutPut 转换后的字符串
	*/
	void UTF8Decode(const char *pInput, std::string &strOutput);
	
	/** 
	*@brief 将UTF-8的格式的字符串转换成当前格式
	*@param lpInput 等待转换的字符串
	*@param strOutPut 转换后的字符串
	*/
	void UTF8Decode(const char *pInput, std::wstring &strOutput);

	/** 
	*@brief 将Unicode格式的字符串转换成Ansi格式的字符串
	*@param pInput 等待转换的字符串
	*@param strOutPut 转换后的Ansi格式的字符串
	*/
	void Unicode2Ansi(const wchar_t *pInput, std::string &strOutput);

	/** 
	*@brief 将Ansi格式的字符串转换成Unicode格式的字符串
	*@param pInput 等待转换的字符串
	*@param strOutPut 转换后的Unicode格式的字符串
	*/
	void Ansi2Unicode(const char *pInput, std::wstring &strOutput);

	/** 
	*@brief 得到字符串表达的16进制的正整数的值
	*@param pBuffer 等待计算的字符串
	*@param nLen 字符串的长度
	*@return 返回字符串所表达的数值
	*/
	UINT GetHexValue(const char *pBuffer, int nLen);
	
	/** 
	*@brief 得到字符串表达的16进制的正整数的值
	*@param pBuffer 等待计算的字符串
	*@param nLen 字符串的长度
	*@return 返回字符串所表达的数值
	*/
	UINT GetHexValue(const wchar_t *pBuffer, int nLen);

	/** 
	*@brief 分割字符串
	*@param str 等待分割的字符串
	*@param separator 分割字符
	*@param strList 保存分割出的子字符串的列表
	*/
	void StringSplit(const std::string &str, std::string::value_type separator, std::vector<std::string> &strList);
	
	/** 
	*@brief 分割字符串
	*@param str 等待分割的字符串
	*@param separator 分割字符
	*@param strList 保存分割出的子字符串的列表
	*/
	void StringSplit(const std::wstring &str, std::wstring::value_type separator, std::vector<std::wstring> &strList);

	/** 
	*@brief 分割字符串
	*@param str 等待分割的字符串
	*@param separator 分割字符集（该字符串中所包含的字符的任意组合作为分隔符）
	*@param strList 保存分割出的子字符串的列表
	*/
	void StringSplit(const std::string &str, const std::string &separator, std::vector<std::string> &strList);
	
	/** 
	*@brief 分割字符串
	*@param str 等待分割的字符串
	*@param separator 分割字符集（该字符串中所包含的字符的任意组合作为分隔符）
	*@param strList 保存分割出的子字符串的列表
	*/
	void StringSplit(const std::wstring &str, const std::wstring &separator, std::vector<std::wstring> &strList);

	/** 
	*@brief 获取从字符串获取由限定字符构成的子字符串
	*@param str 等待拾取的字符串
	*@param strSub 构成子字符串的字符集
	*@param strList 保存获取的子字符串的列表
	*/
	void PickupString(const std::string &str, const std::string &strSub, std::vector<std::string> &strList);
	
	/** 
	*@brief 获取从字符串获取由限定字符构成的子字符串
	*@param str 等待拾取的字符串
	*@param strSub 构成子字符串的字符集
	*@param strList 保存获取的子字符串的列表
	*/
	void PickupString(const std::wstring &str, const std::wstring &strSub, std::vector<std::wstring> &strList);
}

#endif