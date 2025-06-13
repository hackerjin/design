#pragma once

#include "XRFNet_i.h"

class CDetectorDlg;
class CDetectorCallBack : public IDetectorCallBack
{
public:
	CDetectorCallBack(CDetectorDlg *pDetectorDlg);
	~CDetectorCallBack(void);

	HRESULT __stdcall QueryInterface(const struct _GUID& iid,void** ppv);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall OnRead(UINT uQuickCount, UINT uSlowCount, UINT uSystemTime, UINT uLocalTime, IDetectData *pData);

private:
	CDetectorDlg	*m_pDetectorDlg;
};
