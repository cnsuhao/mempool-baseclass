/*******************************************************
* Copyright (C) 2014 iQIYI.COM - All Rights Reserved
* 
* This file is part of {HCDN}.
* Unauthorized copy of this file, via any medium is strictly prohibited.
* Proprietary and Confidential.
* 
* Author(s): xiaojian <xiaojian@qiyi.com>
* 
*******************************************************/
// NetBase.h: interface for the CNetBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__NET_BASE__H__)
#define __NET_BASE__H__
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "basetype.h"
#include <string>
#include <list>
#include <vector>
#include <set>
#include <base/include/psl_lock.h>
#include <base/include/_PSL.h>
#ifdef WIN32
#ifndef _WIN32_WINNT
    #define _WIN32_WINNT  0x0501
#endif
    typedef int socklen_t;
    typedef int ssize_t;
    #include <Winsock2.h>
    #include <Ws2tcpip.h>
	#include <Nb30.h>
    #include <WinINet.h>
	#pragma comment(lib,"ws2_32.lib")  
#else
    #include <sys/types.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <strings.h>
#if (!defined(OS_IOS) && !defined(OS_MACOSX))
    #include <sys/epoll.h>
#endif
//    #include <sys/signal.h>
    #include <sys/time.h>
    #include <sys/resource.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/ioctl.h>
    #include <net/if.h>
#ifndef OS_IOS
    #include <net/if_arp.h>
#endif
    #define  SOCKET int 
    typedef sockaddr_in SOCKADDR_IN;
    typedef sockaddr SOCKADDR,*LPSOCKADDR;
#ifdef PF_IQIYI_TV
    #define  PPS_ETC_FILE "ems.conf"
    #define PPS_ROOT_PATH ""
#endif
    #define SOCKET_ERROR (-1)
    #define INVALID_SOCKET (-1)
    #define SOCKADDR_IN sockaddr_in
    #define CString string
	#define closesocket close
#endif

using namespace std;
//#define interface struct

#ifndef WIN32
    #ifndef PURE
        #define PURE =0
    #endif
#endif

//#ifndef STDMETHOD
//#define STDMETHOD(x) virtual long x
//#endif

#ifndef STDMETHODIMP
#define STDMETHODIMP            long
#endif


_NAMESPACE_BEGIN
#ifdef WIN32
class CWSAInit
{
public:
	CWSAInit(BOOL bForceExit = TRUE)
	{
		WSADATA wsaData;
		if(WSAStartup(0x0202,&wsaData)!=NULL)
		{

		}
	}
	~CWSAInit(){WSACleanup();}
};
static CWSAInit m_WSAInstance;
#endif

_NAMESPACE_END
#ifdef WIN32
	#include <windows.h>
	#define LOAD_DLL(path)	LoadLibraryA(path)
	#define GET_FUNC(h, f)	(void*)::GetProcAddress((HINSTANCE)h, f)
	#define UNLOAD_DLL(h)	FreeLibrary((HINSTANCE)h)
	#define DLL_HANDLE      HINSTANCE
#else
    #include <dlfcn.h>
	#define LOAD_DLL(path)	dlopen(path, RTLD_LAZY)
	#define GET_FUNC		dlsym
	#define UNLOAD_DLL		dlclose
	#define DLL_HANDLE      void *
#endif
#endif // !defined(__NET_BASE__H__)
