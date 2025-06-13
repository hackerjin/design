// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
using namespace ATL;

#include <string>
#include <vector>
#include <list>

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#include "INetKernel.h"
#include <windows.h>

class CEventMgr;

extern wchar_t g_acModulePath[MAX_PATH];		//!< ģ��������ȫ·��

extern HINSTANCE g_hNetLib;						//!< ͨѶDLL��ʵ�����
extern NetLib::INetKernel *g_pNetKernel;		//!< ͨѶϵͳ�����ӿ�
extern CEventMgr g_eventMgr;					//!< �¼�������

extern const UINT g_uLocalIICVersion;			//!< ����IIC�İ汾��
extern const UINT g_uLocalSPIVersion;			//!< ���ض�����ݲɼ����İ汾��
extern UINT	g_uIICVersion;						//!< IIC�İ汾��
extern UINT g_uSPIVersion;						//!< ������ݲɼ����İ汾��


enum EndPointType
{
	e_high_voltage = 0x0001,		//!< ��ѹ������
	e_vacuum_pump = 0x0002,			//!< ��ձ�
	e_x_ray_tube = 0x0003,			//!< X���
	e_motor_control = 0x0004,		//!< ���
	e_multi_channel_data = 0x0005,	//!< ������ݲɼ���  1.spi̽��������
	e_electromagnet = 0x0006,		//!< �����
	e_height_laser = 0x0007,		//!< �߶ȼ���
	e_surface_source = 0x0008,		//!< ���Դ
	e_apparatus = 0x000B,			//!< ��λ��ϵͳ   2 ARm��������
	e_iic = 0x0011,					//!< IIC������  3 iic ������
};

extern const tstring g_strHighVoltage;
extern const tstring g_strVacuumPump;
extern const tstring g_strXRayTube;
extern const tstring g_strMotorControl;
extern const tstring g_strDetector;
extern const tstring g_strElectromagnet;
extern const tstring g_strHeightLaser;
extern const tstring g_strSurfaceSource;
extern const tstring g_strApparatus;
extern const tstring g_strIICControl;
