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
#ifndef __SINGLETON_H__
#define __SINGLETON_H__


#include"psl_lock.h"
#include "_PSL.h"

_NAMESPACE_BEGIN

template<class T>
class singleton
{
protected:
    singleton(void){}
    virtual ~singleton(void){}
public:
    static inline T* GetSingleton(void);
private:
    singleton(const singleton&);
    const singleton& operator=(const singleton&);
private:
    static T *_instance;
	static psl_live::CLock	_csCounter;
};

template <class T>
T *singleton<T>::_instance = NULL;

template <class T>
CLock	singleton<T>::_csCounter;

template<class T>
inline T* singleton<T>::GetSingleton(void)
{
    if (NULL==_instance)
    {
        psl_live::AutoLock lock(_csCounter);
        if (NULL == _instance)
        {
            _instance = new T;
        }
    }
    return _instance;
}
_NAMESPACE_END
#endif // __SINGLETON_H__
