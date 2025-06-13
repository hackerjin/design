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

extern wchar_t g_acModulePath[MAX_PATH];		//!< 模块所处的全路径

extern HINSTANCE g_hNetLib;						//!< 通讯DLL的实例句柄
extern NetLib::INetKernel *g_pNetKernel;		//!< 通讯系统的主接口
extern CEventMgr g_eventMgr;					//!< 事件管理器

extern const UINT g_uLocalIICVersion;			//!< 本地IIC的版本号
extern const UINT g_uLocalSPIVersion;			//!< 本地多道数据采集器的版本号
extern UINT	g_uIICVersion;						//!< IIC的版本号
extern UINT g_uSPIVersion;						//!< 多道数据采集器的版本号


enum EndPointType
{
	e_high_voltage = 0x0001,		//!< 高压控制器
	e_vacuum_pump = 0x0002,			//!< 真空泵
	e_x_ray_tube = 0x0003,			//!< X光管
	e_motor_control = 0x0004,		//!< 电机
	e_multi_channel_data = 0x0005,	//!< 多道数据采集器  1.spi探测器数据
	e_electromagnet = 0x0006,		//!< 电磁铁
	e_height_laser = 0x0007,		//!< 高度激光
	e_surface_source = 0x0008,		//!< 面光源
	e_apparatus = 0x000B,			//!< 下位机系统   2 ARm参数设置
	e_iic = 0x0011,					//!< IIC控制器  3 iic 及其他
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
