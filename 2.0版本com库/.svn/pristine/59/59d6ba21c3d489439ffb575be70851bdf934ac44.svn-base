#ifndef _CONSOLE_THREAD_H_
#define _CONSOLE_THREAD_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file ConsoleThread.h
* @brief 控制台线程
*  
* 控制台窗口所处的线程，主要包含控制台窗口的消息循环
*
* @version 1.0
* @author  汤军
* @date    2010年8月5日
*  
*  
* 修订说明：最初版本  
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
	*@brief	设置转发器
	*@param	lpName 转发器接口
	*@return 没有返回值
	*/
	void SetTransponder(NetLib::ITransponder *pTransponder);

	/** 
	*@brief	添加传输器的类型
	*@param uID 传输器标识符
	*@param	lpName 传输器名称
	*@return 没有返回值
	*/
	void AddType(NetLib::TransportID eID, const TCHAR *pName);
	
	/** 
	*@brief	移除传输器的类型
	*@param uID 传输器标识符
	*@return 没有返回值
	*/
	void RemoveType(NetLib::TransportID eID);

	/** 
	*@brief	显示控制台
	*@param	bShow
	*- TRUE 显示控制台
	*- FALSE 隐藏控制台
	*@return 没有返回值
	*/
	void ShowConsole(BOOL bShow);
	
	/** 
	*@brief	添加一个数据包到控制台
	*@param	lpName		传输器名称
	*@param uTo			数据包的目的地址
	*@param	pData		数据包内容的首地址
	*@param uDataLen	数据包内容的长度
	*@param bSend		该数据包是被发送还是被接受
	*@return 没有返回值
	*/
	void AddData(const TCHAR *pName, UINT uTo, const char *pData, UINT uDataLen, BOOL bSend);
	
	/** 
	*@brief	添加文本到控制台
	*@param	pText		传输器名称
	*@return 没有返回值
	*/
	void AddText(const TCHAR *pText);

	/** 
	*@brief	销毁控制台
	*@return 没有返回值
	*/
	void Destroy();
	
	/** 
	*@brief	控制台是否已经被打开
	*@return 
	*- TRUE 控制台被打开 
	*- FALSE 控制台未打开
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