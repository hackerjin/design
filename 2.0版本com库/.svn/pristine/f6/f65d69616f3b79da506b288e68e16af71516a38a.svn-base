#include "SkyraySocket.h"
#include "SkyrayUtil.h"

#pragma comment(lib, "Ws2_32.lib") 

namespace Skyray
{
	// -----------------------------------------------------------------------------------------------------

	CSocket::CSocket()
	{
		WSADATA			ws;
		int				nRev;

		nRev = WSAStartup(WINSOCK_VERSION, &ws);
		assert(0 == nRev);

		m_socket = INVALID_SOCKET;
	}

	// -----------------------------------------------------------------------------------------------------

	CSocket::CSocket(const CSocket &otherSocket)
	{
		WSADATA			ws;
		int				nRev;

		nRev = WSAStartup(WINSOCK_VERSION, &ws);
		assert(0 == nRev);

		m_socket = otherSocket.m_socket;	
	}

	// -----------------------------------------------------------------------------------------------------

	CSocket::~CSocket()
	{
		if(m_socket != INVALID_SOCKET)
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
		}

		WSACleanup();
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::Domain2IP(const std::wstring &strDomain, std::wstring &strIP)
	{
		hostent*			pHostent;
		SOCKADDR_IN 		remoteAddr;
		std::string			strTemp;

		Unicode2Ansi(strDomain.c_str(), strTemp);
		pHostent = gethostbyname(strTemp.c_str());
		if(NULL == pHostent)
			return FALSE;

		if(pHostent->h_addr_list[0])
		{
			char			acIP[64];

			memcpy(&remoteAddr.sin_addr.s_addr, pHostent->h_addr_list[0], pHostent->h_length);	
			strcpy_s(acIP, 60, inet_ntoa(remoteAddr.sin_addr));

			Ansi2Unicode(acIP, strIP);
			return TRUE;
		}

		return FALSE;
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::Create(int nSocketType, const wchar_t *pSocketIP, UINT nSocketPort)
	{
		if(m_socket != INVALID_SOCKET)
		{
			WSASetLastError(WSAEALREADY);
			return FALSE;
		}

		m_socket = socket(AF_INET, nSocketType, 0);
		if(m_socket == INVALID_SOCKET)
			return FALSE;

		if(!Bind(pSocketIP, nSocketPort))
		{
			Close();
			return FALSE;
		}

		return TRUE;	
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::Bind(const wchar_t *pSocketIP, UINT nSocketPort)
	{
		SOCKADDR_IN 		sockAddr;

		memset(&sockAddr, 0, sizeof(sockAddr));

		sockAddr.sin_family = AF_INET;
		if(pSocketIP == NULL)
		{
			sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		}
		else
		{
			DWORD 				lIP;
			std::string			strTemp;

			Unicode2Ansi(pSocketIP, strTemp);
			lIP = inet_addr(strTemp.c_str());
			if(lIP == INADDR_NONE)
			{
				WSASetLastError(WSAEINVAL);
				return FALSE;
			}

			sockAddr.sin_addr.s_addr = lIP;
		}

		if(0 == nSocketPort)
			sockAddr.sin_port = htons(INADDR_ANY);
		else
			sockAddr.sin_port = htons((u_short)nSocketPort);

		return Bind((SOCKADDR *)&sockAddr, sizeof(sockAddr));
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::Bind(const SOCKADDR *pSockAddr, int nAddrLen)
	{
		if(!bind(m_socket, pSockAddr, nAddrLen))
			return TRUE;
		else
			return FALSE;
	}	

	// -----------------------------------------------------------------------------------------------------

	void CSocket::Close()
	{
		if(m_socket != INVALID_SOCKET)
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
		}
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::Attach(SOCKET nSocket)
	{
		if(INVALID_SOCKET == nSocket)
		{
			m_socket = nSocket;
			return TRUE;
		}
		else
		{
			WSASetLastError(WSAEALREADY);
			return FALSE;
		}
	}

	// -----------------------------------------------------------------------------------------------------

	SOCKET CSocket::Detach()
	{
		SOCKET 			nSocket;

		nSocket		= m_socket;
		m_socket	= INVALID_SOCKET;

		return nSocket;
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::GetSockOpt(int nOptionName, void *pOptionValue, int *pOptionLen, int nLevel)
	{
		if(SOCKET_ERROR == getsockopt(m_socket, nLevel, nOptionName, (char *)pOptionValue, pOptionLen))
			return FALSE;
		else
			return TRUE;	
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::SetSockOpt(int nOptionName, const void *pOptionValue, int nOptionLen, int nLevel)
	{
		if(SOCKET_ERROR == setsockopt(m_socket, nLevel, nOptionName, (char *)pOptionValue, nOptionLen))
			return FALSE;
		else
			return TRUE;
	}

	// -----------------------------------------------------------------------------------------------------

	DWORD CSocket::GetLastError()
	{
		return WSAGetLastError();
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::IOCtl(int lCommand, DWORD *pArgument)
	{
		if(SOCKET_ERROR == ioctlsocket(m_socket, lCommand, pArgument))
			return FALSE;
		else
			return TRUE;
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::Listen(int nConnectCount)
	{
		if(SOCKET_ERROR == listen(m_socket, nConnectCount))
			return FALSE;
		else
			return TRUE;	
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::ShutDown(int nHow)
	{
		if(SOCKET_ERROR == shutdown(m_socket, nHow))
			return FALSE;
		else
			return TRUE;
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::Accept(CSocket &connectedSocket, SOCKADDR *pSockAddr, int *pSockAddrLen)
	{
		assert(INVALID_SOCKET == connectedSocket.m_socket);

		connectedSocket.m_socket = accept(m_socket, pSockAddr, pSockAddrLen);	
		if(connectedSocket.m_socket == INVALID_SOCKET)
			return FALSE;
		else
			return TRUE;
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::Connect(const wchar_t *pHostAddress, UINT nHostPort)
	{
		SOCKADDR_IN 		sockAddr;
		std::string			strTemp;

		if((NULL == pHostAddress) || (0 == nHostPort))
		{
			WSASetLastError(WSAEINVAL);
			return FALSE;
		}	

		Unicode2Ansi(pHostAddress, strTemp);
		memset(&sockAddr,0,sizeof(sockAddr));	
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_addr.s_addr = inet_addr(strTemp.c_str());

		if(sockAddr.sin_addr.s_addr == INADDR_NONE)
		{
			std::wstring				strIP;

			if(Domain2IP(std::wstring(pHostAddress), strIP))
			{
				Unicode2Ansi(strIP.c_str(), strTemp);
				sockAddr.sin_addr.s_addr = inet_addr(strTemp.c_str());
			}

			if(sockAddr.sin_addr.s_addr == INADDR_NONE)
			{
				WSASetLastError(WSAEINVAL);
				return FALSE;
			}
		}

		sockAddr.sin_port = htons((u_short)nHostPort);
		return Connect((SOCKADDR*)&sockAddr, sizeof(sockAddr));
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::Connect(const SOCKADDR *pSocketAddr, int nSocketAddrLen)
	{
		if(SOCKET_ERROR == connect(m_socket, pSocketAddr, nSocketAddrLen))
			return FALSE;
		else
			return TRUE;
	}

	// -----------------------------------------------------------------------------------------------------

	int CSocket::Receive(char *pBuffer, int nBufferLen, int nFlags)
	{
		return recv(m_socket, pBuffer, nBufferLen, nFlags);
	}

	// -----------------------------------------------------------------------------------------------------

	int CSocket::Send(const char *pBuffer, int nBufferLen, int nFlags)	
	{
		return send(m_socket, pBuffer, nBufferLen, nFlags);
	}

	// -----------------------------------------------------------------------------------------------------

	int CSocket::ReceiveFrom(char *pBuffer, int nBufferLen, int nFlags, SOCKADDR *pRemoteAddr, int *pAddrLen)
	{
		return recvfrom(m_socket, pBuffer, nBufferLen, nFlags, pRemoteAddr, pAddrLen);
	}

	// -----------------------------------------------------------------------------------------------------

	int CSocket::SendTo(const char *pBuffer, int nBufferLen, int nFlags, SOCKADDR *pRemoteAddr, int nAddrLen)
	{
		return sendto(m_socket, pBuffer, nBufferLen, nFlags, pRemoteAddr, nAddrLen);
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::CanRead(DWORD dwMilliseconds)
	{
		fd_set 		readfds;
		timeval 	timeout;

		if(INVALID_SOCKET == m_socket)
		{
			WSASetLastError(WSAEINVAL);
			return FALSE;
		}

		if(0 == dwMilliseconds)
		{
			timeout.tv_sec 	= 0;
			timeout.tv_usec = 0;
		}
		else
		{
			timeout.tv_sec 	= dwMilliseconds/1000;
			timeout.tv_usec = dwMilliseconds%1000;
		}

		FD_ZERO(&readfds);
		FD_SET(m_socket, &readfds);

		int ret = select(0, &readfds, NULL, NULL, &timeout);
		if(SOCKET_ERROR == ret)
			return FALSE;

		if((ret > 0) && FD_ISSET(m_socket,  &readfds))
			return TRUE;
		else 
			return FALSE;
	}

	// -----------------------------------------------------------------------------------------------------

	BOOL CSocket::CanWrite(DWORD dwMilliseconds)		
	{
		fd_set 			writefds;
		timeval 		timeout;

		if(INVALID_SOCKET == m_socket)
		{
			WSASetLastError(WSAEINVAL);
			return FALSE;
		}

		if(0 == dwMilliseconds)
		{
			timeout.tv_sec	= 0;
			timeout.tv_usec	= 0;
		}
		else
		{
			timeout.tv_sec	= dwMilliseconds/1000;
			timeout.tv_usec = dwMilliseconds%1000;
		}

		FD_ZERO(&writefds);
		FD_SET(m_socket, &writefds);

		int ret = select(0, NULL, &writefds, NULL, &timeout);		
		if(SOCKET_ERROR == ret)
			return FALSE;

		if((ret > 0) && FD_ISSET(m_socket,  &writefds))
			return TRUE;
		else 
			return FALSE;	
	}
}