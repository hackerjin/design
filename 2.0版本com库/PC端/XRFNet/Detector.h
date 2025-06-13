// DetectorDlg.h : Declaration of the CDetectorDlg

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"
#include "IEndPoint.h"
#include "EventMgr.h"
#include "SkyrayLock.h"

// CDetectorDlg
class ATL_NO_VTABLE CDetector :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDetector, &CLSID_Detector>,
	public IDispatchImpl<IDetector, &IID_IDetector, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::IEndPoint,
	public IEventListener
{
public:
	CDetector();

	DECLARE_REGISTRY_RESOURCEID(IDR_DETECTORDLG)

	BEGIN_COM_MAP(CDetector)
		COM_INTERFACE_ENTRY(IDetector)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

private:
	UINT ID() { return e_multi_channel_data; }
	const TCHAR* Name() { return g_strDetector.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

public:
	STDMETHOD(BeginRead)(void);
	//STDMETHOD(Config)(UCHAR cBaseResume, UCHAR cBaseLimit, UCHAR cHeapUP, UCHAR cRate, UCHAR cCoarse, UINT uFine, UINT uTime, UCHAR cUPTime, UCHAR cWidthTime, UCHAR cSlowLimit);
	STDMETHOD(Config)(UCHAR cBaseResume, UCHAR cBaseLimit, UCHAR cHeapUP, UCHAR cRate, UCHAR cCoarse, UINT uFine, UINT uTime, UCHAR cUPTime, UCHAR cWidthTime, UCHAR cSlowLimit,double dEnCoef);
	STDMETHOD(SetChannelCount)(USHORT uCount);
	STDMETHOD(SetCallback)(IDetectorCallBack* pCallback);
	STDMETHOD(CheckVersion)(BOOL *pCanUse, UINT uTimeOut);

private:
	void Procedure(LPCTSTR lpEventName, WPARAM wParam, LPARAM lParam);

private:
	enum
	{
		e_begin		= 0x1,		//!< ��ʼ����
		e_config	= 0x3,		//!< �������ݲɼ���
		e_ver		= 0x2,		//!< �汾����

		e_dpp100Parameter	= 0x5,     //!< dpp100���ò���
		e_dpp100GetDatas	= 0x6,	   //!< dpp100ȡֵ
	};

	struct DataInfo
	{
		UINT		m_uQuickCount;	//!< ����θ���
		UINT		m_uSlowCount;	//!< �����θ���
		UINT		m_uSystemTime;	//!< ϵͳʱ��
		UINT		m_uLocalTime;	//!< ����ʱ��
		USHORT*		m_pData;		//!< �ɼ�������
		USHORT		m_uDataLen;		//!< �ɼ������ݵĳ���
	};

private:
	IDetectorCallBack*	m_pCallback;	//!< �ص��ӿ�
	tstring				m_strError;		//!< ���յĴ���	
	USHORT				m_uCount;		//!< ������ݲɼ����ĵ���
	UINT				m_uSignalCount;	//<! ��������Ϣͬ�������ü���
	Skyray::CLock		m_lock;			//<! ��������Ϣͬ�������ü�����ͬ����
	HANDLE				m_hNetWork;		//!< �û���ȡ����������Ϣ��ͬ��
	BOOL				m_bGetVersion;	//!< �Ƿ��ڵȴ���ȡ�汾��Ϣ����

	char				m_byteBuffers[16386];//Dpp100ȡֵ����
	USHORT				m_buferLen;
	BOOL                m_bDMCACatch;
public:
	STDMETHOD(SetDpp100Parameter)(BYTE byteDpp100Cmd[], SHORT intCmdLen);
	STDMETHOD(GetDpp100Datas)(BYTE byteDpp100Cmd[], SHORT intDpp100CmdLen,UINT uTimeOut, BYTE byteGetBytes[],SHORT* intGetBytesLen);
	STDMETHOD(GetDMCADatas)(UINT uTimeOut,BYTE shortGetSHORTS[],SHORT* intGetBytesLen);
};

OBJECT_ENTRY_AUTO(__uuidof(Detector), CDetector)
