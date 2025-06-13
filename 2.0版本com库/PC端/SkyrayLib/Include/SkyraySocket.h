#ifndef _SKYRAY_SOCKET_H_
#define _SKYRAY_SOCKET_H_

/*! 
* COPYRIGHT NOTICE  
* Copyright (c) 2010, ��������
* All rights reserved.  
*  
* @file socket.h
* @brief �ṩ���׽��ֵļ򵥷�װ
*  
* Ϊ�ͻ��˰汾�򵥵ķ�װ���׽��֣��Լ��������ı�д��
*
* @version 1.0
* @author  ����
* @date    2010��8��2��
*  
*  
* �޶�˵��������汾  
*/

#include "SkyrayLib.h"

namespace Skyray
{
	/**
	@brief �׽��� ��װ��ϵͳ���׽��ֺ����Լ��׽���ʹ�õĸ��Ӷȡ�
	*/
	class CSocket
	{
	public:
		CSocket();
		CSocket(const CSocket &otherSocket);
		virtual ~CSocket();

		/**
		*@brief	�׽����Ƿ��Ǹ��Ϸ����׽���
		*@return 	
		*- TRUE		�Ϸ�
		*- FALSE	���Ϸ�
		*/
		BOOL IsValid() { return (INVALID_SOCKET != m_socket); }

		/**
		*@brief	�������õ�IP��ַ
		*@param	strDomain	����
		*@param	strIP		��ַ
		*@return 	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/
		BOOL Domain2IP(const std::wstring &strDomain, std::wstring &strIP);

		/**
		*@brief	����һ��Socket
		*@param	nSocketType	�׽��ֵ�����
		*@param	pSocketIp	�׽��ֵĵ�ַ
		*@param	nSocketPort	�׽��ֵĶ˿ں�
		*@return 	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/
		BOOL Create(int nSocketType = SOCK_STREAM, const wchar_t *pSocketIP = NULL, UINT nSocketPort = 0);			

		/**
		*@brief	��һ��Socket
		*@param	nSocketPort	�׽��ֵĶ˿ں�
		*@param	pSocketIp	�׽��ֵĵ�ַ
		*@return	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/
		BOOL Bind(const wchar_t *pSocketIP, UINT nSocketPort);

		/**
		*@brief	��һ��Socket
		*@param	pSockAddr	�׽��ֵ�������ַ
		*@param	nAddrLen	�׽��ֵĵ�ַ����
		*@return 	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/
		BOOL Bind(const SOCKADDR *pSockAddr, int nAddrLen);

		/**
		*@brief		�ر�һ���׽���
		*@return 	�޷���ֵ
		*/	
		void Close();										

		/**
		*@brief	��һ��socket����󶨵�����
		*@param	nSocket		�׽��ֵľ����	
		*@return 	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/	
		BOOL Attach(SOCKET nSocket);	

		/**
		*@brief	��һ��socket����Ӷ����з��룬����ʼ������
		*@param	nSocket		�׽��ֵľ����	
		*@return	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/	
		SOCKET Detach();

		/**
		*@brief	�õ� Socket ��������Ϣ
		*@param	nOptionName		���õ�����
		*@param	nOptionValue	���õ�ֵ
		*@param	pOptionLen		���õ�ֵ�ó���
		*@param	nLevel			���õò��
		*@return 	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/
		BOOL GetSockOpt(int nOptionName, void *pOptionValue, int *pOptionLen, int nLevel=SOL_SOCKET);

		/**
		*@brief	���� Socket ��������Ϣ
		*@param	nOptionName		��������
		*@param	pOptionValue	���õ�ֵ
		*@param	nOptionLen		���õ�ֵ�ó���
		*@param	nLevel			���õò��	
		*@return 	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/	
		BOOL SetSockOpt(int nOptionName, const void *pOptionValue, int nOptionLen, int nLevel = SOL_SOCKET);

		/**
		*@brief	�õ����һ���������
		*@return	ͬWSAGetLastError;
		*/
		DWORD GetLastError();

		/**
		*@brief	���� �׽��� �� IO ����ģʽ
		*@param	lCommand 	��������
		*@param	pArgument	�������
		*@return	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/
		BOOL IOCtl(int lCommand, DWORD *pArgument);

		/**
		*@brief	����һ������
		*@param	nConnectCount	��������������
		*@return	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/
		BOOL Listen(int nConnectCount = 5);

		/**
		*@brief	ʹ�׽��ֵĲ��ֹ���ʧЧ
		*@param	nHow	
		*- 0 ����ʧЧ
		*- 1 ����ʧЧ
		*- 2 ���ܺͷ��Ͷ�ʧЧ
		*@return	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/
		BOOL ShutDown(int nHow = 1);

		/**
		*@brief	����һ������
		*@param	connectedSocket	���Ӷ���
		*@param	pSockAddr		���ӵ�ַ
		*@param	pSockAddrLen	���ӵ�ַ�ó���	
		*@return	
		*- TRUE		����ִ�гɹ�
		*- FALSE	����ִ��ʧ��
		*/
		virtual BOOL Accept(CSocket &connectedSocket, SOCKADDR *pSockAddr = NULL, int *pSockAddrLen=NULL);

		/**
		*@brief	����һ������
		*@param	pHostAddress	���ӵ�Ŀ�ĵ�ַ
		*@param	nHostPort		���ӵ�Ŀ�Ķ˿�
		*@return	
		*- TRUE			����ִ�гɹ�
		*- FALSE		����ִ��ʧ��
		*/
		virtual BOOL Connect(const wchar_t *pHostAddress, UINT nHostPort);

		/**
		*@brief	����һ������
		*@param	pSocketAddr		���ӵ�Ŀ�ĵ�ַ
		*@param	nSocketAddrLen	���ӵ�Ŀ�ĵ�ַ�ĳ���
		*@return	
		*- TRUE			����ִ�гɹ�
		*- FALSE		����ִ��ʧ��
		*/
		virtual BOOL Connect(const SOCKADDR *pSocketAddr, int nSocketAddrLen);

		/**
		*@brief	��������
		*@param	pBuffer			�������ݵ��û�������
		*@param	nBufferLen		������pBuffer�Ĵ�С
		*@param	nFlags			���ձ�־
		*@return	
		*- SOCKET_ERROR	����
		*- ����			��ʵ���ܵ������ݵĳ��ȣ�
		*/
		virtual int Receive(char *pBuffer, int nBufferLen, int nFlags = 0);	

		/**
		*@brief	��������
		*@param	pBuffer			�û�Ҫд������
		*@param	nBufferLen		����pBuffer�Ĵ�С
		*@param	nFlags			���ͱ�־
		*@return	
		*- SOCKET_ERROR 	����ִ��ʧ�ܣ�ԭ��ο�����send��sendto
		*- ����				��ʵ���͵����ݵĳ���, ���ܻ�С��nBufferLen��
		*/
		virtual int Send(const char *pBuffer, int nBufferLen, int nFlags = 0);	

		/**
		*@brief	��������
		*@param	pBuffer			�������ݵ��û�������
		*@param	nBufferLen		������pBuffer�Ĵ�С
		*@param	nFlags			���շ��
		*@param	pRemoteAddr		��������Դ��ַ
		*@param	pAddrLen		����Դ��ַ�ĳ���
		*@return	
		*- ����	��ʵ���ܵ������ݵĳ���  
		*- Ϊ��	����ִ��ʧ�ܣ�ԭ��ο�����recv��recvfrom
		*/
		virtual int ReceiveFrom(char *pBuffer, int nBufferLen, int nFlags, SOCKADDR *pRemoteAddr, int *pAddrLen);	

		/**
		*@brief	��������
		*@param	pBuffer			�û�Ҫд������
		*@param	nBufferLen		����pBuffer�Ĵ�С
		*@param	nFlags			���ͷ��
		*@param	pRemoteAddr		����Ŀ�ĵ�ַ
		*@param	pAddrLen		Ŀ�ĵ�ַ�ĳ���
		*@return 	
		*- SOCKET_ERROR 	����ִ��ʧ�ܣ�ԭ��ο�����send��sendto
		*- ����			��ʵ���͵����ݵĳ���, ���ܻ�С��nBufferLen��
		*/
		virtual int SendTo(const char *pBuffer, int nBufferLen, int nFlags, SOCKADDR *pRemoteAddr, int nAddrLen);

		/**
		*@brief	�鿴�׽����Ƿ�ɶ�
		*@param	dwMilliseconds	��ѯ��ʱ(��λΪ����)
		*@return	
		*- TRUE		�׽��ֿɶ�
		*- FALSE		�׽��ֲ��ɶ�
		*/
		virtual BOOL CanRead(DWORD dwMilliseconds=0);

		/**
		*@brief	�鿴�׽����Ƿ��д
		*@param	dwMilliseconds	��ѯ��ʱ(��λΪ����)
		*@return	
		*- TRUE		�׽��ֿ�д
		*- FALSE		�׽��ֲ���д
		*/								
		virtual BOOL CanWrite(DWORD dwMilliseconds=0);	

	private:
		SOCKET		m_socket;		
	};
}

#endif