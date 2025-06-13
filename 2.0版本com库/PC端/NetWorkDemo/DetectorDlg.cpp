#include "StdAfx.h"
#include "DetectorDlg.h"

// -----------------------------------------------------------------------------------------------------

CDetectorDlg::CDetectorDlg(IDetector *pDetector) : m_cb(this)
{
	m_pDetector = pDetector;
	if(m_pDetector)
		m_pDetector->SetCallback(&m_cb);
	m_bOpen = FALSE;
}

// -----------------------------------------------------------------------------------------------------

CDetectorDlg::~CDetectorDlg()
{
	if(!m_pDetector)
	{
		m_pDetector->SetCallback(NULL);
		m_pDetector->Release();
	}
}

// -----------------------------------------------------------------------------------------------------

BOOL CDetectorDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	CComboBox			rateCtrl = GetDlgItem(IDC_RATE);
	
	rateCtrl.AddString(_T("20M"));
	rateCtrl.AddString(_T("80M"));
	rateCtrl.SetCurSel(0);
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

void CDetectorDlg::OnRead(UINT uQuickCount, UINT uSlowCount, UINT uSystemTime, UINT uLocalTime, const USHORT *pData, USHORT uLen)
{
	if(IsWindow())
	{
		CEdit				dataCtrl = GetDlgItem(IDC_DATA);
		tstring				strText = _T("");
		tstring				strLine = _T("");
		TCHAR				acBuf[8];
		UINT				uCount = 0;

		for(UINT i=0; i<uLen; i++)
		{
			if(0 == strLine.length())
				_stprintf_s(acBuf, 7, _T("%04x"), pData[i]);
			else
				_stprintf_s(acBuf, 7, _T(" %04x"), pData[i]);

			strLine += acBuf;
			uCount++;

			if(uCount >= 32)
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
			dataCtrl.SetWindowText(strText.c_str());
	}
}

// -----------------------------------------------------------------------------------------------------

LRESULT CDetectorDlg::OnConfig(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pDetector)
	{
		CComboBox			rateCtrl = GetDlgItem(IDC_RATE);
		CButton				checkCtrl;
		CString				strText;
		UCHAR				cBaseResume;
		UCHAR				cBaseLimit;
		UCHAR				cHeapUp;
		UCHAR				cRate;
		UCHAR				cCoarse;
		USHORT				uFine;
		USHORT				uTime;
		UCHAR				cUpTime;
		UCHAR				cWidthTime;
		UCHAR				cSlowLimit;

		checkCtrl = GetDlgItem(IDC_BASE_RESUME);
		if(checkCtrl.GetCheck())
		cBaseResume = (UCHAR)_tstoi(strText);

		GetDlgItemText(IDC_BASE_LIMIT, strText);
		cBaseLimit = (UCHAR)_tstoi(strText);
		
		GetDlgItemText(IDC_HEAP_UP, strText);
		cHeapUp = (UCHAR)_tstoi(strText);
		
		cRate = (UCHAR)rateCtrl.GetCurSel();

		GetDlgItemText(IDC_COARSE, strText);
		cCoarse = (UCHAR)_tstoi(strText);
		
		GetDlgItemText(IDC_FINE, strText);
		uFine = (USHORT)_tstoi(strText);

		GetDlgItemText(IDC_TIME, strText);
		uTime = (USHORT)_tstoi(strText);
		
		GetDlgItemText(IDC_UP_TIME, strText);
		cUpTime = (UCHAR)_tstoi(strText);

		GetDlgItemText(IDC_WIDTH_TIME, strText);
		cWidthTime = (UCHAR)_tstoi(strText);

		GetDlgItemText(IDC_SLOW_LIMIT, strText);
		cSlowLimit = (UCHAR)_tstoi(strText);

		m_pDetector->Config(cBaseResume, cBaseLimit, cHeapUp, cRate, cCoarse, uFine, uTime, cUpTime, cWidthTime, cSlowLimit,0.f);
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CDetectorDlg::OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pDetector)
		m_pDetector->BeginRead();
	
	return 0;
}

// -----------------------------------------------------------------------------------------------------

LRESULT CDetectorDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(IDCANCEL);
	return 0;
}
