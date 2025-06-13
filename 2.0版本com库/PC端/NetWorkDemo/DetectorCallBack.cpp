#include "StdAfx.h"
#include "DetectorCallBack.h"
#include "DetectorDlg.h"

// -----------------------------------------------------------------------------------------------------

CDetectorCallBack::CDetectorCallBack(CDetectorDlg *pDetectorDlg)
{
	m_pDetectorDlg = pDetectorDlg;
}

// -----------------------------------------------------------------------------------------------------

CDetectorCallBack::~CDetectorCallBack()
{

}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CDetectorCallBack::QueryInterface(const struct _GUID& iid,void** ppv)
{
	if(iid == IID_INetworkCallBack)
	{
		*ppv=this;
		return S_OK;
	}

	return S_FALSE;
}

// -----------------------------------------------------------------------------------------------------

ULONG __stdcall CDetectorCallBack::AddRef()
{
	//仅仅为了测试，此处为权宜之策，因为反正这个对象在程序结束前是不会退出的
	return 1;
}

// -----------------------------------------------------------------------------------------------------

ULONG __stdcall CDetectorCallBack::Release()
{
	//仅仅为了测试，此处为权宜之策，因为反正这个对象在程序结束前是不会退出的
	return 0;	
}

// -----------------------------------------------------------------------------------------------------

HRESULT __stdcall CDetectorCallBack::OnRead(UINT uQuickCount, UINT uSlowCount, UINT uSystemTime, UINT uLocalTime, IDetectData *pData)
{
	USHORT		uCount;
	USHORT		uData;
	int			k = 0;
	
	pData->Count(&uCount);
	for(USHORT i=0; i<uCount; i++)
	{
		pData->At(i, &uData);
		k++;
	}
	return S_OK;
}