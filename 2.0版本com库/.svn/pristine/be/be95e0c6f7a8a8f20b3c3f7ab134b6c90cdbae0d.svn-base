#include "StdAfx.h"
#include "MotorDlg.h"

// -----------------------------------------------------------------------------------------------------

CMotorDlg::CMotorDlg(IMotorControl *pMotorControl)
{
	m_pMotorControl = pMotorControl;;
}

// -----------------------------------------------------------------------------------------------------

CMotorDlg::~CMotorDlg()
{
	if(m_pMotorControl)
	{
		m_pMotorControl->Release();
		m_pMotorControl = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

BOOL CMotorDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMotorDlg::OnQuery(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pMotorControl)
	{
		UCHAR			cState;

		if(SUCCEEDED(m_pMotorControl->GetState(&cState, 5000)))
		{
			if(0 == cState)
				MessageBox(_T("电机空闲"));
			else
				MessageBox(_T("电机繁忙"));
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMotorDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pMotorControl)
	{
		CString				strText;
		UCHAR				cID;
		UCHAR				cDirection;
		USHORT				uStep;
		UCHAR				cSwitch;
		UCHAR				cRate;

		GetDlgItemText(IDC_ID, strText);
		cID = (UCHAR)_tstoi(strText);

		GetDlgItemText(IDC_DIRECTION, strText);
		cDirection = (UCHAR)_tstoi(strText);

		GetDlgItemText(IDC_STEP, strText);
		uStep = (USHORT)_tstoi(strText);

		GetDlgItemText(IDC_SWITCH, strText);
		cSwitch = (UCHAR)_tstoi(strText);

		GetDlgItemText(IDC_RATE, strText);
		cRate = (UCHAR)_tstoi(strText);

		m_pMotorControl->Move(cID, cDirection, uStep, cSwitch, cRate,0);
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CMotorDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(IDCANCEL);
	return 0;
}
