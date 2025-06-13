#ifndef _ENDPOINT_MGR_H_
#define _ENDPOINT_MGR_H_

/** 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, 天瑞仪器
* All rights reserved.  
*  
* @file EndPointMgr.h
* @brief 终端管理器
*  
* 主要职责：实现管理终端接口
*
* @version 1.0
* @author  汤军
* @date    2010年8月3日
*  
*  
* 修订说明：最初版本  
*/

#include "IEndPointMgr.h"
#include "SkyrayLock.h"

class CEndPointMgr : public NetLib::IEndPointMgr
{
public:
	CEndPointMgr();
	~CEndPointMgr();

	/** 
	@brief	添加一个终端
	@param	pEndPoint 终端接口
	@return	TRUE	添加终端成功
	FALSE	添加终端失败
	*/
	BOOL Add(NetLib::IEndPoint *pEndPoint);

	/** 
	@brief		查找终端
	@param		uID		终端描述符
	@return	NULL	指定终端不存在
	其他	终端接口
	*/
	NetLib::IEndPoint* Find(UINT uID); 

	/** 
	@brief		移除终端
	@param		uID		终端描述符
	*/
	void Remove(UINT uID);

	/** 
	@brief	清空终端管理器
	*/
	void Clear();

private:
	typedef std::vector<NetLib::IEndPoint *> EndPointList;
	typedef EndPointList::iterator EndPointIt;
	
private:
	Skyray::CLock		m_lock;
	EndPointList		m_list;
};

#endif