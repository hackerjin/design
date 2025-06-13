#include "StdAfx.h"
#include "RayTubeDlg.h"

// -----------------------------------------------------------------------------------------------------

CRayTubeDlg::CRayTubeDlg(IXRFRayTube *pRayTube)
{
	m_pRayTube = pRayTube;
	m_bOpen = FALSE;
}

// -----------------------------------------------------------------------------------------------------

CRayTubeDlg::~CRayTubeDlg()
{
	if(m_pRayTube)
	{
		m_pRayTube->Release();
		m_pRayTube = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

BOOL CRayTubeDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CRayTubeDlg::OnSetInfo(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pRayTube)
	{
		CString				strText;
		USHORT				uVoltage;
		USHORT				uCurrent;

		GetDlgItemText(IDC_VOLTAGE, strText);
		uVoltage = (USHORT)_tstoi(strText);

		GetDlgItemText(IDC_CURRENT, strText);
		uCurrent = (USHORT)_tstoi(strText);

		m_pRayTube->SetConfig(uVoltage, uCurrent);
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CRayTubeDlg::OnGetInfo(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pRayTube)
	{
		USHORT				uVoltage;
		USHORT				uCurrent;
		BOOL				bUncover;
		CString				strText;

		m_pRayTube->GetConfig(&uVoltage, &uCurrent, &bUncover, 5000);
		strText.Format(_T("%u"), uVoltage);
		SetDlgItemText(IDC_VOLTAGE, strText);
		
		strText.Format(_T("%u"), uCurrent);
		SetDlgItemText(IDC_CURRENT, strText);

		if(bUncover)
			MessageBox(_T("开盖中"));
		else
			MessageBox(_T("未开盖"));
	}
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CRayTubeDlg::OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pRayTube)
	{
		if(m_bOpen)
		{
			m_bOpen = FALSE;
			m_pRayTube->Close();
			SetDlgItemText(IDOK, _T("开启"));
		}
		else
		{
			m_bOpen = TRUE;
			m_pRayTube->Open();
			SetDlgItemText(IDOK, _T("关闭"));
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CRayTubeDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(IDCANCEL);
	return 0;
}
