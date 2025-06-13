#include "stdafx.h"
#include "ConsoleDlg.h"

#include "Transponder.h"
#include "SkyrayUtil.h"
#include "Packing.h"

// -----------------------------------------------------------------------------------------------------

CConsoleDlg::CConsoleDlg()
{
	m_hRichEditModule = NULL;
	m_nCurType = -1;
}

// -----------------------------------------------------------------------------------------------------

CConsoleDlg::~CConsoleDlg()
{
	
}

// -----------------------------------------------------------------------------------------------------

void CConsoleDlg::SetTransponder(NetLib::ITransponder *pTransponder)
{
	m_pTransponder = pTransponder;
}

// -----------------------------------------------------------------------------------------------------

void CConsoleDlg::AddType(NetLib::TransportID eID, const tstring &strName)
{
	if(m_hWnd)
	{
		CWindow			listRect = GetDlgItem(IDC_LIST_RECT);
		CComboBox		typeCtrl = GetDlgItem(IDC_TYPE);
		TypeItem		item;
		CRect			rcItem;

		typeCtrl.AddString(strName.c_str());
		
		listRect.GetWindowRect(&rcItem);
		ScreenToClient(&rcItem);

		item.m_uID = (UINT)eID;
		item.m_strName = strName;
		item.m_hWnd = ::CreateWindow(
										_T("RichEdit20W"), 
										NULL, 
										WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_READONLY | ES_WANTRETURN | WS_VSCROLL | WS_TABSTOP, 
										rcItem.left,
										rcItem.top,
										rcItem.Width(),
										rcItem.Height(),
										m_hWnd,
										NULL,
										NULL,
										NULL
									);
		
		if(item.m_hWnd)
		{
			CRichEditCtrl		editCtrl(item.m_hWnd);
			CHARFORMAT			cf;

			cf.dwMask |= CFM_COLOR | CFM_SIZE | CFM_FACE;
			cf.dwEffects = 0;
			cf.crTextColor = m_crSend;
			cf.yHeight = 240;
			_stprintf_s(cf.szFaceName, LF_FACESIZE, _T("宋体"));
			editCtrl.SetDefaultCharFormat(cf);
		}

		m_list.push_back(item);
		if(-1 == m_nCurType)
		{
			typeCtrl.SetCurSel(0);
			m_nCurType = 0;
			::ShowWindow(m_list[0].m_hWnd, SW_SHOW);
		}
	}
}

// -----------------------------------------------------------------------------------------------------

BOOL CConsoleDlg::OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/)
{
	if(NULL == m_hRichEditModule)
	{
		m_hRichEditModule = ::LoadLibrary(_T("riched20.dll"));
		::OleInitialize(NULL);
	}

	CWindow			listRect = GetDlgItem(IDC_LIST_RECT);
	CComboBox		typeCtrl = GetDlgItem(IDC_TYPE);
	TypeItem		item;
	CRect			rcItem;

	typeCtrl.AddString(_T("Debug"));

	listRect.GetWindowRect(&rcItem);
	ScreenToClient(&rcItem);

	item.m_uID = 0xFF00;
	item.m_strName = _T("Debug");
	item.m_hWnd = ::CreateWindow(
		_T("RichEdit20W"), 
		NULL, 
		WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_READONLY | ES_WANTRETURN | WS_VSCROLL | WS_TABSTOP, 
		rcItem.left,
		rcItem.top,
		rcItem.Width(),
		rcItem.Height(),
		m_hWnd,
		NULL,
		NULL,
		NULL
		);

	if(item.m_hWnd)
	{
		CRichEditCtrl		editCtrl(item.m_hWnd);
		CHARFORMAT			cf;

		cf.dwMask |= CFM_COLOR | CFM_SIZE | CFM_FACE;
		cf.dwEffects = 0;
		cf.crTextColor = m_crSend;
		cf.yHeight = 240;
		_stprintf_s(cf.szFaceName, LF_FACESIZE, _T("宋体"));
		editCtrl.SetDefaultCharFormat(cf);
	}

	m_list.push_back(item);
	if(-1 == m_nCurType)
	{
		typeCtrl.SetCurSel(0);
		m_nCurType = 0;
		::ShowWindow(m_list[0].m_hWnd, SW_SHOW);
	}
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CConsoleDlg::OnSend(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString					strTo;
	CString					strText;
	std::vector<tstring>	dataList;

	GetDlgItemText(IDC_TO, strTo);
	if(0 == strTo.GetLength())
	{	
		MessageBox(_T("接收方不能为空"));
		return 0;
	}

	GetDlgItemText(IDC_EDIT, strText);
	SetDlgItemText(IDC_EDIT, _T(""));
	
	Skyray::PickupString(tstring(strText), Skyray::g_strDigitxU, dataList);

	if(0 == dataList.size())
	{
		MessageBox(_T("发送数据不能为空"));
		return 0;
	}
	else
	{
		size_t				nSize = dataList.size();
		UINT				uTo = (UINT)_tstoi(strTo);		
		unsigned char		cValue;
		CPacking			*pPacking = new CPacking;

		for(size_t i=0; i<nSize; i++)
		{
			cValue = (unsigned char)Skyray::GetHexValue(dataList[i].c_str(), dataList[i].length());
			pPacking->Push((char)cValue);
		}

		m_pTransponder->Send((NetLib::TransportID)m_list[m_nCurType].m_uID, uTo, pPacking);
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CConsoleDlg::OnCancel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	size_t						nCount = m_list.size();

	for(size_t i=0; i<nCount; i++)
	{
		CComboBox				typeCtrl = GetDlgItem(IDC_TYPE);
		RichEditCtrlConstIt		it;

		typeCtrl.DeleteString(i);

		if(m_list[i].m_hWnd)
			::DestroyWindow(m_list[i].m_hWnd);
	}
	m_list.clear();
	m_nCurType = -1;

	DestroyWindow();
	return 0;
}

// -----------------------------------------------------------------------------------------------------

void CConsoleDlg::AddData(HWND hWnd, const char *pData, UINT uDataLen)
{
	CRichEditCtrl			listCtrl(hWnd);
	tstring					strText;
	tstring					strLine;
	TCHAR					acBuf[8];
	UINT					uCount = 0;
	
	assert(listCtrl.m_hWnd);

	for(UINT i=0; i<uDataLen; i++)
	{
		if(0 == strLine.length())
			_stprintf_s(acBuf, 7, _T("%02x"), (unsigned char)pData[i]);
		else
			_stprintf_s(acBuf, 7, _T(" %02x"), (unsigned char)pData[i]);

		strLine += acBuf;
		uCount++;

		if(uCount >= m_nLineSize)
		{
			if(0 != strText.length())
				strText += _T("\r\n");

			strText += strLine;
			strLine.clear();
			uCount = 0;
		}
	}

	if(0 != strLine.length())
	{
		if(0 != strText.length())
			strText += _T("\r\n");
		strText += strLine;
	}

	if(0 != strText.length())
	{
		listCtrl.SetSel(-1, -1);
		listCtrl.ReplaceSel(strText.c_str(), FALSE);
	}
}

// -----------------------------------------------------------------------------------------------------

void CConsoleDlg::AddText(HWND hWnd, const tstring &strText)
{
	if(0 != strText.length())
	{
		CRichEditCtrl			listCtrl(hWnd);
		
		assert(listCtrl.m_hWnd);

		listCtrl.SetSel(-1, -1);
		listCtrl.ReplaceSel(strText.c_str(), FALSE);
	}
}

// -----------------------------------------------------------------------------------------------------

void CConsoleDlg::SetTextColor(HWND hWnd, COLORREF crText)
{
	CRichEditCtrl		editCtrl(hWnd);
	CHARFORMAT			cf;
	
	editCtrl.GetSelectionCharFormat(cf);
	cf.dwMask|=CFM_COLOR;
	cf.dwEffects = 0;
	cf.crTextColor = crText;
	editCtrl.SetSelectionCharFormat(cf);
}

// -----------------------------------------------------------------------------------------------------

LRESULT CConsoleDlg::OnCbnSelchangeType(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CComboBox		typeCtrl = GetDlgItem(IDC_TYPE);
	int				nCurType = typeCtrl.GetCurSel();

	if(m_nCurType != nCurType)
	{
		if(-1 != m_nCurType)
			::ShowWindow(m_list[m_nCurType].m_hWnd, SW_HIDE);
		
		m_nCurType = nCurType;
		::ShowWindow(m_list[m_nCurType].m_hWnd, SW_SHOW);
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CConsoleDlg::OnInsertType(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	tstring				*pTransportName = (tstring *)lParam;

	AddType((NetLib::TransportID)wParam, *pTransportName);
	delete pTransportName;
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CConsoleDlg::OnRemoveType(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	NetLib::TransportID			eType = (NetLib::TransportID)wParam;
	size_t						nCount = m_list.size();

	for(size_t i=0; i<nCount; i++)
	{
		if(m_list[i].m_uID == (UINT)eType)
		{
			CComboBox				typeCtrl = GetDlgItem(IDC_TYPE);
			RichEditCtrlConstIt		it;

			typeCtrl.DeleteString(i);

			if(m_list[i].m_hWnd)
				::DestroyWindow(m_list[i].m_hWnd);

			it = m_list.begin();
			std::advance(it, i);

			m_list.erase(it);
			break;
		}
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CConsoleDlg::OnInsertData(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	ConsoleData			*pData = (ConsoleData *)lParam;
	int					nIndex = pData ? FindList(pData->m_strTransport) : -1;

	if(-1 != nIndex)
	{
		SYSTEMTIME		st;
		tstring			strTitle;
		TCHAR			acBuf[128];
		
		if(!m_list[nIndex].m_bEmpty)
			strTitle = _T("\r\n");

		if(pData->m_bSend)
			strTitle += _T("<==== 接收终端");
		else
			strTitle += _T("====> 发送终端");
		
		_stprintf_s(acBuf, 32, _T(" 0x%02x "), pData->m_uTo);
		strTitle += acBuf;

		::GetLocalTime(&st);
		_stprintf_s(acBuf, 127, _T("%04d年%02d月%02d日 %2d:%2d:%2d:%3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		strTitle += acBuf;
		strTitle += _T("\r\n");
		

		if(pData->m_bSend)
		{
			SetTextColor(m_list[nIndex].m_hWnd, m_crSend);
			AddText(m_list[nIndex].m_hWnd, strTitle);
			SetTextColor(m_list[nIndex].m_hWnd, m_crSend);
			AddData(m_list[nIndex].m_hWnd, pData->m_pData, pData->m_uDataLen);
		}
		else
		{
			SetTextColor(m_list[nIndex].m_hWnd, m_crRecv);
			AddText(m_list[nIndex].m_hWnd, strTitle);
			SetTextColor(m_list[nIndex].m_hWnd, m_crRecv);
			AddData(m_list[nIndex].m_hWnd, pData->m_pData, pData->m_uDataLen);
		}
		m_list[nIndex].m_bEmpty = FALSE;
	}

	delete pData;
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CConsoleDlg::OnInsertText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	ConsoleText			*pInfo = (ConsoleText *)lParam;
	int					nIndex = FindList(_T("Debug"));

	if(-1 != nIndex)
	{
		SYSTEMTIME		st;
		tstring			strTitle;
		TCHAR			acBuf[128];

		if(!m_list[nIndex].m_bEmpty)
			strTitle = _T("\r\n");

		::GetLocalTime(&st);
		_stprintf_s(acBuf, 127, _T("%04u %04d年%02d月%02d日 %2d:%2d:%2d:%3d"), pInfo->m_dwThreadID, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		strTitle += acBuf;
		strTitle += _T("\r\n  ");
		strTitle += pInfo->m_strTitle;
		strTitle += _T("\r\n");

		SetTextColor(m_list[nIndex].m_hWnd, m_crTitle);
		AddText(m_list[nIndex].m_hWnd, strTitle);
		SetTextColor(m_list[nIndex].m_hWnd, m_crTitle);
	}
	
	delete pInfo;
	return 0;
}

// -----------------------------------------------------------------------------------------------------

int CConsoleDlg::FindList(const tstring &strName)
{
	size_t				nCount = m_list.size();

	for(size_t i=0; i<nCount; i++)
	{
		if(m_list[i].m_strName == strName)
			return (int)i;
	}

	return -1;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CConsoleDlg::OnBnClickedClear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(-1 != m_nCurType)
	{
		CRichEditCtrl		editCtrl(m_list[m_nCurType].m_hWnd);

		editCtrl.SetSel(0, -1);
		editCtrl.ReplaceSel(_T(""), FALSE);

		m_list[m_nCurType].m_bEmpty = TRUE;
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CConsoleDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	if(m_hRichEditModule)
	{
		::OleUninitialize();
		//::FreeLibrary(m_hRichEditModule);
		//m_hRichEditModule = NULL;
	}

	::PostQuitMessage(0);
	bHandled = FALSE;
	return 1;
}