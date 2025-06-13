#ifndef _EVENT_MGR_H_
#define _EVENT_MGR_H_

#include "IEventMgr.h"
#include "SkyrayLock.h"

#include <vector>
#include <map>
#include <list>

class CEventMgr : public IEventMgr
{
public:
	CEventMgr();
	~CEventMgr();
	
	/**
	 @brief 设置事件通知执行的线程环境
	 @warning 调用该方法的线程必须为窗口线程，而所有侦听器代码的执行在该线程的上下文环境中。
	*/
	void SetProcedureContext();

	/**
	 @brief 注册事件
	 @param	lpEventName	事件名称
	 @return == TRUE 注册成功 == FALSE注册失败（主要是同名事件已经被注册）
	*/
	BOOL Register(LPCTSTR lpEventName);

	/**
	 @brief 注销事件
	 @param	lpEventName	事件名称
	*/
	void Unregister(LPCTSTR lpEventName);
	
	/**
	 @brief 指定事件是否存在
	 @return == TRUE 事件存在 == FALSE 事件不存在
	*/
	BOOL EventIsExist(LPCTSTR lpEventName);

	/**
	 @brief 挂钩事件
	 @param	lpEventName	事件名称
	 @param pListener 事件侦听器
	 @return == TRUE 挂钩成功 == FALSE挂钩失败（主要是指定事件未被注册）
	*/
	BOOL Hook(LPCTSTR lpEventName, IEventListener *pListener);

	/**
	 @brief 脱钩事件
	 @param	lpEventName	事件名称
	 @param pListener 事件侦听器
	*/
	void Unhook(LPCTSTR lpEventName, IEventListener *pListener);

	/**
	 @brief 通知事件被触发
	 @param	lpEventName	事件名称
	 @param wParam		事件参数1
	 @param	lParam		事件参数2
	 @return == TRUE 事件通知成功。 == FALSE 事件通知失败（主要是指定事件未被注册）
	 @warning 事件参数的具体含义参看具体事件的定义
	*/
	BOOL Notify(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam);

private:
	typedef std::list<IEventListener *>			ListenerList;
	typedef ListenerList::iterator					ListenerIt;

	typedef std::map<tstring, ListenerList*>		EventList;
	typedef EventList::iterator						EventIt;
	typedef EventList::const_iterator				EventConstIt;
	
	typedef std::list<tstring>						TraversalList;
	typedef TraversalList::iterator					TraversalIt;
	typedef TraversalList::const_iterator			TraversalConstIt;

private:
	BOOL Procedure(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam);
	void PushTraversal(const tstring &strName);
	void PopTraversal();
	BOOL IsTraversal(const tstring &strName);

private:
	struct APCTask
	{
		IEventMgr			*m_pEventMgr;	//!< 事件管理器接口
		tstring				m_strEventName;	//!< 事件名称
		WPARAM				m_wParam;		//!< 事件参数1
		LPARAM				m_lParam;		//!< 事件参数2
	};

private:
	static LRESULT CALLBACK APCWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void CALLBACK APCProc(ULONG_PTR dwParam);

private:
	HANDLE				m_hThread;			//!< 执行侦听器过程的线程的句柄
	DWORD				m_dwThreadID;		//!< 执行侦听器过程的线程ID
	HWND				m_hWnd;				//!< 使得线程 m_hThread 进入警告状态的建立在线程 m_hThread上的不可见的辅助窗口
	
	Skyray::CLock		m_lock;				//!< 线程同步锁
	TraversalList		m_traversalList;	//!< 真在遍历列表的集合
	EventList			m_events;			//!< 事件列表
};

#endif