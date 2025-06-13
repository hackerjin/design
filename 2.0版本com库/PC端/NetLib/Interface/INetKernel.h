#ifndef _I_NET_KERNEL_H_
#define _I_NET_KERNEL_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file INetKernel.h
* @brief 网络内核接口
*  
* 网络通讯模块的内心接口，本接口是个单体,主要为了简化网络模块的使用
*
* @version 1.0
* @author  汤军
* @date    2010年8月3日
*  
* 修订说明：最初版本  
*/

#include "INetKernelCallback.h"
#include "ITransponder.h"
#include "IEndPointMgr.h"
#include "IPacking.h"

/** @mainpage 通用网络通讯系统
*@section 概述
*    通用网络通讯系统PC端演示软件主要有网络传输层、应用逻辑层、UI层三层组成。其中网络通讯层负责提供可靠的由终端到终端
*的数据传输功能，应用逻辑层根据具体的应用以终端为颗粒来组织整个应用的数据，UI层主要负责用户输入以及对测试过程或结果的
*反馈。对于以后具体的系统开发中所用到的算法，将由独立模块，以逻辑层的外接设施来提供，其对传输层和UI层透明。
*@section 网络传输层
*- 主要职责：提供一个可靠的由终端到终端的数据传输功能。对终端的位置不敏感。
*- 主要分模块。
*	-# 终端：主要定义通用的逻辑层和网络层的交互接口，是个抽象类，由逻辑层实现，网络层仅负责定义这个接口。
*	-# 终端管理器：提供终端接口的管理功能：添加、删除、查找。
*	-# 传输器：提供真实的数据传输服务。数据已序列化和反序列化接口的方式传递。
*	-# 传输管理器：提供对传输器接口的管理功能：添加、删除、查找。
*	-# 控制台：提供一个调试的手段，可以显示当前发送和接受的数据包，可以编辑发送数据包。
*	-# 总控模块：本身是个单体，提供对终端管理器、传输管理器的生存期的维护。负责网络连接的建立与断开。提供访问终端管理器的方法。
*- 网络层提供通用的数据序列化与反序列化的接口，以方便逻辑层对网络数据的打包与解包。
*- 网络层对逻辑层的反馈主要通过由逻辑层实现网络层定义的回调接口来进行。
*@section 应用逻辑层
*- 主要职责：实现面向逻辑层的终端接口。序列化网络层以及逻辑层的多线程环境下的回调。使其工作于UI层的线程环境下。
*- 主要分模块
*	-# 终端：主要实现了X光管、多道数据采集器、电机控制器等。
*	-# 事件管理器：将多线程环境下的回调序列化到UI线程环境中执行。
*- 应用层对UI层的反馈主要通过由UI层实现逻辑层定义的回调接口来进行。
*@section UI层
*- 主要职责：接受用户输入（含对输入的预处理）、展示处理结果。
*- 本UI层主要用于测试的目的，过只使用简单的界面展示。
*@section 程序结构
*	整个程序有四个项目构成，每个负责实现一个方面。SkyrayLib主要是些工具类的结合，使得其他模块可以方便的实现字符串转码，
*开启线程，高精度定时器，套接字等。NetLib主要实现网络传输层。XRFNet主要实现应用逻辑层。NetWorkDemo主要实现UI层。
*/

/** 
@brief 网络通讯层
*- 网络连接建立
*- 数据序列化与反序列化
*- 网络数据路由
*- 终端的定义
*/
namespace NetLib
{
	/** 
	*@brief 网络通讯核心类
	*/
	class INetKernel
	{
	public:
		/** 
		*@brief		设置回调接口
		*@param		pCallback 网络内核类的回调接口
		*@return	无返回值
		*/
		virtual void SetCallback(INetKernelCallback *pCallback) = 0;

		/** 
		*@brief		启动与仪器的连接
		*@param		pIP		仪器的IP地址		
		*@param		uPort	仪器的端口号
		*@return	
		*- TRUE		连接成功 
		*- FALSE	连接失败
		*/
		virtual BOOL Startup(const wchar_t *pIP, UINT uPort) = 0;
		
		/** 
		*@brief		断开与仪器的连接
		*@return	无返回值
		*/
		virtual void Shutdown() = 0;

		/** 
		*@brief		请求远程协助
		*@param		pIP		远端PC的IP地址		
		*@param		uPort	远端PC的端口号
		*@return	
		*- TRUE		连接成功 
		*- FALSE	连接失败
		*/
		virtual BOOL StartupRemote(const wchar_t *pIP, UINT uPort) = 0;
		
		/** 
		*@brief		断开远端协助
		*@return	无返回值
		*/
		virtual void ShutdownRemote() = 0;
		
		/** 
		*@brief		开启提供远程协助的服务
		*@param		pIP		服务的IP地址		
		*@param		uPort	服务的端口号
		*@return	
		*- TRUE		服务开启成功 
		*- FALSE	服务开启失败
		*/
		virtual BOOL StartupRemoteServer(const wchar_t *pIP, UINT uPort) = 0;

		/** 
		*@brief		关闭远端协助的服务
		*@return 无返回值
		*/
		virtual void ShutdownRemoteServer() = 0;
		
		/** 
		*@brief		获取转发器
		*@return	转发器接口
		*/
		virtual ITransponder* Transponder() = 0;

		/** 
		*@brief		获取终端管理器
		*@return	终端管理器接口
		*/
		virtual IEndPointMgr* EndPointMgr() = 0;

		/** 
		*@brief		创建一个数据序列化接口
		*@return	封包器接口
		*/
		virtual IPacking* CreatePacking() = 0;
		
		/**
		*@brief		打开调试控制台
		*@return 无返回值
		*/
		virtual void OpenConsole() = 0;

		/**
		*@brief		关闭调试控制台
		*@return 无返回值
		*/
		virtual void CloseConsole() = 0;
		
		/**
		*@brief		在控制台打印文本
		*@param	pText 将要在控制台中显示的文本
		*@return 无返回值
		*/
		virtual void ConsolePrint(const wchar_t *pText) = 0;
		
		/**
		*@brief		销毁接口
		*@return 无返回值
		*/
		virtual void Destroy() = 0;
	};
}


#ifdef NETLIB_EXPORTS
	extern "C" __declspec(dllexport) NetLib::INetKernel* CreateNetKernel();
#else
	extern "C" __declspec(dllimport) NetLib::INetKernel* CreateNetKernel();
#endif

#endif