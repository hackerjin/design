#ifndef _SKYRAY_SOCKET_H_
#define _SKYRAY_SOCKET_H_

/*! 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file socket.h
* @brief 提供对套接字的简单封装
*  
* 为客户端版本简单的封装了套接字，以简化网络程序的编写。
*
* @version 1.0
* @author  汤军
* @date    2010年8月2日
*  
*  
* 修订说明：最初版本  
*/

#include "SkyrayLib.h"

namespace Skyray
{
	/**
	@brief 套接字 封装了系统的套接字函数以简化套接字使用的复杂度。
	*/
	class CSocket
	{
	public:
		CSocket();
		CSocket(const CSocket &otherSocket);
		virtual ~CSocket();

		/**
		*@brief	套接字是否是个合法的套接字
		*@return 	
		*- TRUE		合法
		*- FALSE	不合法
		*/
		BOOL IsValid() { return (INVALID_SOCKET != m_socket); }

		/**
		*@brief	由域名得到IP地址
		*@param	strDomain	域名
		*@param	strIP		地址
		*@return 	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/
		BOOL Domain2IP(const std::wstring &strDomain, std::wstring &strIP);

		/**
		*@brief	创建一个Socket
		*@param	nSocketType	套接字的类型
		*@param	pSocketIp	套接字的地址
		*@param	nSocketPort	套接字的端口号
		*@return 	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/
		BOOL Create(int nSocketType = SOCK_STREAM, const wchar_t *pSocketIP = NULL, UINT nSocketPort = 0);			

		/**
		*@brief	绑定一个Socket
		*@param	nSocketPort	套接字的端口号
		*@param	pSocketIp	套接字的地址
		*@return	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/
		BOOL Bind(const wchar_t *pSocketIP, UINT nSocketPort);

		/**
		*@brief	绑定一个Socket
		*@param	pSockAddr	套接字的完整地址
		*@param	nAddrLen	套接字的地址长度
		*@return 	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/
		BOOL Bind(const SOCKADDR *pSockAddr, int nAddrLen);

		/**
		*@brief		关闭一个套接字
		*@return 	无返回值
		*/	
		void Close();										

		/**
		*@brief	将一个socket句柄绑定到对象
		*@param	nSocket		套接字的句柄，	
		*@return 	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/	
		BOOL Attach(SOCKET nSocket);	

		/**
		*@brief	将一个socket句柄从对象中分离，并初始化对象
		*@param	nSocket		套接字的句柄，	
		*@return	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/	
		SOCKET Detach();

		/**
		*@brief	得到 Socket 得配置信息
		*@param	nOptionName		配置得名称
		*@param	nOptionValue	配置得值
		*@param	pOptionLen		配置得值得长度
		*@param	nLevel			配置得层次
		*@return 	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/
		BOOL GetSockOpt(int nOptionName, void *pOptionValue, int *pOptionLen, int nLevel=SOL_SOCKET);

		/**
		*@brief	设置 Socket 得配置信息
		*@param	nOptionName		配置名称
		*@param	pOptionValue	配置得值
		*@param	nOptionLen		配置得值得长度
		*@param	nLevel			配置得层次	
		*@return 	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/	
		BOOL SetSockOpt(int nOptionName, const void *pOptionValue, int nOptionLen, int nLevel = SOL_SOCKET);

		/**
		*@brief	得到最后一个网络错误
		*@return	同WSAGetLastError;
		*/
		DWORD GetLastError();

		/**
		*@brief	控制 套接字 的 IO 操作模式
		*@param	lCommand 	控制命令
		*@param	pArgument	命令参数
		*@return	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/
		BOOL IOCtl(int lCommand, DWORD *pArgument);

		/**
		*@brief	开启一个侦听
		*@param	nConnectCount	并发得连接数量
		*@return	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/
		BOOL Listen(int nConnectCount = 5);

		/**
		*@brief	使套接字的部分功能失效
		*@param	nHow	
		*- 0 接受失效
		*- 1 发送失效
		*- 2 接受和发送都失效
		*@return	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/
		BOOL ShutDown(int nHow = 1);

		/**
		*@brief	接受一个连接
		*@param	connectedSocket	连接对象
		*@param	pSockAddr		连接地址
		*@param	pSockAddrLen	连接地址得长度	
		*@return	
		*- TRUE		函数执行成功
		*- FALSE	函数执行失败
		*/
		virtual BOOL Accept(CSocket &connectedSocket, SOCKADDR *pSockAddr = NULL, int *pSockAddrLen=NULL);

		/**
		*@brief	建立一个连接
		*@param	pHostAddress	连接得目的地址
		*@param	nHostPort		连接的目的端口
		*@return	
		*- TRUE			函数执行成功
		*- FALSE		函数执行失败
		*/
		virtual BOOL Connect(const wchar_t *pHostAddress, UINT nHostPort);

		/**
		*@brief	建立一个连接
		*@param	pSocketAddr		连接得目的地址
		*@param	nSocketAddrLen	连接的目的地址的长度
		*@return	
		*- TRUE			函数执行成功
		*- FALSE		函数执行失败
		*/
		virtual BOOL Connect(const SOCKADDR *pSocketAddr, int nSocketAddrLen);

		/**
		*@brief	接收数据
		*@param	pBuffer			接受数据的用户缓冲区
		*@param	nBufferLen		缓冲区pBuffer的大小
		*@param	nFlags			接收标志
		*@return	
		*- SOCKET_ERROR	出错
		*- 其它			真实接受到的数据的长度；
		*/
		virtual int Receive(char *pBuffer, int nBufferLen, int nFlags = 0);	

		/**
		*@brief	发送数据
		*@param	pBuffer			用户要写的数据
		*@param	nBufferLen		数据pBuffer的大小
		*@param	nFlags			发送标志
		*@return	
		*- SOCKET_ERROR 	函数执行失败，原因参看函数send或sendto
		*- 其它				真实发送的数据的长度, 可能会小于nBufferLen；
		*/
		virtual int Send(const char *pBuffer, int nBufferLen, int nFlags = 0);	

		/**
		*@brief	接收数据
		*@param	pBuffer			接受数据的用户缓冲区
		*@param	nBufferLen		缓冲区pBuffer的大小
		*@param	nFlags			接收风格
		*@param	pRemoteAddr		保存数据源地址
		*@param	pAddrLen		数据源地址的长度
		*@return	
		*- 非零	真实接受到的数据的长度  
		*- 为零	函数执行失败，原因参看函数recv或recvfrom
		*/
		virtual int ReceiveFrom(char *pBuffer, int nBufferLen, int nFlags, SOCKADDR *pRemoteAddr, int *pAddrLen);	

		/**
		*@brief	发送数据
		*@param	pBuffer			用户要写的数据
		*@param	nBufferLen		数据pBuffer的大小
		*@param	nFlags			发送风格
		*@param	pRemoteAddr		数据目的地址
		*@param	pAddrLen		目的地址的长度
		*@return 	
		*- SOCKET_ERROR 	函数执行失败，原因参看函数send或sendto
		*- 其它			真实发送的数据的长度, 可能会小于nBufferLen；
		*/
		virtual int SendTo(const char *pBuffer, int nBufferLen, int nFlags, SOCKADDR *pRemoteAddr, int nAddrLen);

		/**
		*@brief	查看套接字是否可读
		*@param	dwMilliseconds	查询超时(单位为毫秒)
		*@return	
		*- TRUE		套接字可读
		*- FALSE		套接字不可读
		*/
		virtual BOOL CanRead(DWORD dwMilliseconds=0);

		/**
		*@brief	查看套接字是否可写
		*@param	dwMilliseconds	查询超时(单位为毫秒)
		*@return	
		*- TRUE		套接字可写
		*- FALSE		套接字不可写
		*/								
		virtual BOOL CanWrite(DWORD dwMilliseconds=0);	

	private:
		SOCKET		m_socket;		
	};
}

#endif