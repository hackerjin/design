// VacuumPump.h : Declaration of the CVacuumPump

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"
#include "IEndPoint.h"
#include "SkyrayLock.h"

// CVacuumPump
class ATL_NO_VTABLE CVacuumPump :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CVacuumPump, &CLSID_VacuumPump>,
	public IDispatchImpl<IVacuumPump, &IID_IVacuumPump, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::IEndPoint
{
public:
	CVacuumPump();

	DECLARE_REGISTRY_RESOURCEID(IDR_VACUUMPUMP)

	BEGIN_COM_MAP(CVacuumPump)
		COM_INTERFACE_ENTRY(IVacuumPump)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

private:
	UINT ID() { return e_vacuum_pump; }
	const TCHAR* Name() { return g_strVacuumPump.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

public:
	/*STDMETHOD(Open)(void);
	STDMETHOD(Close)(void);
	STDMETHOD(GetVacuum)(UINT uType, UINT* pVacuum,  UINT uTimeOut);*/
//public:
//	STDMETHOD(GetDoubleVacuum)(UINT uType,UINT* pUpVacuum, UINT* pDownVacuum, UINT uTimeOut);//�����ӵ�ȡ˫��ն�2012-10-31

private:
	enum
	{
		//e_control		= 0x12,		//!< ���Ƹ�ѹ�Ƿ���
		//e_get_vacuum	= 0x23,		//!< ��ȡ��ն�
		//e_get_doublevacuum	= 0x26,		//!< ��ȡ˫��ն�
	};

private:
	UINT			m_uCount;				//!< ��������Ϣͬ�������ü���
	Skyray::CLock	m_lock;					//!< ��������Ϣͬ�������ü�����ͬ����
	HANDLE			m_hNetWork;				//!< �û���ȡ����������Ϣ��ͬ��		
	UINT			m_vacuum;				//!< ��ն�		
	FLOAT			m_vacuumUp;				//!< ��ն�		
	FLOAT			m_vacuumDown;				//!< ��ն�		
	tstring			m_strError;				//<! ���յĴ���

};

OBJECT_ENTRY_AUTO(__uuidof(VacuumPump), CVacuumPump)
