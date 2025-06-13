#include "StdAfx.h"
#include "HighVoltageDlg.h"

// -----------------------------------------------------------------------------------------------------

CHighVoltageDlg::CHighVoltageDlg(IHighVoltage *pHighVoltage)
{
	m_pHighVoltage = pHighVoltage;
	m_bOpen = FALSE;
	m_bOpenPilot = FALSE;
}

// -----------------------------------------------------------------------------------------------------

CHighVoltageDlg::~CHighVoltageDlg()
{
	if(m_pHighVoltage)
	{
		m_pHighVoltage->Release();
		m_pHighVoltage = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

BOOL CHighVoltageDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	CComboBox			coverTypeCtrl = GetDlgItem(IDC_COVER);

	coverTypeCtrl.AddString(_T("允许开盖开高压"));
	coverTypeCtrl.AddString(_T("严禁开盖开高压"));
	coverTypeCtrl.SetCurSel(0);
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CHighVoltageDlg::OnSetType(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pHighVoltage)
	{
		CComboBox			coverTypeCtrl = GetDlgItem(IDC_COVER);

		if(0 == coverTypeCtrl.GetCurSel())
			m_pHighVoltage->AllowUncover();
		else
			m_pHighVoltage->ForbidUncover();
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CHighVoltageDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pHighVoltage)
	{
		if(m_bOpen)
		{
			m_bOpen = FALSE;
			m_pHighVoltage->Close();
			SetDlgItemText(IDOK, _T("开启高压"));
		}
		else
		{
			m_bOpen = TRUE;
			m_pHighVoltage->Open();
			SetDlgItemText(IDOK, _T("关闭高压"));
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CHighVoltageDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(IDCANCEL);
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CHighVoltageDlg::OnBnClickedPilot(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pHighVoltage)
	{
		if(m_bOpenPilot)
		{
			m_bOpenPilot = FALSE;
			m_pHighVoltage->ClosePilotLamp();
			SetDlgItemText(IDC_PILOT, _T("开启高压指示灯"));
		}
		else
		{
			m_bOpenPilot = TRUE;
			m_pHighVoltage->OpenPilotLamp();
			SetDlgItemText(IDC_PILOT, _T("关闭高压指示灯"));
		}
	}

	return 0;
}
