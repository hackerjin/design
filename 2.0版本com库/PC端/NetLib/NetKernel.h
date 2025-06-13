#ifndef _NET_KERNEL_H_
#define _NET_KERNEL_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file INetKernel.h
* @brief 网络内核
*  
* 实现网络通讯模块的内心接口
*
* @version 1.0
* @author  汤军
* @date    2010年8月3日
*  
*  
* 修订说明：最初版本  
*/

#include "INetKernel.h"

#include "EndPointMgr.h"
#include "Packing.h"
#include "Transponder.h"
#include "Transport.h"
#include "RemoteServer.h"
#include "ConsoleThread.h"

class CNetKernel : public NetLib::INetKernel
{
public:
	/** 
	*@brief		设置回调接口
	*@param		pCallback 网络内核类的回调接口
	*@return	无返回值
	*/
	void SetCallback(NetLib::INetKernelCallback *pCallback) { m_transponder.SetCallback(pCallback); }

	/** 
	*@brief		启动与仪器的连接
	*@param		pIP		仪器的IP地址		
	*@param		uPort	仪器的端口号
	*@return	
	*- TRUE		连接成功 
	*- FALSE	连接失败
	*/
	BOOL Startup(const wchar_t *pIP, UINT uPort);

	/** 
	*@brief		断开与仪器的连接
	*@return	无返回值
	*/
	void Shutdown();

	/** 
	*@brief		请求远程协助
	*@param		pIP		远端PC的IP地址		
	*@param		uPort	远端PC的端口号
	*@return	
	*- TRUE		连接成功 
	*- FALSE	连接失败
	*/
	BOOL StartupRemote(const wchar_t *pIP, UINT uPort);

	/** 
	*@brief		断开远端协助
	*@return	无返回值
	*/
	void ShutdownRemote();
	
	/** 
	*@brief		开启提供远程协助的服务
	*@param		pIP		服务的IP地址		
	*@param		uPort	服务的端口号
	*@return	
	*- TRUE		服务开启成功 
	*- FALSE	服务开启失败
	*/
	BOOL StartupRemoteServer(const wchar_t *pIP, UINT uPort);

	/** 
	*@brief		关闭远端协助的服务
	*@return 无返回值
	*/
	void ShutdownRemoteServer();

	/** 
	*@brief		获取转发器
	*@return	转发器接口
	*/
	NetLib::ITransponder* Transponder() { return &m_transponder; }

	/** 
	*@brief		获取终端管理器
	*@return		终端管理器接口
	*/
	NetLib::IEndPointMgr* EndPointMgr() { return &m_endPointMgr; }
	
	/** 
	*@brief		创建一个数据序列化接口
	*@return	封包器接口
	*/
	NetLib::IPacking* CreatePacking() { return new CPacking(); }
	
	/**
	*@brief		打开调试控制台
	*@return 无返回值
	*/
	void OpenConsole();

	/**
	*@brief		关闭调试控制台
	*@return 无返回值
	*/
	void CloseConsole();
	
	/**
	*@brief		在控制台打印文本
	*@param	pText 将要在控制台中显示的文本
	*@return 无返回值
	*/
	void ConsolePrint(const wchar_t *pText);

	/**
	*@brief		销毁接口
	*@return 无返回值
	*/
	void Destroy();

public:
	static NetLib::INetKernel* Instance();

private:
	CNetKernel();
	~CNetKernel();

private:
	CConsoleThread		m_consoleThread;	//!< 控制台线程

	CEndPointMgr		m_endPointMgr;		//!< 终端管理器
	CTransponder		m_transponder;		//!< 转发器
	CRemoteServer		m_remoteServer;		//!< 接受远程协助的服务器
};

#endif