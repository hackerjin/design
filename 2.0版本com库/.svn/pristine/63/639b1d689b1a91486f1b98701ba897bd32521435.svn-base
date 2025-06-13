// DetectData.cpp : Implementation of CDetectData
#include "stdafx.h"
#include "DetectData.h"

// -----------------------------------------------------------------------------------------------------

HRESULT CDetectData::FinalConstruct()
{
	m_pData = NULL;
	m_uDataLen = 0;
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

void CDetectData::FinalRelease()
{
	if(NULL != m_pData)
	{
		delete []m_pData;
		m_pData = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CDetectData::Init(const USHORT *pData, USHORT uDataLen)
{
	if((NULL == pData) || (0 == uDataLen))
		return E_INVALIDARG;

	if(NULL != m_pData)
	{
		delete []m_pData;
		m_pData = NULL;
	}

	m_pData = new USHORT[uDataLen];
	m_uDataLen = uDataLen;
	memcpy_s(static_cast<void *>(m_pData), sizeof(USHORT)*m_uDataLen, static_cast<const void *>(pData), sizeof(USHORT)*uDataLen);
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CDetectData::Count(USHORT *pCount)
{
	if(NULL == pCount)
		return E_INVALIDARG;

	*pCount = m_uDataLen;
	return S_OK;
}

// -----------------------------------------------------------------------------------------------------

STDMETHODIMP CDetectData::At(USHORT uIndex, USHORT *pData)
{
	if((NULL == m_pData) || (uIndex >= m_uDataLen) || (NULL == pData))
		return E_INVALIDARG;

	*pData = m_pData[uIndex];
	return S_OK;
}