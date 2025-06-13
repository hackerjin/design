#include "StdAfx.h"
#include "SurfaceSourceDlg.h"

// -----------------------------------------------------------------------------------------------------

CSurfaceSourceDlg::CSurfaceSourceDlg(ISurfaceSource *pSurfaceSource)
{
	m_pSurfaceSource = pSurfaceSource;
}

// -----------------------------------------------------------------------------------------------------

CSurfaceSourceDlg::~CSurfaceSourceDlg()
{
	if(m_pSurfaceSource)
	{
		m_pSurfaceSource->Release();
		m_pSurfaceSource = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

BOOL CSurfaceSourceDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CSurfaceSourceDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pSurfaceSource)
	{
		CString				strText;
		USHORT				uFirstLight;
		USHORT				uSecondLight;

		GetDlgItemText(IDC_FRIST_LIGHT, strText);
		uFirstLight = (USHORT)_tstoi(strText);

		GetDlgItemText(IDC_SECOND_LIGHT, strText);
		uSecondLight = (USHORT)_tstoi(strText);

		m_pSurfaceSource->SetLight(uFirstLight, uSecondLight, uFirstLight, uSecondLight);
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CSurfaceSourceDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(IDCANCEL);
	return 0;
}
