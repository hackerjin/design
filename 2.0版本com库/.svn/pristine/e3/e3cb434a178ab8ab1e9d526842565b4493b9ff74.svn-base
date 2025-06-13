// MotorControl.h : Declaration of the CMotorControl

#pragma once
#include "resource.h"       // main symbols

#include "XRFNet_i.h"
#include "IEndPoint.h"
#include "SkyrayLock.h"

// CMotorControl
class ATL_NO_VTABLE CMotorControl :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMotorControl, &CLSID_MotorControl>,
	public IDispatchImpl<IMotorControl, &IID_IMotorControl, &LIBID_XRFNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public NetLib::IEndPoint
{
public:
	CMotorControl()
	{
		m_hNetWork = NULL;
		m_cState = 0;
		m_uCount = 0;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MOTORCONTROL)

	BEGIN_COM_MAP(CMotorControl)
		COM_INTERFACE_ENTRY(IMotorControl)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

private:
	UINT ID() { return e_motor_control; }
	const TCHAR* Name() { return g_strMotorControl.c_str(); }
	BOOL IsRelay() { return TRUE; }
	void OnReceive(NetLib::TransportID eID, NetLib::IUnpacking *pUnpacking);
	const TCHAR* GetLastError() { return m_strError.c_str(); }
	void Destroy() {}

//public:
//	STDMETHOD(GetState)(UCHAR *pState, UINT uTimeOut);
//	//STDMETHOD(Move)(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate);
//
//	//STDMETHOD(Move)(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate,USHORT uDutyRatio);
//	STDMETHOD(Move)(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate,USHORT uDutyRatio,USHORT uChamberCoef2);

//private:
//	enum
//	{
//		e_control	= 0x17,					//!< 控制电机
//		e_state		= 0x21,					//!< 查询状态
//		e_chamber   = 0x29,					//!<获取样品杯信息
//		e_controlZAutoMoter=0x33,			//!控制Z轴自动调节
//		e_switchinfo  = 0x25,			   //!< 查询光电开关状态
//		//e_pushButton = 0x2E,      //获取按键状态
//		//e_clearpushStatus = 0x1A,  //清除按键状态
//	};

private:
	tstring			m_strError;				//<! 最终的错误
	HANDLE			m_hNetWork;				//<! 用户获取服务器端信息的同步
	UINT			m_uCount;				//<! 服务器信息同步的引用计数
	Skyray::CLock	m_lock;					//<! 服务器信息同步的引用计数的同步锁
	UCHAR			m_cState;	
	UCHAR			m_cChamState[2];
	SHORT           m_info;            //光电开关状态
    /*UCHAR			m_cPushButton;*/
//public:
	//STDMETHOD(GetChamberState)(UCHAR pState[], UINT pStateLen, UINT uTimeOut);
	//STDMETHOD(MoveZAutoMotor)(UCHAR cRate);
	//STDMETHOD(GetSwitchInfo)(SHORT* pInfo, UINT uTimeOut);
	////STDMETHOD(GetPushButtonInfo)(UCHAR * pInfo, UINT uTimeOut);
 ////   STDMETHOD(ClearPushButtonInfo)();


};

OBJECT_ENTRY_AUTO(__uuidof(MotorControl), CMotorControl)
