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
		e_set_info = 0x19,  //���ù�����ѹ
		e_get_info = 0x22,  //��ȡ������ѹ
		e_operator = 0x16,
		e_ver = 0x10,		//!< �汾����
		e_xray_sel = 0x28,		//!���ΰеĿ���


		e_control_vacuum = 0x12,		//!< ������ձ��Ƿ���
		e_get_vacuum = 0x23,		//!< ��ȡ��ն�
		e_get_doublevacuum = 0x26,		//!< ��ȡ˫��ն�


		e_pushButton = 0x2E,      //��ȡ����״̬
		e_clearpushStatus = 0x1A,  //�������״̬


		e_control_HighVoltage = 0x11,		//!< ���Ƹ�ѹ�Ƿ���
		e_pilot_lamp_HighVoltage = 0x13,		//!< ���Ƹ�ѹָʾ���Ƿ���
		e_cover_HighVoltage = 0x18,		//!< �Ƿ������ǵ�����¿�����ѹ

		e_controlElectromagnetU = 0x14,					//!< ���Ƶ�����Ƿ��� ��ʱδ�õ�������
		e_controlElectromagnet = 0x15,					//!< ���Ƶ�����Ĺ����Ƿ���--->(�̼�ʵ�����ڵ����)
		e_controlLaser = 0x32,				//!< ���Ƹ߶ȼ����Ƿ���
		e_LaserMode = 0x34,				    //!< ���Ƹ߶ȼ����ģʽ
		e_control_SurfaceSource = 0x20,					//!< �������Դ

		e_control_Motor = 0x17,					//!< ���Ƶ��
		e_state_Motor = 0x21,					//!< ��ѯ״̬
		e_chamber = 0x29,					//!<��ȡ��Ʒ����Ϣ
		e_controlZAutoMoter = 0x33,			//!����Z���Զ�����
		e_switchinfo = 0x25,			   //!< ��ѯ��翪��״̬

	};

private:
	USHORT			m_uVoltage;
	USHORT			m_uCurrent;
	BOOL			m_bUncover;
	UINT			m_uCount;				//!< ��������Ϣͬ�������ü���
	Skyray::CLock	m_lock;					//!< ��������Ϣͬ�������ü�����ͬ����
	tstring			m_strError;				//!< ���յĴ���
	HANDLE			m_hNetWork;				//!< �û���ȡ����������Ϣ��ͬ��	

	UINT			m_vacuum;				//!< ��ն�		
	FLOAT			m_vacuumUp;				//!< ��ն�		
	FLOAT			m_vacuumDown;				//!< ��ն�	
	UCHAR			m_cPushButton;          //������Ϣ

	UCHAR			m_cState;
	UCHAR			m_cChamState[2];
	SHORT           m_info;            //��翪��״̬


public:
	//STDMETHOD(CheckVersion)(UINT* pVersion, UINT uTimeOut);
	//��ȡIIC�İ汾��
	STDMETHOD(CheckVersion)(UINT pVersion[], UINT uTimeOut);
	//���ΰ�
	STDMETHOD(bXRayTubeSel)(UINT index);
	//����
	STDMETHOD(GetPushButtonInfo)(UCHAR * pInfo, UINT uTimeOut);
	STDMETHOD(ClearPushButtonInfo)();
	//���
	STDMETHOD(GetDoubleVacuum)(UINT uType, UINT* pUpVacuum, UINT* pDownVacuum, UINT uTimeOut);//�����ӵ�ȡ˫��ն�2022-3-17
	STDMETHOD(OpenVacuumPump)(void);
	STDMETHOD(CloseVacuumPump)(void);
	STDMETHOD(GetVacuum)(UINT uType, UINT* pVacuum, UINT uTimeOut);
	//��ѹ
	STDMETHOD(OpenHighVoltage)(void);
	STDMETHOD(CloseHighVoltage)(void);
	STDMETHOD(GetConfig)(USHORT* pVoltage, USHORT* pCurrent, BOOL* pUncover, UINT uTimeOut);
	STDMETHOD(SetConfig)(USHORT uVoltage, USHORT uCurrent);
	STDMETHOD(AllowUncover)(void);
	STDMETHOD(ForbidUncover)(void);
	STDMETHOD(OpenPilotLamp)(void);
	STDMETHOD(ClosePilotLamp)(void);
	//�߶ȼ���
	STDMETHOD(OpenElectromagnet)(void);//!���Ƶ�����Ĺ���(�̼�ʵ�����ڵ����)
	STDMETHOD(CloseElectromagnet)(void);//!���Ƶ�����Ĺ���(�̼�ʵ�����ڵ����)
	STDMETHOD(OpenLaserControl)(BYTE byteOpen);//!< ���Ƹ߶ȼ����Ƿ���
	STDMETHOD(SetLaserMode)(BYTE bManual);//����Ŀ���ģʽ
										  //���Դ
	STDMETHOD(SetSurfaceLight)(USHORT uFirstLight, USHORT uSecondLight, USHORT uThirdLight, USHORT uFourthLight);
	//���
	STDMETHOD(GetMotorState)(UCHAR *pState, UINT uTimeOut);
	STDMETHOD(MotorMove)(UCHAR cID, UCHAR cDirection, USHORT uStep, UCHAR cSwitch, UCHAR cRate, USHORT uDutyRatio, USHORT uChamberCoef2);
	STDMETHOD(GetChamberState)(UCHAR pState[], UINT pStateLen, UINT uTimeOut);
	STDMETHOD(MoveZAutoMotor)(UCHAR cRate);
	STDMETHOD(GetSwitchInfo)(SHORT* pInfo, UINT uTimeOut);

};

OBJECT_ENTRY_AUTO(__uuidof(XRFRay), CXRFRayTube)
