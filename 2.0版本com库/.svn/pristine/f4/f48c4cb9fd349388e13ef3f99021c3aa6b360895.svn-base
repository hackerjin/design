// stdafx.cpp : source file that includes just the standard includes
// XRFNet.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "EventMgr.h"

HINSTANCE			g_hNetLib = NULL;
NetLib::INetKernel	*g_pNetKernel = NULL;
CEventMgr			g_eventMgr;

const UINT g_uLocalIICVersion = 2;
const UINT g_uLocalSPIVersion = 1;
UINT g_uIICVersion = 0;
UINT g_uSPIVersion = 0;

wchar_t g_acModulePath[MAX_PATH]	= L"\0";
const tstring g_strHighVoltage		= _T("高压控制器");
const tstring g_strVacuumPump		= _T("真空泵");
const tstring g_strXRayTube			= _T("X光管");
const tstring g_strMotorControl		= _T("电机");
const tstring g_strDetector			= _T("多道数据采集器");
const tstring g_strElectromagnet	= _T("电磁铁");
const tstring g_strHeightLaser		= _T("高度激光指示器");
const tstring g_strSurfaceSource	= _T("面光源控制器");
const tstring g_strApparatus		= _T("下位机");
const tstring g_strIICControl		= _T("IIC控制器");