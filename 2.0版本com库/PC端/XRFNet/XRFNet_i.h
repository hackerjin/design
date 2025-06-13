

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Apr 27 08:55:30 2025
 */
/* Compiler settings for XRFNet.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __XRFNet_i_h__
#define __XRFNet_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IXRFRayTube_FWD_DEFINED__
#define __IXRFRayTube_FWD_DEFINED__
typedef interface IXRFRayTube IXRFRayTube;

#endif 	/* __IXRFRayTube_FWD_DEFINED__ */


#ifndef __IHighVoltage_FWD_DEFINED__
#define __IHighVoltage_FWD_DEFINED__
typedef interface IHighVoltage IHighVoltage;

#endif 	/* __IHighVoltage_FWD_DEFINED__ */


#ifndef __IVacuumPump_FWD_DEFINED__
#define __IVacuumPump_FWD_DEFINED__
typedef interface IVacuumPump IVacuumPump;

#endif 	/* __IVacuumPump_FWD_DEFINED__ */


#ifndef __IMotorControl_FWD_DEFINED__
#define __IMotorControl_FWD_DEFINED__
typedef interface IMotorControl IMotorControl;

#endif 	/* __IMotorControl_FWD_DEFINED__ */


#ifndef __IElectromagnet_FWD_DEFINED__
#define __IElectromagnet_FWD_DEFINED__
typedef interface IElectromagnet IElectromagnet;

#endif 	/* __IElectromagnet_FWD_DEFINED__ */


#ifndef __IHeightLaser_FWD_DEFINED__
#define __IHeightLaser_FWD_DEFINED__
typedef interface IHeightLaser IHeightLaser;

#endif 	/* __IHeightLaser_FWD_DEFINED__ */


#ifndef __ISurfaceSource_FWD_DEFINED__
#define __ISurfaceSource_FWD_DEFINED__
typedef interface ISurfaceSource ISurfaceSource;

#endif 	/* __ISurfaceSource_FWD_DEFINED__ */


#ifndef __IDetectData_FWD_DEFINED__
#define __IDetectData_FWD_DEFINED__
typedef interface IDetectData IDetectData;

#endif 	/* __IDetectData_FWD_DEFINED__ */


#ifndef __IDetectorCallBack_FWD_DEFINED__
#define __IDetectorCallBack_FWD_DEFINED__
typedef interface IDetectorCallBack IDetectorCallBack;

#endif 	/* __IDetectorCallBack_FWD_DEFINED__ */


#ifndef __IDetector_FWD_DEFINED__
#define __IDetector_FWD_DEFINED__
typedef interface IDetector IDetector;

#endif 	/* __IDetector_FWD_DEFINED__ */


#ifndef __INetworkCallBack_FWD_DEFINED__
#define __INetworkCallBack_FWD_DEFINED__
typedef interface INetworkCallBack INetworkCallBack;

#endif 	/* __INetworkCallBack_FWD_DEFINED__ */


#ifndef __IApparatus_FWD_DEFINED__
#define __IApparatus_FWD_DEFINED__
typedef interface IApparatus IApparatus;

#endif 	/* __IApparatus_FWD_DEFINED__ */


#ifndef __IXRFNetwork_FWD_DEFINED__
#define __IXRFNetwork_FWD_DEFINED__
typedef interface IXRFNetwork IXRFNetwork;

#endif 	/* __IXRFNetwork_FWD_DEFINED__ */


#ifndef __XRFRay_FWD_DEFINED__
#define __XRFRay_FWD_DEFINED__

#ifdef __cplusplus
typedef class XRFRay XRFRay;
#else
typedef struct XRFRay XRFRay;
#endif /* __cplusplus */

#endif 	/* __XRFRay_FWD_DEFINED__ */


#ifndef __HighVoltage_FWD_DEFINED__
#define __HighVoltage_FWD_DEFINED__

#ifdef __cplusplus
typedef class HighVoltage HighVoltage;
#else
typedef struct HighVoltage HighVoltage;
#endif /* __cplusplus */

#endif 	/* __HighVoltage_FWD_DEFINED__ */


#ifndef __VacuumPump_FWD_DEFINED__
#define __VacuumPump_FWD_DEFINED__

#ifdef __cplusplus
typedef class VacuumPump VacuumPump;
#else
typedef struct VacuumPump VacuumPump;
#endif /* __cplusplus */

#endif 	/* __VacuumPump_FWD_DEFINED__ */


#ifndef __MotorControl_FWD_DEFINED__
#define __MotorControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class MotorControl MotorControl;
#else
typedef struct MotorControl MotorControl;
#endif /* __cplusplus */

#endif 	/* __MotorControl_FWD_DEFINED__ */


#ifndef __Electromagnet_FWD_DEFINED__
#define __Electromagnet_FWD_DEFINED__

#ifdef __cplusplus
typedef class Electromagnet Electromagnet;
#else
typedef struct Electromagnet Electromagnet;
#endif /* __cplusplus */

#endif 	/* __Electromagnet_FWD_DEFINED__ */


#ifndef __HeightLaser_FWD_DEFINED__
#define __HeightLaser_FWD_DEFINED__

#ifdef __cplusplus
typedef class HeightLaser HeightLaser;
#else
typedef struct HeightLaser HeightLaser;
#endif /* __cplusplus */

#endif 	/* __HeightLaser_FWD_DEFINED__ */


#ifndef __SurfaceSource_FWD_DEFINED__
#define __SurfaceSource_FWD_DEFINED__

#ifdef __cplusplus
typedef class SurfaceSource SurfaceSource;
#else
typedef struct SurfaceSource SurfaceSource;
#endif /* __cplusplus */

#endif 	/* __SurfaceSource_FWD_DEFINED__ */


#ifndef __DetectData_FWD_DEFINED__
#define __DetectData_FWD_DEFINED__

#ifdef __cplusplus
typedef class DetectData DetectData;
#else
typedef struct DetectData DetectData;
#endif /* __cplusplus */

#endif 	/* __DetectData_FWD_DEFINED__ */


#ifndef __Detector_FWD_DEFINED__
#define __Detector_FWD_DEFINED__

#ifdef __cplusplus
typedef class Detector Detector;
#else
typedef struct Detector Detector;
#endif /* __cplusplus */

#endif 	/* __Detector_FWD_DEFINED__ */


#ifndef __Apparatus_FWD_DEFINED__
#define __Apparatus_FWD_DEFINED__

#ifdef __cplusplus
typedef class Apparatus Apparatus;
#else
typedef struct Apparatus Apparatus;
#endif /* __cplusplus */

#endif 	/* __Apparatus_FWD_DEFINED__ */


#ifndef __XRFNetwork_FWD_DEFINED__
#define __XRFNetwork_FWD_DEFINED__

#ifdef __cplusplus
typedef class XRFNetwork XRFNetwork;
#else
typedef struct XRFNetwork XRFNetwork;
#endif /* __cplusplus */

#endif 	/* __XRFNetwork_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IXRFRayTube_INTERFACE_DEFINED__
#define __IXRFRayTube_INTERFACE_DEFINED__

/* interface IXRFRayTube */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IXRFRayTube;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B2018705-C2AE-4902-8BA5-0313921E3E0D")
    IXRFRayTube : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetConfig( 
            /* [out] */ USHORT *pVoltage,
            /* [out] */ USHORT *pCurrent,
            /* [out] */ BOOL *pUncover,
            /* [in] */ UINT uTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetConfig( 
            /* [in] */ USHORT uVoltage,
            /* [in] */ USHORT uCurrent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckVersion( 
            /* [out] */ UINT pVersion[ 4 ],
            /* [in] */ UINT uTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE bXRayTubeSel( 
            /* [in] */ UINT index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDoubleVacuum( 
            /* [in] */ UINT uType,
            /* [out] */ UINT *pUpVacuum,
            /* [out] */ UINT *pDownVacuum,
            UINT uTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPushButtonInfo( 
            /* [out] */ UCHAR *pState,
            /* [in] */ UINT uTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearPushButtonInfo( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenVacuumPump( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseVacuumPump( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVacuum( 
            /* [in] */ UINT uType,
            /* [out] */ UINT *pVacuum,
            /* [in] */ UINT uTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenHighVoltage( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseHighVoltage( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AllowUncover( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ForbidUncover( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenPilotLamp( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClosePilotLamp( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenElectromagnet( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseElectromagnet( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenLaserControl( 
            /* [in] */ BYTE byteOpen) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLaserMode( 
            /* [in] */ BYTE bManual) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSurfaceLight( 
            /* [in] */ USHORT uFirstLight,
            /* [in] */ USHORT uSecondLight,
            /* [in] */ USHORT uThirdLight,
            /* [in] */ USHORT uFourthLight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMotorState( 
            /* [out] */ UCHAR *pState,
            /* [in] */ UINT uTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MotorMove( 
            /* [in] */ UCHAR cID,
            /* [in] */ UCHAR cDirection,
            /* [in] */ USHORT uStep,
            /* [in] */ UCHAR cSwitch,
            /* [in] */ UCHAR cRate,
            /* [in] */ USHORT uDutyRatio,
            /* [in] */ USHORT uChamberCoef2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChamberState( 
            /* [out][in] */ UCHAR pState[ 2 ],
            /* [in] */ UINT pStateLen,
            /* [in] */ UINT uTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveZAutoMotor( 
            /* [in] */ UCHAR cRate) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSwitchInfo( 
            /* [out] */ SHORT *pInfo,
            UINT uTimeOut) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IXRFRayTubeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXRFRayTube * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXRFRayTube * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXRFRayTube * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXRFRayTube * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXRFRayTube * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXRFRayTube * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXRFRayTube * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetConfig )( 
            IXRFRayTube * This,
            /* [out] */ USHORT *pVoltage,
            /* [out] */ USHORT *pCurrent,
            /* [out] */ BOOL *pUncover,
            /* [in] */ UINT uTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetConfig )( 
            IXRFRayTube * This,
            /* [in] */ USHORT uVoltage,
            /* [in] */ USHORT uCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckVersion )( 
            IXRFRayTube * This,
            /* [out] */ UINT pVersion[ 4 ],
            /* [in] */ UINT uTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *bXRayTubeSel )( 
            IXRFRayTube * This,
            /* [in] */ UINT index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDoubleVacuum )( 
            IXRFRayTube * This,
            /* [in] */ UINT uType,
            /* [out] */ UINT *pUpVacuum,
            /* [out] */ UINT *pDownVacuum,
            UINT uTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPushButtonInfo )( 
            IXRFRayTube * This,
            /* [out] */ UCHAR *pState,
            /* [in] */ UINT uTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearPushButtonInfo )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenVacuumPump )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseVacuumPump )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVacuum )( 
            IXRFRayTube * This,
            /* [in] */ UINT uType,
            /* [out] */ UINT *pVacuum,
            /* [in] */ UINT uTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenHighVoltage )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseHighVoltage )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AllowUncover )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ForbidUncover )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenPilotLamp )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClosePilotLamp )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenElectromagnet )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseElectromagnet )( 
            IXRFRayTube * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenLaserControl )( 
            IXRFRayTube * This,
            /* [in] */ BYTE byteOpen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLaserMode )( 
            IXRFRayTube * This,
            /* [in] */ BYTE bManual);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSurfaceLight )( 
            IXRFRayTube * This,
            /* [in] */ USHORT uFirstLight,
            /* [in] */ USHORT uSecondLight,
            /* [in] */ USHORT uThirdLight,
            /* [in] */ USHORT uFourthLight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMotorState )( 
            IXRFRayTube * This,
            /* [out] */ UCHAR *pState,
            /* [in] */ UINT uTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MotorMove )( 
            IXRFRayTube * This,
            /* [in] */ UCHAR cID,
            /* [in] */ UCHAR cDirection,
            /* [in] */ USHORT uStep,
            /* [in] */ UCHAR cSwitch,
            /* [in] */ UCHAR cRate,
            /* [in] */ USHORT uDutyRatio,
            /* [in] */ USHORT uChamberCoef2);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChamberState )( 
            IXRFRayTube * This,
            /* [out][in] */ UCHAR pState[ 2 ],
            /* [in] */ UINT pStateLen,
            /* [in] */ UINT uTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveZAutoMotor )( 
            IXRFRayTube * This,
            /* [in] */ UCHAR cRate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSwitchInfo )( 
            IXRFRayTube * This,
            /* [out] */ SHORT *pInfo,
            UINT uTimeOut);
        
        END_INTERFACE
    } IXRFRayTubeVtbl;

    interface IXRFRayTube
    {
        CONST_VTBL struct IXRFRayTubeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXRFRayTube_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IXRFRayTube_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IXRFRayTube_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IXRFRayTube_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IXRFRayTube_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IXRFRayTube_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IXRFRayTube_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IXRFRayTube_Open(This)	\
    ( (This)->lpVtbl -> Open(This) ) 

#define IXRFRayTube_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IXRFRayTube_GetConfig(This,pVoltage,pCurrent,pUncover,uTimeOut)	\
    ( (This)->lpVtbl -> GetConfig(This,pVoltage,pCurrent,pUncover,uTimeOut) ) 

#define IXRFRayTube_SetConfig(This,uVoltage,uCurrent)	\
    ( (This)->lpVtbl -> SetConfig(This,uVoltage,uCurrent) ) 

#define IXRFRayTube_CheckVersion(This,pVersion,uTimeOut)	\
    ( (This)->lpVtbl -> CheckVersion(This,pVersion,uTimeOut) ) 

#define IXRFRayTube_bXRayTubeSel(This,index)	\
    ( (This)->lpVtbl -> bXRayTubeSel(This,index) ) 

#define IXRFRayTube_GetDoubleVacuum(This,uType,pUpVacuum,pDownVacuum,uTimeOut)	\
    ( (This)->lpVtbl -> GetDoubleVacuum(This,uType,pUpVacuum,pDownVacuum,uTimeOut) ) 

#define IXRFRayTube_GetPushButtonInfo(This,pState,uTimeOut)	\
    ( (This)->lpVtbl -> GetPushButtonInfo(This,pState,uTimeOut) ) 

#define IXRFRayTube_ClearPushButtonInfo(This)	\
    ( (This)->lpVtbl -> ClearPushButtonInfo(This) ) 

#define IXRFRayTube_OpenVacuumPump(This)	\
    ( (This)->lpVtbl -> OpenVacuumPump(This) ) 

#define IXRFRayTube_CloseVacuumPump(This)	\
    ( (This)->lpVtbl -> CloseVacuumPump(This) ) 

#define IXRFRayTube_GetVacuum(This,uType,pVacuum,uTimeOut)	\
    ( (This)->lpVtbl -> GetVacuum(This,uType,pVacuum,uTimeOut) ) 

#define IXRFRayTube_OpenHighVoltage(This)	\
    ( (This)->lpVtbl -> OpenHighVoltage(This) ) 

#define IXRFRayTube_CloseHighVoltage(This)	\
    ( (This)->lpVtbl -> CloseHighVoltage(This) ) 

#define IXRFRayTube_AllowUncover(This)	\
    ( (This)->lpVtbl -> AllowUncover(This) ) 

#define IXRFRayTube_ForbidUncover(This)	\
    ( (This)->lpVtbl -> ForbidUncover(This) ) 

#define IXRFRayTube_OpenPilotLamp(This)	\
    ( (This)->lpVtbl -> OpenPilotLamp(This) ) 

#define IXRFRayTube_ClosePilotLamp(This)	\
    ( (This)->lpVtbl -> ClosePilotLamp(This) ) 

#define IXRFRayTube_OpenElectromagnet(This)	\
    ( (This)->lpVtbl -> OpenElectromagnet(This) ) 

#define IXRFRayTube_CloseElectromagnet(This)	\
    ( (This)->lpVtbl -> CloseElectromagnet(This) ) 

#define IXRFRayTube_OpenLaserControl(This,byteOpen)	\
    ( (This)->lpVtbl -> OpenLaserControl(This,byteOpen) ) 

#define IXRFRayTube_SetLaserMode(This,bManual)	\
    ( (This)->lpVtbl -> SetLaserMode(This,bManual) ) 

#define IXRFRayTube_SetSurfaceLight(This,uFirstLight,uSecondLight,uThirdLight,uFourthLight)	\
    ( (This)->lpVtbl -> SetSurfaceLight(This,uFirstLight,uSecondLight,uThirdLight,uFourthLight) ) 

#define IXRFRayTube_GetMotorState(This,pState,uTimeOut)	\
    ( (This)->lpVtbl -> GetMotorState(This,pState,uTimeOut) ) 

#define IXRFRayTube_MotorMove(This,cID,cDirection,uStep,cSwitch,cRate,uDutyRatio,uChamberCoef2)	\
    ( (This)->lpVtbl -> MotorMove(This,cID,cDirection,uStep,cSwitch,cRate,uDutyRatio,uChamberCoef2) ) 

#define IXRFRayTube_GetChamberState(This,pState,pStateLen,uTimeOut)	\
    ( (This)->lpVtbl -> GetChamberState(This,pState,pStateLen,uTimeOut) ) 

#define IXRFRayTube_MoveZAutoMotor(This,cRate)	\
    ( (This)->lpVtbl -> MoveZAutoMotor(This,cRate) ) 

#define IXRFRayTube_GetSwitchInfo(This,pInfo,uTimeOut)	\
    ( (This)->lpVtbl -> GetSwitchInfo(This,pInfo,uTimeOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXRFRayTube_INTERFACE_DEFINED__ */


#ifndef __IHighVoltage_INTERFACE_DEFINED__
#define __IHighVoltage_INTERFACE_DEFINED__

/* interface IHighVoltage */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IHighVoltage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3CF2238-258C-4A72-9783-18F5A56F10A9")
    IHighVoltage : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IHighVoltageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHighVoltage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHighVoltage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHighVoltage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IHighVoltage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IHighVoltage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IHighVoltage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IHighVoltage * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IHighVoltageVtbl;

    interface IHighVoltage
    {
        CONST_VTBL struct IHighVoltageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHighVoltage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHighVoltage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHighVoltage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHighVoltage_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IHighVoltage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IHighVoltage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IHighVoltage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHighVoltage_INTERFACE_DEFINED__ */


#ifndef __IVacuumPump_INTERFACE_DEFINED__
#define __IVacuumPump_INTERFACE_DEFINED__

/* interface IVacuumPump */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IVacuumPump;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3FF9BF19-80A9-4A16-B457-C9009555C51F")
    IVacuumPump : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IVacuumPumpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVacuumPump * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVacuumPump * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVacuumPump * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVacuumPump * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVacuumPump * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVacuumPump * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVacuumPump * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IVacuumPumpVtbl;

    interface IVacuumPump
    {
        CONST_VTBL struct IVacuumPumpVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVacuumPump_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVacuumPump_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVacuumPump_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVacuumPump_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IVacuumPump_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IVacuumPump_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IVacuumPump_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVacuumPump_INTERFACE_DEFINED__ */


#ifndef __IMotorControl_INTERFACE_DEFINED__
#define __IMotorControl_INTERFACE_DEFINED__

/* interface IMotorControl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMotorControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("001E2793-623D-481B-B52E-1D6CC76DA85D")
    IMotorControl : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IMotorControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMotorControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMotorControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMotorControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMotorControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMotorControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMotorControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMotorControl * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IMotorControlVtbl;

    interface IMotorControl
    {
        CONST_VTBL struct IMotorControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMotorControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMotorControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMotorControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMotorControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMotorControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMotorControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMotorControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMotorControl_INTERFACE_DEFINED__ */


#ifndef __IElectromagnet_INTERFACE_DEFINED__
#define __IElectromagnet_INTERFACE_DEFINED__

/* interface IElectromagnet */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IElectromagnet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EE6C642C-4B0A-4D0E-9BE3-02EDA39BED4C")
    IElectromagnet : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IElectromagnetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IElectromagnet * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IElectromagnet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IElectromagnet * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IElectromagnet * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IElectromagnet * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IElectromagnet * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IElectromagnet * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IElectromagnet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IElectromagnet * This);
        
        END_INTERFACE
    } IElectromagnetVtbl;

    interface IElectromagnet
    {
        CONST_VTBL struct IElectromagnetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElectromagnet_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IElectromagnet_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IElectromagnet_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IElectromagnet_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IElectromagnet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IElectromagnet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IElectromagnet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IElectromagnet_Open(This)	\
    ( (This)->lpVtbl -> Open(This) ) 

#define IElectromagnet_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IElectromagnet_INTERFACE_DEFINED__ */


#ifndef __IHeightLaser_INTERFACE_DEFINED__
#define __IHeightLaser_INTERFACE_DEFINED__

/* interface IHeightLaser */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IHeightLaser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D61BCE8A-6193-4A76-BEEA-57A2462D01FB")
    IHeightLaser : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IHeightLaserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHeightLaser * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHeightLaser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHeightLaser * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IHeightLaser * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IHeightLaser * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IHeightLaser * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IHeightLaser * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IHeightLaserVtbl;

    interface IHeightLaser
    {
        CONST_VTBL struct IHeightLaserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHeightLaser_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHeightLaser_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHeightLaser_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHeightLaser_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IHeightLaser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IHeightLaser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IHeightLaser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHeightLaser_INTERFACE_DEFINED__ */


#ifndef __ISurfaceSource_INTERFACE_DEFINED__
#define __ISurfaceSource_INTERFACE_DEFINED__

/* interface ISurfaceSource */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISurfaceSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF18E5ED-E54A-4D97-A2A5-AE335B0AFFE7")
    ISurfaceSource : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfaceSource * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfaceSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfaceSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISurfaceSource * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISurfaceSource * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISurfaceSource * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISurfaceSource * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ISurfaceSourceVtbl;

    interface ISurfaceSource
    {
        CONST_VTBL struct ISurfaceSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfaceSource_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfaceSource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfaceSource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfaceSource_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISurfaceSource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISurfaceSource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISurfaceSource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfaceSource_INTERFACE_DEFINED__ */


#ifndef __IDetectData_INTERFACE_DEFINED__
#define __IDetectData_INTERFACE_DEFINED__

/* interface IDetectData */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDetectData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6EAC33BA-BAA0-4F4D-96F6-F41C822B5DB7")
    IDetectData : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ const USHORT *pData,
            /* [in] */ USHORT uDataLen) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Count( 
            /* [out] */ USHORT *pCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE At( 
            /* [in] */ USHORT uIndex,
            /* [out] */ USHORT *pData) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDetectDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDetectData * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDetectData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDetectData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDetectData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDetectData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDetectData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDetectData * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDetectData * This,
            /* [in] */ const USHORT *pData,
            /* [in] */ USHORT uDataLen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Count )( 
            IDetectData * This,
            /* [out] */ USHORT *pCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *At )( 
            IDetectData * This,
            /* [in] */ USHORT uIndex,
            /* [out] */ USHORT *pData);
        
        END_INTERFACE
    } IDetectDataVtbl;

    interface IDetectData
    {
        CONST_VTBL struct IDetectDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDetectData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDetectData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDetectData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDetectData_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDetectData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDetectData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDetectData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDetectData_Init(This,pData,uDataLen)	\
    ( (This)->lpVtbl -> Init(This,pData,uDataLen) ) 

#define IDetectData_Count(This,pCount)	\
    ( (This)->lpVtbl -> Count(This,pCount) ) 

#define IDetectData_At(This,uIndex,pData)	\
    ( (This)->lpVtbl -> At(This,uIndex,pData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDetectData_INTERFACE_DEFINED__ */


#ifndef __IDetectorCallBack_INTERFACE_DEFINED__
#define __IDetectorCallBack_INTERFACE_DEFINED__

/* interface IDetectorCallBack */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDetectorCallBack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A9FE068B-59C6-4156-BDF4-7F886069FB6B")
    IDetectorCallBack : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnRead( 
            /* [in] */ UINT uQuickCount,
            /* [in] */ UINT uSlowCount,
            /* [in] */ UINT uSystemTime,
            /* [in] */ UINT uLocalTime,
            /* [in] */ IDetectData *pData) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDetectorCallBackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDetectorCallBack * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDetectorCallBack * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDetectorCallBack * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnRead )( 
            IDetectorCallBack * This,
            /* [in] */ UINT uQuickCount,
            /* [in] */ UINT uSlowCount,
            /* [in] */ UINT uSystemTime,
            /* [in] */ UINT uLocalTime,
            /* [in] */ IDetectData *pData);
        
        END_INTERFACE
    } IDetectorCallBackVtbl;

    interface IDetectorCallBack
    {
        CONST_VTBL struct IDetectorCallBackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDetectorCallBack_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDetectorCallBack_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDetectorCallBack_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDetectorCallBack_OnRead(This,uQuickCount,uSlowCount,uSystemTime,uLocalTime,pData)	\
    ( (This)->lpVtbl -> OnRead(This,uQuickCount,uSlowCount,uSystemTime,uLocalTime,pData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDetectorCallBack_INTERFACE_DEFINED__ */


#ifndef __IDetector_INTERFACE_DEFINED__
#define __IDetector_INTERFACE_DEFINED__

/* interface IDetector */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDetector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E7A21723-40CB-4C61-86EE-867388717F2C")
    IDetector : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BeginRead( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Config( 
            /* [in] */ UCHAR cBaseResume,
            /* [in] */ UCHAR cBaseLimit,
            /* [in] */ UCHAR cHeapUP,
            /* [in] */ UCHAR cRate,
            /* [in] */ UCHAR cCoarse,
            /* [in] */ UINT uFine,
            /* [in] */ UINT uTime,
            /* [in] */ UCHAR cUPTime,
            /* [in] */ UCHAR cWidthTime,
            /* [in] */ UCHAR cSlowLimit,
            /* [in] */ double dEnCoef) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetChannelCount( 
            /* [in] */ USHORT uCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCallback( 
            /* [in] */ IDetectorCallBack *pCallback) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckVersion( 
            /* [out] */ BOOL *pCanUse,
            /* [in] */ UINT uTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDpp100Parameter( 
            /* [in] */ BYTE byteDpp100Cmd[ 68 ],
            /* [in] */ SHORT intCmdLen) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDpp100Datas( 
            /* [in] */ BYTE byteDpp100Cmd[ 68 ],
            /* [in] */ SHORT intDpp100CmdLen,
            UINT uTimeOut,
            /* [out][in] */ BYTE byteGetBytes[ 16390 ],
            /* [out][in] */ SHORT *intGetBytesLen) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDMCADatas( 
            UINT uTimeOut,
            /* [out][in] */ BYTE byteGetBytes[ 16390 ],
            /* [out][in] */ SHORT *intGetBytesLen) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDetectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDetector * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDetector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDetector * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDetector * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDetector * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDetector * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDetector * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BeginRead )( 
            IDetector * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Config )( 
            IDetector * This,
            /* [in] */ UCHAR cBaseResume,
            /* [in] */ UCHAR cBaseLimit,
            /* [in] */ UCHAR cHeapUP,
            /* [in] */ UCHAR cRate,
            /* [in] */ UCHAR cCoarse,
            /* [in] */ UINT uFine,
            /* [in] */ UINT uTime,
            /* [in] */ UCHAR cUPTime,
            /* [in] */ UCHAR cWidthTime,
            /* [in] */ UCHAR cSlowLimit,
            /* [in] */ double dEnCoef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetChannelCount )( 
            IDetector * This,
            /* [in] */ USHORT uCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCallback )( 
            IDetector * This,
            /* [in] */ IDetectorCallBack *pCallback);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckVersion )( 
            IDetector * This,
            /* [out] */ BOOL *pCanUse,
            /* [in] */ UINT uTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDpp100Parameter )( 
            IDetector * This,
            /* [in] */ BYTE byteDpp100Cmd[ 68 ],
            /* [in] */ SHORT intCmdLen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDpp100Datas )( 
            IDetector * This,
            /* [in] */ BYTE byteDpp100Cmd[ 68 ],
            /* [in] */ SHORT intDpp100CmdLen,
            UINT uTimeOut,
            /* [out][in] */ BYTE byteGetBytes[ 16390 ],
            /* [out][in] */ SHORT *intGetBytesLen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDMCADatas )( 
            IDetector * This,
            UINT uTimeOut,
            /* [out][in] */ BYTE byteGetBytes[ 16390 ],
            /* [out][in] */ SHORT *intGetBytesLen);
        
        END_INTERFACE
    } IDetectorVtbl;

    interface IDetector
    {
        CONST_VTBL struct IDetectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDetector_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDetector_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDetector_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDetector_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDetector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDetector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDetector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDetector_BeginRead(This)	\
    ( (This)->lpVtbl -> BeginRead(This) ) 

#define IDetector_Config(This,cBaseResume,cBaseLimit,cHeapUP,cRate,cCoarse,uFine,uTime,cUPTime,cWidthTime,cSlowLimit,dEnCoef)	\
    ( (This)->lpVtbl -> Config(This,cBaseResume,cBaseLimit,cHeapUP,cRate,cCoarse,uFine,uTime,cUPTime,cWidthTime,cSlowLimit,dEnCoef) ) 

#define IDetector_SetChannelCount(This,uCount)	\
    ( (This)->lpVtbl -> SetChannelCount(This,uCount) ) 

#define IDetector_SetCallback(This,pCallback)	\
    ( (This)->lpVtbl -> SetCallback(This,pCallback) ) 

#define IDetector_CheckVersion(This,pCanUse,uTimeOut)	\
    ( (This)->lpVtbl -> CheckVersion(This,pCanUse,uTimeOut) ) 

#define IDetector_SetDpp100Parameter(This,byteDpp100Cmd,intCmdLen)	\
    ( (This)->lpVtbl -> SetDpp100Parameter(This,byteDpp100Cmd,intCmdLen) ) 

#define IDetector_GetDpp100Datas(This,byteDpp100Cmd,intDpp100CmdLen,uTimeOut,byteGetBytes,intGetBytesLen)	\
    ( (This)->lpVtbl -> GetDpp100Datas(This,byteDpp100Cmd,intDpp100CmdLen,uTimeOut,byteGetBytes,intGetBytesLen) ) 

#define IDetector_GetDMCADatas(This,uTimeOut,byteGetBytes,intGetBytesLen)	\
    ( (This)->lpVtbl -> GetDMCADatas(This,uTimeOut,byteGetBytes,intGetBytesLen) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDetector_INTERFACE_DEFINED__ */


#ifndef __INetworkCallBack_INTERFACE_DEFINED__
#define __INetworkCallBack_INTERFACE_DEFINED__

/* interface INetworkCallBack */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INetworkCallBack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B8AD5FFC-3225-403f-BB30-38D54DB1752B")
    INetworkCallBack : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnConnected( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDisconnect( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnRemoteConnected( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnRemoteDisconnected( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnRemoteServerDisconnected( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct INetworkCallBackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INetworkCallBack * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INetworkCallBack * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INetworkCallBack * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnConnected )( 
            INetworkCallBack * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDisconnect )( 
            INetworkCallBack * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnRemoteConnected )( 
            INetworkCallBack * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnRemoteDisconnected )( 
            INetworkCallBack * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnRemoteServerDisconnected )( 
            INetworkCallBack * This);
        
        END_INTERFACE
    } INetworkCallBackVtbl;

    interface INetworkCallBack
    {
        CONST_VTBL struct INetworkCallBackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INetworkCallBack_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INetworkCallBack_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INetworkCallBack_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INetworkCallBack_OnConnected(This)	\
    ( (This)->lpVtbl -> OnConnected(This) ) 

#define INetworkCallBack_OnDisconnect(This)	\
    ( (This)->lpVtbl -> OnDisconnect(This) ) 

#define INetworkCallBack_OnRemoteConnected(This)	\
    ( (This)->lpVtbl -> OnRemoteConnected(This) ) 

#define INetworkCallBack_OnRemoteDisconnected(This)	\
    ( (This)->lpVtbl -> OnRemoteDisconnected(This) ) 

#define INetworkCallBack_OnRemoteServerDisconnected(This)	\
    ( (This)->lpVtbl -> OnRemoteServerDisconnected(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INetworkCallBack_INTERFACE_DEFINED__ */


#ifndef __IApparatus_INTERFACE_DEFINED__
#define __IApparatus_INTERFACE_DEFINED__

/* interface IApparatus */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IApparatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E5BA37AA-E10A-406D-B55E-1EFB81695DA4")
    IApparatus : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Config( 
            /* [in] */ const UCHAR *pIP,
            /* [in] */ const UCHAR *pSubnetMask,
            /* [in] */ const UCHAR *pGateway,
            /* [in] */ const UCHAR *pDNS) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckVersion( 
            /* [out] */ UINT *pVersion,
            /* [in] */ UINT uTimeOut) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IApparatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IApparatus * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IApparatus * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IApparatus * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IApparatus * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IApparatus * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IApparatus * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IApparatus * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Config )( 
            IApparatus * This,
            /* [in] */ const UCHAR *pIP,
            /* [in] */ const UCHAR *pSubnetMask,
            /* [in] */ const UCHAR *pGateway,
            /* [in] */ const UCHAR *pDNS);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckVersion )( 
            IApparatus * This,
            /* [out] */ UINT *pVersion,
            /* [in] */ UINT uTimeOut);
        
        END_INTERFACE
    } IApparatusVtbl;

    interface IApparatus
    {
        CONST_VTBL struct IApparatusVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApparatus_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IApparatus_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IApparatus_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IApparatus_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IApparatus_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IApparatus_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IApparatus_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IApparatus_Config(This,pIP,pSubnetMask,pGateway,pDNS)	\
    ( (This)->lpVtbl -> Config(This,pIP,pSubnetMask,pGateway,pDNS) ) 

#define IApparatus_CheckVersion(This,pVersion,uTimeOut)	\
    ( (This)->lpVtbl -> CheckVersion(This,pVersion,uTimeOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IApparatus_INTERFACE_DEFINED__ */


#ifndef __IXRFNetwork_INTERFACE_DEFINED__
#define __IXRFNetwork_INTERFACE_DEFINED__

/* interface IXRFNetwork */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IXRFNetwork;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0F5C0627-33A9-49B2-8371-A4104389D718")
    IXRFNetwork : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ const UCHAR *pIP,
            /* [in] */ unsigned short uPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartupRemoteServer( 
            /* [in] */ const UCHAR *pIP,
            /* [in] */ unsigned short uPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShutdownRemoteServer( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectRemoteServer( 
            /* [in] */ const UCHAR *pIP,
            /* [in] */ unsigned short uPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisconnectRemoteServer( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowConsole( 
            /* [in] */ BOOL bShow) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRayTube( 
            /* [retval][out] */ IXRFRayTube **ppXRFRayTube) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHighVotage( 
            /* [retval][out] */ IHighVoltage **ppHighVoltage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVacuumPump( 
            /* [retval][out] */ IVacuumPump **ppVacuumPump) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMotor( 
            /* [retval][out] */ IMotorControl **ppMotorControl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetElectromagnet( 
            /* [retval][out] */ IElectromagnet **ppElectromagnet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHeightLaser( 
            /* [retval][out] */ IHeightLaser **ppHeightLaser) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSurfaceSource( 
            /* [retval][out] */ ISurfaceSource **ppSurfaceSource) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDetector( 
            /* [retval][out] */ IDetector **ppDetector) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCallback( 
            /* [in] */ INetworkCallBack *pCallback) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckVersion( 
            /* [out] */ BOOL *pCanUse,
            /* [in] */ UINT uTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConsolePrint( 
            /* [in] */ const UCHAR *pText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetApparatus( 
            /* [retval][out] */ IApparatus **ppApparatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenSmallCamera( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseSmallCamera( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GainSmallCameraLight( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReduceSmallCameraLight( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GainLargeCameraLight( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReduceLargeCameraLight( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IXRFNetworkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXRFNetwork * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXRFNetwork * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXRFNetwork * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXRFNetwork * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXRFNetwork * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXRFNetwork * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXRFNetwork * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IXRFNetwork * This,
            /* [in] */ const UCHAR *pIP,
            /* [in] */ unsigned short uPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IXRFNetwork * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartupRemoteServer )( 
            IXRFNetwork * This,
            /* [in] */ const UCHAR *pIP,
            /* [in] */ unsigned short uPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShutdownRemoteServer )( 
            IXRFNetwork * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConnectRemoteServer )( 
            IXRFNetwork * This,
            /* [in] */ const UCHAR *pIP,
            /* [in] */ unsigned short uPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisconnectRemoteServer )( 
            IXRFNetwork * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowConsole )( 
            IXRFNetwork * This,
            /* [in] */ BOOL bShow);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRayTube )( 
            IXRFNetwork * This,
            /* [retval][out] */ IXRFRayTube **ppXRFRayTube);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHighVotage )( 
            IXRFNetwork * This,
            /* [retval][out] */ IHighVoltage **ppHighVoltage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVacuumPump )( 
            IXRFNetwork * This,
            /* [retval][out] */ IVacuumPump **ppVacuumPump);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMotor )( 
            IXRFNetwork * This,
            /* [retval][out] */ IMotorControl **ppMotorControl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetElectromagnet )( 
            IXRFNetwork * This,
            /* [retval][out] */ IElectromagnet **ppElectromagnet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHeightLaser )( 
            IXRFNetwork * This,
            /* [retval][out] */ IHeightLaser **ppHeightLaser);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSurfaceSource )( 
            IXRFNetwork * This,
            /* [retval][out] */ ISurfaceSource **ppSurfaceSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDetector )( 
            IXRFNetwork * This,
            /* [retval][out] */ IDetector **ppDetector);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCallback )( 
            IXRFNetwork * This,
            /* [in] */ INetworkCallBack *pCallback);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckVersion )( 
            IXRFNetwork * This,
            /* [out] */ BOOL *pCanUse,
            /* [in] */ UINT uTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConsolePrint )( 
            IXRFNetwork * This,
            /* [in] */ const UCHAR *pText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetApparatus )( 
            IXRFNetwork * This,
            /* [retval][out] */ IApparatus **ppApparatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenSmallCamera )( 
            IXRFNetwork * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseSmallCamera )( 
            IXRFNetwork * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GainSmallCameraLight )( 
            IXRFNetwork * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReduceSmallCameraLight )( 
            IXRFNetwork * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GainLargeCameraLight )( 
            IXRFNetwork * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReduceLargeCameraLight )( 
            IXRFNetwork * This);
        
        END_INTERFACE
    } IXRFNetworkVtbl;

    interface IXRFNetwork
    {
        CONST_VTBL struct IXRFNetworkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXRFNetwork_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IXRFNetwork_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IXRFNetwork_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IXRFNetwork_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IXRFNetwork_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IXRFNetwork_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IXRFNetwork_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IXRFNetwork_Connect(This,pIP,uPort)	\
    ( (This)->lpVtbl -> Connect(This,pIP,uPort) ) 

#define IXRFNetwork_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#define IXRFNetwork_StartupRemoteServer(This,pIP,uPort)	\
    ( (This)->lpVtbl -> StartupRemoteServer(This,pIP,uPort) ) 

#define IXRFNetwork_ShutdownRemoteServer(This)	\
    ( (This)->lpVtbl -> ShutdownRemoteServer(This) ) 

#define IXRFNetwork_ConnectRemoteServer(This,pIP,uPort)	\
    ( (This)->lpVtbl -> ConnectRemoteServer(This,pIP,uPort) ) 

#define IXRFNetwork_DisconnectRemoteServer(This)	\
    ( (This)->lpVtbl -> DisconnectRemoteServer(This) ) 

#define IXRFNetwork_ShowConsole(This,bShow)	\
    ( (This)->lpVtbl -> ShowConsole(This,bShow) ) 

#define IXRFNetwork_GetRayTube(This,ppXRFRayTube)	\
    ( (This)->lpVtbl -> GetRayTube(This,ppXRFRayTube) ) 

#define IXRFNetwork_GetHighVotage(This,ppHighVoltage)	\
    ( (This)->lpVtbl -> GetHighVotage(This,ppHighVoltage) ) 

#define IXRFNetwork_GetVacuumPump(This,ppVacuumPump)	\
    ( (This)->lpVtbl -> GetVacuumPump(This,ppVacuumPump) ) 

#define IXRFNetwork_GetMotor(This,ppMotorControl)	\
    ( (This)->lpVtbl -> GetMotor(This,ppMotorControl) ) 

#define IXRFNetwork_GetElectromagnet(This,ppElectromagnet)	\
    ( (This)->lpVtbl -> GetElectromagnet(This,ppElectromagnet) ) 

#define IXRFNetwork_GetHeightLaser(This,ppHeightLaser)	\
    ( (This)->lpVtbl -> GetHeightLaser(This,ppHeightLaser) ) 

#define IXRFNetwork_GetSurfaceSource(This,ppSurfaceSource)	\
    ( (This)->lpVtbl -> GetSurfaceSource(This,ppSurfaceSource) ) 

#define IXRFNetwork_GetDetector(This,ppDetector)	\
    ( (This)->lpVtbl -> GetDetector(This,ppDetector) ) 

#define IXRFNetwork_SetCallback(This,pCallback)	\
    ( (This)->lpVtbl -> SetCallback(This,pCallback) ) 

#define IXRFNetwork_CheckVersion(This,pCanUse,uTimeOut)	\
    ( (This)->lpVtbl -> CheckVersion(This,pCanUse,uTimeOut) ) 

#define IXRFNetwork_ConsolePrint(This,pText)	\
    ( (This)->lpVtbl -> ConsolePrint(This,pText) ) 

#define IXRFNetwork_GetApparatus(This,ppApparatus)	\
    ( (This)->lpVtbl -> GetApparatus(This,ppApparatus) ) 

#define IXRFNetwork_OpenSmallCamera(This)	\
    ( (This)->lpVtbl -> OpenSmallCamera(This) ) 

#define IXRFNetwork_CloseSmallCamera(This)	\
    ( (This)->lpVtbl -> CloseSmallCamera(This) ) 

#define IXRFNetwork_GainSmallCameraLight(This)	\
    ( (This)->lpVtbl -> GainSmallCameraLight(This) ) 

#define IXRFNetwork_ReduceSmallCameraLight(This)	\
    ( (This)->lpVtbl -> ReduceSmallCameraLight(This) ) 

#define IXRFNetwork_GainLargeCameraLight(This)	\
    ( (This)->lpVtbl -> GainLargeCameraLight(This) ) 

#define IXRFNetwork_ReduceLargeCameraLight(This)	\
    ( (This)->lpVtbl -> ReduceLargeCameraLight(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXRFNetwork_INTERFACE_DEFINED__ */



#ifndef __XRFNetLib_LIBRARY_DEFINED__
#define __XRFNetLib_LIBRARY_DEFINED__

/* library XRFNetLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_XRFNetLib;

EXTERN_C const CLSID CLSID_XRFRay;

#ifdef __cplusplus

class DECLSPEC_UUID("E7045447-BA52-4EC9-8F74-1C9A807750CF")
XRFRay;
#endif

EXTERN_C const CLSID CLSID_HighVoltage;

#ifdef __cplusplus

class DECLSPEC_UUID("802619F6-EDC4-492C-B86B-7DC1D3B70005")
HighVoltage;
#endif

EXTERN_C const CLSID CLSID_VacuumPump;

#ifdef __cplusplus

class DECLSPEC_UUID("3F182FD5-66C6-4EDB-8EC0-8C067857D013")
VacuumPump;
#endif

EXTERN_C const CLSID CLSID_MotorControl;

#ifdef __cplusplus

class DECLSPEC_UUID("D33504EF-6DED-4FF5-88D7-FEDE2C95A616")
MotorControl;
#endif

EXTERN_C const CLSID CLSID_Electromagnet;

#ifdef __cplusplus

class DECLSPEC_UUID("0CA31212-C263-4C5A-82AD-4502A8099918")
Electromagnet;
#endif

EXTERN_C const CLSID CLSID_HeightLaser;

#ifdef __cplusplus

class DECLSPEC_UUID("F5DDAFC0-62BA-42C3-972E-189FE55699FB")
HeightLaser;
#endif

EXTERN_C const CLSID CLSID_SurfaceSource;

#ifdef __cplusplus

class DECLSPEC_UUID("9FD8EB54-E882-4E70-A732-4C537807D5A9")
SurfaceSource;
#endif

EXTERN_C const CLSID CLSID_DetectData;

#ifdef __cplusplus

class DECLSPEC_UUID("E240F897-46B0-4277-A90F-55C9C89EC5C6")
DetectData;
#endif

EXTERN_C const CLSID CLSID_Detector;

#ifdef __cplusplus

class DECLSPEC_UUID("99171B6C-4EC3-453C-9A61-5A746244A6FE")
Detector;
#endif

EXTERN_C const CLSID CLSID_Apparatus;

#ifdef __cplusplus

class DECLSPEC_UUID("9022B9EA-D842-43C3-AF0C-D83BB61098DA")
Apparatus;
#endif

EXTERN_C const CLSID CLSID_XRFNetwork;

#ifdef __cplusplus

class DECLSPEC_UUID("14E8BF9B-B96F-4FBE-88BD-1B79EC215D57")
XRFNetwork;
#endif
#endif /* __XRFNetLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


