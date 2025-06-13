#include "StdAfx.h"
#include "IPConfigDlg.h"

// -----------------------------------------------------------------------------------------------------

CIPConfigDlg::CIPConfigDlg()
{

}

// -----------------------------------------------------------------------------------------------------

CIPConfigDlg::~CIPConfigDlg()
{
}

// -----------------------------------------------------------------------------------------------------

BOOL CIPConfigDlg::OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/)
{
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CIPConfigDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString				strIP;
	CString				strSubnetMask;
	CString				strGateWay;
	CString				strDNS;

	GetDlgItemText(IDC_IP, strIP);
	if((0 == strIP.GetLength()) || (strIP == _T("0.0.0.0")))
	{
		MessageBox(_T("IP地址不能为空"));
		return 0;
	}
	
	GetDlgItemText(IDC_SUBNET_MASK, strSubnetMask);
	if((0 == strSubnetMask.GetLength()) || (strSubnetMask == _T("0.0.0.0")))
	{
		MessageBox(_T("子网掩码不能为空"));
		return 0;
	}

	GetDlgItemText(IDC_GATEWAY, strGateWay);
	if((0 == strGateWay.GetLength()) || (strGateWay == _T("0.0.0.0")))
	{
		MessageBox(_T("网关不能为空"));
		return 0;
	}

	GetDlgItemText(IDC_DNS, strDNS);
	if((0 == strDNS.GetLength()) || (strDNS == _T("0.0.0.0")))
	{
		MessageBox(_T("DNS不能为空"));
		return 0;
	}
	
// 	if(m_pXRFApp)
// 	{
// 		XRF::IApparatus		*pApparatus = m_pXRFApp->Apparatus();
// 
// 		pApparatus->SetIPConfig(strIP, strSubnetMask, strGateWay, strDNS);
// 	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CIPConfigDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(IDCANCEL);
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CIPConfigDlg::OnBnClickedGetIp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
// 	if(m_pXRFApp)
// 	{
// 		XRF::IApparatus		*pApparatus = m_pXRFApp->Apparatus();
// 
// 		pApparatus->GetIP();
// 	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CIPConfigDlg::OnBnClickedSetIp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
// 	CString				strIP;
// 
// 	GetDlgItemText(IDC_NEW_IP, strIP);
// 	if(m_pXRFApp)
// 	{
// 		XRF::IApparatus		*pApparatus = m_pXRFApp->Apparatus();
// 
// 		pApparatus->SetIP(strIP);
// 	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CIPConfigDlg::OnBnClickedGetPort(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
// 	if(m_pXRFApp)
// 	{
// 		XRF::IApparatus		*pApparatus = m_pXRFApp->Apparatus();
// 
// 		pApparatus->GetPort();
// 	}
	return 0;
}
