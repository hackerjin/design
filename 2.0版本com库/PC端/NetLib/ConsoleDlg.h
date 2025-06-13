#ifndef _CONSOLE_DLG_H_
#define _CONSOLE_DLG_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file ConsoleDlg.h
* @brief 控制台对话框
*  
* 控制台对话框由WTL实现
*
* @version 1.0
* @author  汤军
* @date    2010年8月5日
*  
*  
* 修订说明：最初版本  
*/

#include <atlbase.h>
#include <atlstr.h>
#include <atlapp.h>
#define _WTL_NO_CSTRING
#include <atlmisc.h>
#include <atlwin.h>
#include <atlcrack.h>
#include <atlctrls.h>

#include "Resource.h"

#include "ITransport.h"
#include "ITransponder.h"

#define WM_INSERT_TYPE (WM_USER+101)
#define WM_REMOVE_TYPE (WM_USER+102)
#define WM_INSERT_DATA (WM_USER+103)
#define WM_INSERT_TEXT (WM_USER+104)

struct ConsoleData
{
	tstring		m_strTransport;
	UINT		m_uTo;
	char		*m_pData;
	UINT		m_uDataLen;
	BOOL		m_bSend;

	ConsoleData()
	{
		m_strTransport	= _T("");
		m_uTo			= 0;
		m_pData			= NULL;
		m_uDataLen		= 0;
		m_bSend			= TRUE;
	}

	~ConsoleData()
	{
		if(m_pData)
		{
			delete []m_pData;
			m_pData = NULL;
		}
	}
};

struct ConsoleText
{
	tstring		m_strTitle;
	DWORD		m_dwThreadID;
};

class CConsoleDlg : public ATL::CDialogImpl<CConsoleDlg>
{
public:
	enum { IDD = IDD_CONSOLE };

public:
	CConsoleDlg();
	~CConsoleDlg();
	
	/** 
	*@brief	添加传输器的类型
	*@param uID 传输器标识符
	*@param	strName 传输器名称
	*/
	void AddType(NetLib::TransportID eID, const tstring &strName);
	
	/** 
	*@brief	设置转发器
	*@param	pTransponder 转发器
	*/
	void SetTransponder(NetLib::ITransponder *pTransponder);

public:
	BEGIN_MSG_MAP(CConsoleDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnSend)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
		COMMAND_HANDLER(IDC_TYPE, CBN_SELCHANGE, OnCbnSelchangeType)
		MESSAGE_HANDLER(WM_INSERT_TYPE, OnInsertType)
		MESSAGE_HANDLER(WM_REMOVE_TYPE, OnRemoveType)
		MESSAGE_HANDLER(WM_INSERT_DATA, OnInsertData)
		MESSAGE_HANDLER(WM_INSERT_TEXT, OnInsertText)
		COMMAND_HANDLER(IDC_CLEAR, BN_CLICKED, OnBnClickedClear)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	END_MSG_MAP()

private:
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	LRESULT OnSend(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchangeType(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnInsertType(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnRemoveType(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnInsertData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnInsertText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnBnClickedClear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	const static UINT		m_nLineSize = 16;			//!<一行显示的数据的个数
	const static COLORREF	m_crSend = RGB(136, 0, 0);	//!< 发送出的数据显示的颜色
	const static COLORREF	m_crRecv = RGB(0, 128, 0);	//!< 接收到的数据显示的颜色
	const static COLORREF	m_crTitle = RGB(0, 0, 128);	//!< 控制台文本的现实

private:
	void AddData(HWND hWnd, const char *pData, UINT uDataLen);
	void AddText(HWND hWnd, const tstring &strText);
	void SetTextColor(HWND hWnd, COLORREF crText);
	int FindList(const tstring &strName);

private:
	struct TypeItem
	{
		UINT			m_uID;		//!< 传输器识别符
		tstring			m_strName;	//!< 传输器名称
		HWND			m_hWnd;		//!< 显示该传输器上传输的数据的RichEdit
		BOOL			m_bEmpty;	//!< 列表框是否为空
		
		TypeItem()
		{
			m_uID = (UINT)NetLib::e_apparatus_transport;
			m_strName = _T("");
			m_hWnd = NULL;
			m_bEmpty = TRUE;
		}

		TypeItem(const TypeItem &other)
		{
			m_uID = other.m_uID;
			m_strName = other.m_strName;
			m_hWnd = other.m_hWnd;
			m_bEmpty = other.m_bEmpty;
		}

		TypeItem& operator=(const TypeItem &other)
		{
			if(this != &other)
			{
				m_uID = other.m_uID;
				m_strName = other.m_strName;
				m_hWnd = other.m_hWnd;
				m_bEmpty = other.m_bEmpty;
			}

			return *this;
		}
	};

	typedef std::vector<TypeItem>				RichEditCtrlList;
	typedef RichEditCtrlList::iterator			RichEditCtrlIt;
	typedef	RichEditCtrlList::const_iterator	RichEditCtrlConstIt;

private:
	HMODULE					m_hRichEditModule;
	NetLib::ITransponder	*m_pTransponder;
	RichEditCtrlList		m_list;
	int						m_nCurType;	
	
};

#endif