#ifndef _SKYRAY_UTIL_H_
#define _SKYRAY_UTIL_H_

#include "SkyrayLib.h"

namespace Skyray
{
	extern const std::string g_strDigitxA;	//!< ���16���������ַ���
	extern const std::wstring g_strDigitxU;	//!< ���16���������ַ���

	/** 
	*@brief ����ǰ�ַ���ת����UTF-8�ĸ�ʽ
	*@param lpInput �ȴ�ת�����ַ���
	*@param strOutPut ת�����UTF-8�ַ���
	*/
	void UTF8Encode(const char *pInput, std::string &strOutput);
	
	/** 
	*@brief ����ǰ�ַ���ת����UTF-8�ĸ�ʽ
	*@param lpInput �ȴ�ת�����ַ���
	*@param strOutPut ת�����UTF-8�ַ���
	*/
	void UTF8Encode(const wchar_t *pInput, std::string &strOutput);

	/** 
	*@brief ��UTF-8�ĸ�ʽ���ַ���ת���ɵ�ǰ��ʽ
	*@param lpInput �ȴ�ת�����ַ���
	*@param strOutPut ת������ַ���
	*/
	void UTF8Decode(const char *pInput, std::string &strOutput);
	
	/** 
	*@brief ��UTF-8�ĸ�ʽ���ַ���ת���ɵ�ǰ��ʽ
	*@param lpInput �ȴ�ת�����ַ���
	*@param strOutPut ת������ַ���
	*/
	void UTF8Decode(const char *pInput, std::wstring &strOutput);

	/** 
	*@brief ��Unicode��ʽ���ַ���ת����Ansi��ʽ���ַ���
	*@param pInput �ȴ�ת�����ַ���
	*@param strOutPut ת�����Ansi��ʽ���ַ���
	*/
	void Unicode2Ansi(const wchar_t *pInput, std::string &strOutput);

	/** 
	*@brief ��Ansi��ʽ���ַ���ת����Unicode��ʽ���ַ���
	*@param pInput �ȴ�ת�����ַ���
	*@param strOutPut ת�����Unicode��ʽ���ַ���
	*/
	void Ansi2Unicode(const char *pInput, std::wstring &strOutput);

	/** 
	*@brief �õ��ַ�������16���Ƶ���������ֵ
	*@param pBuffer �ȴ�������ַ���
	*@param nLen �ַ����ĳ���
	*@return �����ַ�����������ֵ
	*/
	UINT GetHexValue(const char *pBuffer, int nLen);
	
	/** 
	*@brief �õ��ַ�������16���Ƶ���������ֵ
	*@param pBuffer �ȴ�������ַ���
	*@param nLen �ַ����ĳ���
	*@return �����ַ�����������ֵ
	*/
	UINT GetHexValue(const wchar_t *pBuffer, int nLen);

	/** 
	*@brief �ָ��ַ���
	*@param str �ȴ��ָ���ַ���
	*@param separator �ָ��ַ�
	*@param strList ����ָ�������ַ������б�
	*/
	void StringSplit(const std::string &str, std::string::value_type separator, std::vector<std::string> &strList);
	
	/** 
	*@brief �ָ��ַ���
	*@param str �ȴ��ָ���ַ���
	*@param separator �ָ��ַ�
	*@param strList ����ָ�������ַ������б�
	*/
	void StringSplit(const std::wstring &str, std::wstring::value_type separator, std::vector<std::wstring> &strList);

	/** 
	*@brief �ָ��ַ���
	*@param str �ȴ��ָ���ַ���
	*@param separator �ָ��ַ��������ַ��������������ַ������������Ϊ�ָ�����
	*@param strList ����ָ�������ַ������б�
	*/
	void StringSplit(const std::string &str, const std::string &separator, std::vector<std::string> &strList);
	
	/** 
	*@brief �ָ��ַ���
	*@param str �ȴ��ָ���ַ���
	*@param separator �ָ��ַ��������ַ��������������ַ������������Ϊ�ָ�����
	*@param strList ����ָ�������ַ������б�
	*/
	void StringSplit(const std::wstring &str, const std::wstring &separator, std::vector<std::wstring> &strList);

	/** 
	*@brief ��ȡ���ַ�����ȡ���޶��ַ����ɵ����ַ���
	*@param str �ȴ�ʰȡ���ַ���
	*@param strSub �������ַ������ַ���
	*@param strList �����ȡ�����ַ������б�
	*/
	void PickupString(const std::string &str, const std::string &strSub, std::vector<std::string> &strList);
	
	/** 
	*@brief ��ȡ���ַ�����ȡ���޶��ַ����ɵ����ַ���
	*@param str �ȴ�ʰȡ���ַ���
	*@param strSub �������ַ������ַ���
	*@param strList �����ȡ�����ַ������б�
	*/
	void PickupString(const std::wstring &str, const std::wstring &strSub, std::vector<std::wstring> &strList);
}

#endif