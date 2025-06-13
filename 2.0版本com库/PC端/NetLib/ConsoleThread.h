#ifndef _CONSOLE_THREAD_H_
#define _CONSOLE_THREAD_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file ConsoleThread.h
* @brief ����̨�߳�
*  
* ����̨�����������̣߳���Ҫ��������̨���ڵ���Ϣѭ��
*
* @version 1.0
* @author  ����
* @date    2010��8��5��
*  
*  
* �޶�˵��������汾  
*/

#include "SkyrayThread.h"
#include "ConsoleDlg.h"

#include "ITransport.h"
#include "ITransponder.h"

#include "SkyrayLock.h"

class CConsoleThread : public Skyray::CThread
{
public:
	CConsoleThread();
	~CConsoleThread();
	
	/** 
	*@brief	����ת����
	*@param	lpName ת�����ӿ�
	*@return û�з���ֵ
	*/
	void SetTransponder(NetLib::ITransponder *pTransponder);

	/** 
	*@brief	��Ӵ�����������
	*@param uID ��������ʶ��
	*@param	lpName ����������
	*@return û�з���ֵ
	*/
	void AddType(NetLib::TransportID eID, const TCHAR *pName);
	
	/** 
	*@brief	�Ƴ�������������
	*@param uID ��������ʶ��
	*@return û�з���ֵ
	*/
	void RemoveType(NetLib::TransportID eID);

	/** 
	*@brief	��ʾ����̨
	*@param	bShow
	*- TRUE ��ʾ����̨
	*- FALSE ���ؿ���̨
	*@return û�з���ֵ
	*/
	void ShowConsole(BOOL bShow);
	
	/** 
	*@brief	���һ�����ݰ�������̨
	*@param	lpName		����������
	*@param uTo			���ݰ���Ŀ�ĵ�ַ
	*@param	pData		���ݰ����ݵ��׵�ַ
	*@param uDataLen	���ݰ����ݵĳ���
	*@param bSend		�����ݰ��Ǳ����ͻ��Ǳ�����
	*@return û�з���ֵ
	*/
	void AddData(const TCHAR *pName, UINT uTo, const char *pData, UINT uDataLen, BOOL bSend);
	
	/** 
	*@brief	����ı�������̨
	*@param	pText		����������
	*@return û�з���ֵ
	*/
	void AddText(const TCHAR *pText);

	/** 
	*@brief	���ٿ���̨
	*@return û�з���ֵ
	*/
	void Destroy();
	
	/** 
	*@brief	����̨�Ƿ��Ѿ�����
	*@return 
	*- TRUE ����̨���� 
	*- FALSE ����̨δ��
	*/
	BOOL IsOPenConsole();

private:
	DWORD Run();

private:
	struct TypeItem
	{
		NetLib::TransportID m_eID;
		tstring				m_strName;
	};

	typedef std::vector<TypeItem>		TypeList;
	typedef TypeList::const_iterator	TypeConstIt;
	typedef TypeList::iterator			TypeIt;

private:
	Skyray::CLock		m_lock;
	CConsoleDlg			m_console;
	TypeList			m_types;
};

#endif