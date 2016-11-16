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
#pragma once

#include "_PSL.h"
#ifdef WIN32
#include<Windows.h>
#else
#include <pthread.h>
#endif
_NAMESPACE_BEGIN

	class CLock
	{
	public:
		CLock(void);
		~CLock(void);
		void Lock();
		void UnLock();
	private:
#ifdef WIN32
		CRITICAL_SECTION  m_cs;
#else
		pthread_mutex_t  m_mutex;
#endif
	};
	class AutoLock
	{
	public:
		AutoLock(CLock &lock);
		~AutoLock();
	private:
		CLock &m_lock;
	};

_NAMESPACE_END
