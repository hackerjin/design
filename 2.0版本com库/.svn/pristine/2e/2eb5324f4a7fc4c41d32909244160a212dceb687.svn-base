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
		e_begin		= 0x1,		//!< 开始读谱
		e_config	= 0x3,		//!< 配置数据采集器
		e_ver		= 0x2,		//!< 版本控制

		e_dpp100Parameter	= 0x5,     //!< dpp100设置参数
		e_dpp100GetDatas	= 0x6,	   //!< dpp100取值
	};

	struct DataInfo
	{
		UINT		m_uQuickCount;	//!< 快成形个数
		UINT		m_uSlowCount;	//!< 慢成形个数
		UINT		m_uSystemTime;	//!< 系统时间
		UINT		m_uLocalTime;	//!< 本地时间
		USHORT*		m_pData;		//!< 采集的数据
		USHORT		m_uDataLen;		//!< 采集的数据的长度
	};

private:
	IDetectorCallBack*	m_pCallback;	//!< 回调接口
	tstring				m_strError;		//!< 最终的错误	
	USHORT				m_uCount;		//!< 多道数据采集器的道数
	UINT				m_uSignalCount;	//<! 服务器信息同步的引用计数
	Skyray::CLock		m_lock;			//<! 服务器信息同步的引用计数的同步锁
	HANDLE				m_hNetWork;		//!< 用户获取服务器端信息的同步
	BOOL				m_bGetVersion;	//!< 是否在等待获取版本信息数据

	char				m_byteBuffers[16386];//Dpp100取值缓存
	USHORT				m_buferLen;
	BOOL                m_bDMCACatch;
public:
	STDMETHOD(SetDpp100Parameter)(BYTE byteDpp100Cmd[], SHORT intCmdLen);
	STDMETHOD(GetDpp100Datas)(BYTE byteDpp100Cmd[], SHORT intDpp100CmdLen,UINT uTimeOut, BYTE byteGetBytes[],SHORT* intGetBytesLen);
	STDMETHOD(GetDMCADatas)(UINT uTimeOut,BYTE shortGetSHORTS[],SHORT* intGetBytesLen);
};

OBJECT_ENTRY_AUTO(__uuidof(Detector), CDetector)
