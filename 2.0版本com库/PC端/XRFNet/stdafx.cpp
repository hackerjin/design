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
const tstring g_strHighVoltage		= _T("��ѹ������");
const tstring g_strVacuumPump		= _T("��ձ�");
const tstring g_strXRayTube			= _T("X���");
const tstring g_strMotorControl		= _T("���");
const tstring g_strDetector			= _T("������ݲɼ���");
const tstring g_strElectromagnet	= _T("�����");
const tstring g_strHeightLaser		= _T("�߶ȼ���ָʾ��");
const tstring g_strSurfaceSource	= _T("���Դ������");
const tstring g_strApparatus		= _T("��λ��");
const tstring g_strIICControl		= _T("IIC������");