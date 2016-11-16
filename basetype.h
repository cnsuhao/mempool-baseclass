/*******************************************************
 * Copyright (C) 2014 iQIYI.COM - All Rights Reserved
 * 
 * This file is part of {HCDN}.
 * Unauthorized copy of this file, via any medium is strictly prohibited.
 * Proprietary and Confidential.
 * 
 * Author(s): zenglinan <zenglinan@qiyi.com>
 * 
 *******************************************************/
#ifndef __TYPE__H__
#define __TYPE__H__
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <assert.h>
#include <time.h>
#include "tchar.h"
#include "_PSL.h"
#include <map>
#include <list>
#include <set>
#include <string>

using namespace std;
#ifdef __LINUX__
#include <netdb.h>
#include <sys/socket.h>

#endif
//#define __LINUX__
//#define __ANDROID__

#if defined(OS_IOS) || defined(OS_MACOSX)
#include <sys/time.h>

#include <mach/mach_time.h>
#include <mach/clock.h>

#define ORWL_NANO (+1.0E-9)
#define ORWL_GIGA UINT64_C(1000000000)
#endif

#ifdef ANDROID
#undef ANDROID
#endif

//#ifdef UNMULTIBYTE
//#define tsprintf wsprintf
//#define tnsprintf swprintf
//#else
#define tsprintf sprintf
#define tnsprintf snprintf
//#endif


#ifndef THREAD_PRIORITY_NORMAL
#define THREAD_PRIORITY_NORMAL          0
#endif

#ifdef WIN32

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#define Fseek(x,y,z) _fseeki64((x),(y),(z))
#define Ftell(x) _ftelli64(x)
#else
#include "NetBaseDef.h"
typedef hostent HOSTENT;
#define Fseek(x,y,z) fseeko64((x),(y),(z))
#define Ftell(x) ftello64(x)
#if (defined OS_ANDROID)|| (defined OS_IOS)||(defined _FO_ROUTER_)
#define fseeko64(stream, offset, origin) fseeko(stream, offset, origin)
#define ftello64(stream) ftello(stream)
#define TEXT(quote) __TEXT(quote)
#define __TEXT(quote) quote  
#define FILE_BEGIN              0
#define FILE_CURRENT            1
#define FILE_END                2
#endif

#define INVALID_HANDLE_VALUE -1
#define HLOCAL void*
#define __stdcall
//#define HANDLE UINT
#define S_FALSE 1
#define S_OK 0
#define HRESULT long
#define ESRCH           3


#ifndef WINAPI
#define WINAPI __stdcall
#endif

#endif

//huchen 2013.11.6  为android添加CP_ACP的值 
#ifndef WIN32
#define CP_ACP                    0
#define DeleteFile(file) remove(file)
#define DeleteFileA(file) remove(file)
#endif

#ifndef _DISABLEWARNING4786_4355
#define _DISABLEWARNING4786_4355
#pragma warning( disable : 4786 )
#pragma warning( disable : 4355 )
#endif

#ifndef _ENABLEUSESTL
#define _ENABLEUSESTL
#endif

#ifdef _DEBUG
#define CYASSERT(f)
#else
#define CYASSERT(f)
#endif
#define DPASSERT(x) CYASSERT(x)
const int CONFIGURATIONVALUEBUFFER_SIZE = 1030;


typedef unsigned long long	uint64;
typedef unsigned int		uint32;
typedef unsigned short		uint16;
typedef unsigned char		uint8;

typedef long long	int64;
typedef int			int32;
typedef short		int16;


typedef const char          *LPCSTR, *PCSTR;
typedef char                *LPSTR, *PSTR;
#define nil	0
#ifndef _L
#define _L(x) __L(x)
#ifndef __L
#define __L(x) L##x
#endif
#endif

//#define lstrlen  lstrlenA
//#define lstrcpy  lstrcpyA
#define tstring  std::string
#ifndef _T
#define _T(s) s

#define ttoi     atoi
#define tstrchr  strchr
#endif

#define __WFUNCTION__ __FUNCTION__
#define __TFUNCTION__ __FUNCTION__
#define __WFILE__     L"file"


#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#undef far
#undef near
#undef pascal

#define far
#define near
#define CONST               const

#undef FAR
#undef NEAR

#define FAR far
#define NEAR near

#ifndef MAX_PATH
#define MAX_PATH        260
#endif

#if (defined OS_ANDROID)||(defined _FO_ROUTER_)
/*
template<class A>
A min(A a,A b)
{
	return a>b?b:a;
}
template<class A>
A max(A a,A b)
{
	return a>b?a:b;
}
*/
#endif

//#ifndef interface
//    #define interface struct
//#endif

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
//#include <sys/atomic.h>
#define sprintf_s snprintf
typedef void                *PVOID;
typedef int					INT;
typedef int					BOOL, *PBOOL, *LPBOOL;
typedef unsigned int		UINT, UINT32 ,size_t;
typedef char				CHAR;
typedef short				SHORT;
typedef long				LONG;
typedef unsigned int		DWORD, ULONG;
typedef long long			INT64, __int64, LONGLONG;
typedef unsigned long long	UINT64, DDWORD, ULONGLONG;
typedef unsigned char		BYTE, UCHAR;
typedef unsigned short		WORD, USHORT;
typedef float				FLOAT;
typedef FLOAT				*PFLOAT;
typedef BYTE				*PBYTE;
typedef BYTE				*LPBYTE;
typedef int					*PINT;
typedef int					*LPINT;
typedef WORD				*PWORD;
typedef WORD				*LPWORD;
typedef long				*LPLONG;
typedef DWORD				*PDWORD;
typedef DWORD				*LPDWORD;
typedef void				*LPVOID;
typedef const void			*LPCVOID;
typedef void				*HANDLE,*HMODULE;
typedef wchar_t             WCHAR;
typedef WCHAR               *PWCHAR;
typedef WCHAR               *LPWCH, *PWCH;
typedef ULONG				*PULONG;
typedef void				*HRSRC;
typedef const WCHAR			*LPCWSTR;

// use for crypt
typedef unsigned int ALG_ID;

typedef unsigned long ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR HCRYPTPROV;
typedef ULONG_PTR HCRYPTKEY;
typedef ULONG_PTR HCRYPTHASH;

typedef union _ULARGE_INTEGER {
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } u;
    ULONGLONG QuadPart;
} ULARGE_INTEGER;

typedef const char          *LPCSTR;
typedef void				VOID;
#ifndef _UNICODE
typedef const char          *LPCTSTR;
typedef char                *LPTSTR;
typedef char                TCHAR;
#else
typedef const wchar_t       *LPCTSTR;
typedef wchar_t             *LPTSTR;
typedef wchar_t             TCHAR;
#endif	// _UNICODE


#define ERROR_SUCCESS       0L
#define NO_ERROR            0L
#define ERROR_CRC           23L
#define INFINITE            0xFFFFFFFF
#ifdef __mips__
#define ULONG_MAX     0xffffffffUL 
#endif
#define OutputDebugString   printf
#define stricmp             strcasecmp
#define strcmpi             strcasecmp
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)

inline void Sleep(unsigned int x)
{
#if defined(OS_IOS) || defined(__APPLE__)
    if (x<40)
    {
        x = 40;
    }
#endif
    usleep(x*1000);
}

inline unsigned long GetTickCount()
{
#if (!defined(OS_IOS) && !defined(OS_MACOSX)) && !defined(__APPLE__)
    struct timespec t_spec;
    clock_gettime(CLOCK_MONOTONIC, &t_spec);
    return t_spec.tv_sec *1000 + t_spec.tv_nsec / 1000000;
#else
#ifdef IOS_ARM64
    static unsigned long startTick =0;
    if (startTick == 0 )
    {
        timeval tv;
        gettimeofday(&tv, NULL);
        startTick = tv.tv_sec * 1000 +tv.tv_usec / 1000;
    }
    timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long curTick = tv.tv_sec * 1000 +tv.tv_usec / 1000;
    return curTick - startTick;
#else
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 +tv.tv_usec / 1000;
#endif
#endif
}

inline long InterlockedCompareExchange(volatile long* Destination, long Exchange, long Comperand)
{
    return __sync_val_compare_and_swap((int32_t*)Destination, Comperand, Exchange);
}

inline long InterlockedIncrement(volatile long* Destination)
{
    return __sync_add_and_fetch((int32_t*)Destination, 1);
}

inline long InterlockedDecrement(volatile long* Destination)
{
    return __sync_sub_and_fetch((int32_t*)Destination, 1);
}

#define memcpy_s(dest, size, src, len) memcpy((dest), (src), (min(size, len)))

#endif	// WIN32

inline time_t GetTimeSec()
{
#if defined(WIN32)
    return time(NULL);
#else
#if (!defined(OS_IOS) && !defined(OS_MACOSX))
    struct timespec t_spec;
    clock_gettime(CLOCK_MONOTONIC, &t_spec);
    return t_spec.tv_sec;
#else
    static double orwl_timebase = 0.0;
    static uint64_t orwl_timestart = 0;
    
    // be more careful in a multithreaded environement
    if (!orwl_timestart) {
        mach_timebase_info_data_t tb = { 0 };
        mach_timebase_info(&tb);
        orwl_timebase = tb.numer;
        orwl_timebase /= tb.denom;
        orwl_timestart = mach_absolute_time();
    }
    struct timespec t_spec;
    double diff = (mach_absolute_time() - orwl_timestart) * orwl_timebase;
    t_spec.tv_sec = diff * ORWL_NANO;
    t_spec.tv_nsec = diff - (t_spec.tv_sec * ORWL_GIGA);
    return t_spec.tv_sec;
#endif
#endif
}


#define TRACE printf
#define ASSERT assert
#define VERIFY assert

inline int os_fopen_s(FILE **_file, const char *_file_name, const char *_mode)
{
#ifdef WIN32
    return fopen_s(_file, _file_name, _mode);
#else
    *_file = fopen(_file_name, _mode);
    return (*_file==NULL)?-1:0;
#endif
}

/*
  func  : os_strncpy_s 
  param : char * _dst            : 目的缓冲区 
          unsigned int _dst_size : 目的缓冲区字节大小 
          const char *           : 源缓冲区 
          unsigned int _src_size : 源缓冲区大小 
  return: 错误码，成功返回0，失败返回非零 
  notic : 对于_src_size参数， 
          1 在WIN32环境下，会始终保证_dst内数据以'\0'结尾 
              当_src_size为-1时，函数为自动截断模式， 
                  当出现_src数据大于等于_dst_size指定长度时，做截断处理，_dst最后一个字节填充'\0' 
              当_src_size为小于_src数据长度时，做截断处理 
              当_src_size大于_src数据长度时，只会拷贝_src内数据长度 
              当_src_size大于_src并且大于_dst_size时，出现崩溃 
          在使用该函数时，需明确清楚_src_size参数不同值造成的结果影响， 
          尤其是在填充-1值时，确保可以接受数据截断，否则建议让其崩溃 

          2 在非WIN32环境下，会始终保证_dst内数据以'\0'结尾 
              该环境下始终在缓冲区不足的情况下进行数据截断，不会出现崩溃 
*/
inline int os_strncpy_s(char *_dst, unsigned int _dst_size, const char *_src, unsigned int _src_size)
{
    assert(_dst_size>0);
#ifdef WIN32
    return strncpy_s(_dst, _dst_size, _src, _src_size);
#else
    unsigned int size = strlen(_src);
    size = size>_src_size?_src_size:size;
    size = size>(_dst_size-1)?(_dst_size-1):size;
    strncpy(_dst, _src, size);
    _dst[size] = '\0';
    return 0;
#endif
}

#ifdef WIN32
#define os_sprintf_s(_buffer, _buffer_size, format, ...) sprintf_s(_buffer, _buffer_size, format, ##__VA_ARGS__)
#else
#define os_sprintf_s(_buffer, _buffer_size, format, ...) snprintf(_buffer, _buffer_size, format, ##__VA_ARGS__)
#endif

#ifdef WIN32
#define os_access_s(_file, _mode) _access((_file), (_mode))
#else
#define os_access_s(_file, _mode) access((_file), (_mode))
#endif

inline char* os_itoa_s(int value,char *buffer,unsigned int sizeInCharacters,int radix)
{
#ifdef WIN32
	_itoa_s(value,buffer,sizeInCharacters,radix) ;
	return buffer ;
#else
	if(10 == radix)
	{
		snprintf(buffer,sizeInCharacters,"%d",value);
	}
	else if(16 == radix)
	{
		snprintf(buffer,sizeInCharacters,"%x",value);
	}
	
	return buffer;
#endif
}

inline UINT64 os_atoui64(const char *szUnsignedInt) {
#ifdef WIN32
	return _strtoui64(szUnsignedInt, NULL, 10);
#else
	return static_cast<UINT64>(atoll(szUnsignedInt));
#endif
}


inline int os_strncat_s(char *_dst, unsigned int _dst_size, const char *_src, unsigned int _src_size)
{
#ifdef WIN32
    return strncat_s(_dst, _dst_size, _src, _src_size);
#else
    unsigned int _dst_used = strlen(_dst);
    if(_src_size == (unsigned int)(-1))
    {
        _src_size = strlen(_src);
    }
    if(_src_size + _dst_used + 1 > _dst_size)
    {
        // overflow
    }
    unsigned int _size = (_dst_size-_dst_used-1)>_src_size?_src_size:(_dst_size-_dst_used-1);
    strncat(_dst, _src, _size);
    return _size<_src_size?-1:0;
#endif
}

inline void os_wcsncpy_s(wchar_t *strDest, unsigned int numberOfElements, const wchar_t *strSource, unsigned int count)
{
#ifdef WIN32
    wcsncpy_s(strDest, numberOfElements, strSource, count);
#else
    unsigned int size = wcslen(strSource);;
    if(count == (unsigned int)-1)
    {
        count = size;
    }
    else
    {
        size = size>count?count:size;
    }
    size = size>(numberOfElements-1)?(numberOfElements-1):size;
    wcsncpy(strDest, strSource, size);
    strDest[size] = 0;
#endif
}

inline int os_strcmpi_s(const char *string1,const char *string2)
{
#ifdef WIN32
	return _strcmpi(string1,string2);
#else
	return strcasecmp(string1,string2);
#endif
}

//#ifdef WIN32
//    #define interface interface
//#else
//    #define interface struct
//#endif

#ifdef WIN32
#define INT64_ARG   "%I64d"
#define UINT64_ARG  "%I64u"
#else
#define INT64_ARG   "%lld"
#define UINT64_ARG  "%llu"
#endif // WIN32

#define XML_UTF8_HEAD   "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"
#define XML_GB2312_HEAD "<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n"

#ifdef WIN32
#define XML_HEAD	XML_GB2312_HEAD

#else
#define XML_HEAD	XML_GB2312_HEAD
#endif

#ifdef WIN32
#define localtime_r(_time_t,_tm) localtime_s((_tm),(_time_t))
#endif

#ifdef WIN32
//#include <boost/algorithm/string.hpp>
#define ON_LINUX_MAKE_LOWER(str)
#define ON_WINDOWS_MAKE_LOWER(str) boost::algorithm::to_lower(str)
#else
//((stringex&)(str)).makelower()
#define ON_LINUX_MAKE_LOWER(str) boost::algorithm::to_lower(str)
#define ON_WINDOWS_MAKE_LOWER(str)
#endif

//HC 2013.11.8
#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif

//HC add for downlaodengine
#ifndef WIN32
#define THREAD_BASE_PRIORITY_MAX    2   // maximum thread base priority boost
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX
#define THREAD_PRIORITY_ABOVE_NORMAL    (THREAD_PRIORITY_HIGHEST-1)

#define WAIT_TIMEOUT                     258L    // dderror

/*
 * WinSock 2 extension -- manifest constants for shutdown()
 */
#define SD_RECEIVE      0x00
#define SD_SEND         0x01
#define SD_BOTH         0x02

typedef	struct linger	LINGER;

#ifndef _ERRCODE_DEFINED
#define _ERRCODE_DEFINED
typedef int errno_t;
#endif

#endif

//HC add for storage
#ifndef WIN32

typedef ULARGE_INTEGER *PULARGE_INTEGER;

#if defined(MIDL_PASS)
typedef struct _LARGE_INTEGER {
#else // MIDL_PASS
typedef union _LARGE_INTEGER {
	struct {
		DWORD LowPart;
		LONG HighPart;
	} DUMMYSTRUCTNAME;
	struct {
		DWORD LowPart;
		LONG HighPart;
	} u;
#endif //MIDL_PASS
	LONGLONG QuadPart;
} LARGE_INTEGER;


#endif


#endif  // __TYPE__H__
