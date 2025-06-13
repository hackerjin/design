#ifndef _I_EVENT_MGR_H_
#define _I_EVENT_MGR_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file IEventMgr.h
* @brief 提供事件管理器
*  
* 提供事件管理器的接口定义。事件管理器可以将来之不同线程的通知处理序列化到指定的窗口线程。
*
* @version 1.0
* @author  汤军
* @date    2010年8月2日
*  
*  
* 修订说明：最初版本  
*/

/**
 @brief 事件侦听器接口 主要负责对事件进行处理的回调接口
*/
class IEventListener
{
public:
	/**
	 @brief 事件处理过程
	 @param	lpEventName	事件名称
	 @param wParam		事件参数1
	 @param	lParam		事件参数2
	 @warning 事件参数的具体含义参看具体事件的定义
	*/
	virtual void Procedure(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam) = 0;
};

/**
@brief 事件管理器接口 
* - 事件的注册、注销
* - 事件的挂钩、脱钩
* - 事件的分发
*/
class IEventMgr
{
public:
	/**
	 @brief 设置事件通知执行的线程环境
	 @warning 调用该方法的线程必须为窗口线程，而所有侦听器代码的执行在该线程的上下文环境中。
	*/
	virtual void SetProcedureContext() = 0;

	/**
	 @brief 注册事件
	 @param	lpEventName	事件名称
	 @return == TRUE 注册成功 == FALSE注册失败（主要是同名事件已经被注册）
	*/
	virtual BOOL Register(LPCTSTR lpEventName) = 0;

	/**
	 @brief 注销事件
	 @param	lpEventName	事件名称
	*/
	virtual void Unregister(LPCTSTR lpEventName) = 0;
	
	/**
	 @brief 指定事件是否存在
	 @return == TRUE 事件存在 == FALSE 事件不存在
	*/
	virtual BOOL EventIsExist(LPCTSTR lpEventName) = 0;

	/**
	 @brief 挂钩事件
	 @param	lpEventName	事件名称
	 @param pListener 事件侦听器
	 @return == TRUE 挂钩成功 == FALSE挂钩失败（主要是指定事件未被注册）
	*/
	virtual BOOL Hook(LPCTSTR lpEventName, IEventListener *pListener) = 0;

	/**
	 @brief 脱钩事件
	 @param	lpEventName	事件名称
	 @param pListener 事件侦听器
	*/
	virtual void Unhook(LPCTSTR lpEventName, IEventListener *pListener) = 0;

	/**
	 @brief 通知事件被触发
	 @param	lpEventName	事件名称
	 @param wParam		事件参数1
	 @param	lParam		事件参数2
	 @return == TRUE 事件通知成功。 == FALSE 事件通知失败（主要是指定事件未被注册）
	 @warning 事件参数的具体含义参看具体事件的定义
	*/
	virtual BOOL Notify(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam) = 0;
};

#endif