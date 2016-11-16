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
#include "psl_lock.h"

_NAMESPACE_BEGIN
	CLock::CLock(void)
	{
#ifdef WIN32
		::InitializeCriticalSection(&m_cs);
#else
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
#ifdef OS_IOS
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
#else
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#endif
        pthread_mutex_init(&m_mutex,&attr);
        pthread_mutexattr_destroy(&attr);
#endif
	}

	CLock::~CLock(void)
	{
#ifdef WIN32
		::DeleteCriticalSection(&m_cs);
#else
		pthread_mutex_destroy(&m_mutex);
#endif
	}
	void CLock::Lock()
	{
#ifdef WIN32
		EnterCriticalSection(&m_cs);
#else
		pthread_mutex_lock(&m_mutex);
#endif
	}
	void CLock::UnLock()
	{
#ifdef WIN32
		LeaveCriticalSection(&m_cs);
#else
		pthread_mutex_unlock(&m_mutex);
#endif
	}
	AutoLock::AutoLock(CLock &lock):m_lock(lock)
	{
		m_lock.Lock();
	}
	AutoLock::~AutoLock()
	{
		m_lock.UnLock();
	}
_NAMESPACE_END