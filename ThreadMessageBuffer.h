/*******************************************************
 * Copyright (C) 2014 iQIYI.COM - All Rights Reserved
 * 
 * This file is part of {HCDN}.
 * Unauthorized copy of this file, via any medium is strictly prohibited.
 * Proprietary and Confidential.
 * 
 * Author(s): xuxiaoyi <xuxiaoyi@qiyi.com>
 * 
 *******************************************************/
#ifndef __VODNET_BASE_THREADMESSAGEBUFFER_H__INCLUDE__
#define __VODNET_BASE_THREADMESSAGEBUFFER_H__INCLUDE__

#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
//#include <intrin.h>
#include "UnitQueue.h"
#include "basetype.h"
#define MAX_MESSAGEBUFFER_LENGTH    (2 * 1024 * 1024+1024)

namespace th_message_mempool
{

class ThreadMessageBuffer
{
public:
    /*!	panguipin, 2012-5-30   14:17
    *	desc:	缓存管理
    *	access:
    *	params:	Datatype		paramname		IN/OUT	remark
    *			unsigned char*  _buffer			IN      需要拷贝的数据.如果不拷贝数据，只分配内存，_buffer为空
	*			int             _length         IN      分配内存大小
    *	return:
    */
    /*! Yuan.Peng
     *  统一在ThreadMessageBuffer( int _length );构造函数中初始化内存
     */
	ThreadMessageBuffer( const unsigned char* _buffer,int _length );
	ThreadMessageBuffer( int _length );
	virtual ~ThreadMessageBuffer();
    /*! Yuan.Peng
     *  将内存保护起来
     */
    unsigned char * GetBuffer()
    {
        return m_Buffer;
    }
    int GetBufferSize()
    {
        return m_BufferSize;
    }
    /*! Yuan.Peng
     *  由用户自己设定使用内存的长度
     */
    bool SetLength( int _Length, int & _OldLength  )
    {
        _OldLength = m_Length;
        if( _Length > 0  && _Length <= m_BufferSize )
        {
            m_Length = _Length;
            return true;
        }
        return false;
    }
    int GetLength()
    {
        return m_Length;
    }
protected:
    // 初始化内存
    bool Init( int _BufferSize );
public:
    /*static long s_total_block_new_cnt;*/
    static long m_u64NewBufferCnt;
    static long m_u64DeleteBufferCnt;
    static long m_u64NewBufferSize;
    static long m_u64DeleteBufferSize;//volatile
protected:
	int m_Length;
    int m_BufferSize;
	unsigned char * m_Buffer;

};

//volatile LONG ThreadMessageBuffer::m_u64NewBufferCnt = 0;
//volatile LONG ThreadMessageBuffer::m_u64DeleteBufferCnt = 0;
//volatile LONG ThreadMessageBuffer::m_u64NewBufferSize = 0;
//volatile LONG ThreadMessageBuffer::m_u64DeleteBufferSize = 0;

typedef boost::shared_ptr<ThreadMessageBuffer>	MessageBufferPtr;

} // vodnet_base



#endif // __VODNET_BASE_THREADMESSAGEBUFFER_H__INCLUDE__