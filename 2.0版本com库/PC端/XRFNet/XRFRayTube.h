// XRFRay.h : Declaration of the CXRFRay

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"
#include "IEndPoint.h"
#include "SkyrayLock.h"

// CXRFRay
class ATL_NO_VTABLE CXRFRayTube :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CXRFRayTube, &CLSID_XRFRay>,
	public IDispatchImpl<IXRFRayTube, &IID_IXRFRayTube, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::IEndPoint
{
public:
	CXRFRayTube();
	~CXRFRayTube();

	DECLARE_REGISTRY_RESOURCEID(IDR_XRFRAY)

	BEGIN_COM_MAP(CXRFRayTube)
		COM_INTERFACE_ENTRY(IXRFRayTube)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

public:
	STDMETHOD(Open)(void);
	STDMETHOD(Close)(void);



private:
	UINT ID() { return e_x_ray_tube; }
	const TCHAR* Name() { return g_strXRayTube.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

	int m_uIICVersion[4];


private:
	enum
	{
		e_set_info = 0x19,  //设置管流管压
		e_get_info = 0x22,  //获取管流管压
		e_operator = 0x16,
		e_ver = 0x10,		//!< 版本控制
		e_xray_sel = 0x28,		//!二次靶的开关


		e_control_vacuum = 0x12,		//!< 控制真空泵是否开启
		e_get_vacuum = 0x23,		//!< 获取真空度
		e_get_doublevacuum = 0x26,		//!< 获取双真空度


		e_pushButton = 0x2E,      //获取按键状态
		e_clearpushStatus = 0x1A,  //清除按键状态


		e_control_HighVoltage = 0x11,		//!< 控制高压是否开启
		e_pilot_lamp_HighVoltage = 0x13,		//!< 控制高压指示灯是否开启
		e_cover_HighVoltage = 0x18,		//!< 是否允许开盖的情况下开启高压

		e_controlElectromagnetU = 0x14,					//!< 控制电磁铁是否开启 暂时未用到不整理
		e_controlElectromagnet = 0x15,					//!< 控制电磁铁的功能是否开启--->(固件实际用在电磁铁)
		e_controlLaser = 0x32,				//!< 控制高度激光是否开启
		e_LaserMode = 0x34,				    //!< 控制高度激光的模式
		e_control_SurfaceSource = 0x20,					//!< 设置面光源

		e_control_Motor = 0x17,					//!< 控制电机
		e_state_Motor = 0x21,					//!< 查询状态
		e_chamber = 0x29,					//!<获取样品杯信息
		e_controlZAutoMoter = 0x33,			//!控制Z轴自动调节
		e_switchinfo = 0x25,			   //!< 查询光电开关状态

	};

private:
	USHORT			m_uVoltage;
	USHORT			m_uCurrent;
	BOOL			m_bUncover;
	UINT			m_uCount;				//!< 服务器信息同步的引用计数
	Skyray::CLock	m_lock;					//!< 服务器信息同步的引用计数的同步锁
	tstring			m_strError;				//!< 最终的错误
	HANDLE			m_hNetWork;				//!< 用户获取服务器端信息的同步	

	UINT			m_vacuum;				//!< 真空度		
	FLOAT			m_vacuumUp;				//!< 真空度		
	FLOAT			m_vacuumDown;				//!< 真空度	
	UCHAR			m_cPushButton;          //按键信息

	UCHAR			m_cState;
	UCHAR			m_cChamState[2];
	SHORT           m_info;            //光电开关状态


public:
	//STDMETHOD(CheckVersion)(UINT* pVersion, UINT uTimeOut);
	//获取IIC的版本号
	STDMETHOD(CheckVersion)(UINT pVersion[], UINT uTimeOut);
	//二次靶
	STDMETHOD(bXRayTubeSel)(UINT index);
	//按键
	STDMETHOD(GetPushButtonInfo)(UCHAR * pInfo, UINT uTimeOut);
	STDMETHOD(ClearPushButtonInfo)();
	//真空
	STDMETHOD(GetDoubleVacuum)(UINT uType, UINT* pUpVacuum, UINT* pDownVacuum, UINT uTimeOut);//新增加的取双真空度2022-3-17
	STDMETHOD(OpenVacuumPump)(void);
	STDMETHOD(CloseVacuumPump)(void);
	STDMETHOD(GetVacuum)(UINT uType, UINT* pVacuum, UINT uTimeOut);
	//高压
	STDMETHOD(OpenHighVoltage)(void);
	STDMETHOD(CloseHighVoltage)(void);
	STDMETHOD(GetConfig)(USHORT* pVoltage, USHORT* pCurrent, BOOL* pUncover, UINT uTimeOut);
	STDMETHOD(SetConfig)(USHORT uVoltage, USHORT uCurrent);
	STDMETHOD(AllowUncover)(void);
	STDMETHOD(ForbidUncover)(void);
	STDMETHOD(OpenPilotLamp)(void);
	STDMETHOD(ClosePilotLamp)(void);
	//高度激光
	STDMETHOD(OpenElectromagnet)(void);//!控制电磁铁的功能(固件实际用在电磁铁)
	STDMETHOD(CloseElectromagnet)(void);//!控制电磁铁的功能(固件实际用在电磁铁)
	STDMETHOD(OpenLaserControl)(BYTE byteOpen);//!< 控制高度激光是否开启
	STDMETHOD(SetLaserMode)(BYTE bManual);//激光的开启模式
										  //面光源
	STDMETHOD(SetSurfaceLight)(USHORT uFirstLight, USHORT uSecondLight, USHORT uThirdLight, USHORT uFourthLight);
	//电机
	STDMETHOD(GetMotorState)(UCHAR *pState, UINT uTimeOut);
	STDMETHOD(MotorMove)(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate, USHORT uDutyRatio, USHORT uChamberCoef2);
	STDMETHOD(GetChamberState)(UCHAR pState[], UINT pStateLen, UINT uTimeOut);
	STDMETHOD(MoveZAutoMotor)(UCHAR cRate);
	STDMETHOD(GetSwitchInfo)(SHORT* pInfo, UINT uTimeOut);

};

OBJECT_ENTRY_AUTO(__uuidof(XRFRay), CXRFRayTube)
