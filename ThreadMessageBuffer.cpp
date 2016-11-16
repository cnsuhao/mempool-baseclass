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

//#include "stdafx.h"

#include "ThreadMessageBuffer.h"
#include "MemoryFragmentManager.h"

namespace th_message_mempool
{

long ThreadMessageBuffer::m_u64NewBufferCnt = 0;
long ThreadMessageBuffer::m_u64DeleteBufferCnt = 0;
long ThreadMessageBuffer::m_u64NewBufferSize = 0;
long ThreadMessageBuffer::m_u64DeleteBufferSize = 0;

//GlobalQueueInit g_GlobalQueueInit;

ThreadMessageBuffer::ThreadMessageBuffer( const unsigned char* _Buffer,int _BufferSize )
: m_Buffer(NULL)
, m_BufferSize(0)
, m_Length(0)
{
	assert( _BufferSize > 0 && _BufferSize <= MAX_MESSAGEBUFFER_LENGTH );
    if( Init( _BufferSize ) )
	{
        if( NULL != _Buffer && NULL != m_Buffer
            && m_BufferSize >= _BufferSize )
        {
            memcpy_s( m_Buffer, m_BufferSize, _Buffer, _BufferSize );
        }
	}
}

ThreadMessageBuffer::ThreadMessageBuffer( int _BufferSize )
: m_Buffer(NULL)
, m_BufferSize(0)
, m_Length(0)
{
    assert( _BufferSize > 0 && _BufferSize <= MAX_MESSAGEBUFFER_LENGTH );
    Init( _BufferSize );
}

ThreadMessageBuffer::~ThreadMessageBuffer()
{
	if( NULL != m_Buffer)
	{
        /*if( NULL != m_pUnit )
            g_GlobalQueueInit.FreeBufferBackToQueue( m_pUnit, m_Buffer );
        else
		    delete [] m_Buffer;*/
		psl_live::g_MFM.FreeMemery( m_Buffer );
		m_Buffer = NULL;
        // 计数析释放内存
        // 计数内存分配
        InterlockedIncrement( &m_u64DeleteBufferCnt );
        //_InterlockedAnd( &m_u64DeleteBufferSize, m_length );
        //_InterlockedAdd64( &m_u64DeleteBufferSize, m_length );
	}
    m_BufferSize = 0;
	m_Length = 0;
}

bool ThreadMessageBuffer::Init( int _BufferSize )
{
    if( _BufferSize > 0 && _BufferSize <= MAX_MESSAGEBUFFER_LENGTH )
	{
        /*m_pUnit = g_GlobalQueueInit.AllocBufferFromQueue( _BufferSize );
        if( NULL != m_pUnit)
            m_Buffer = ( BYTE * )(m_pUnit->m_pcData);
        else
		    m_Buffer = new unsigned char[_BufferSize];*/

		m_Buffer = psl_live::g_MFM.AllocMemery( _BufferSize );
		if( NULL != m_Buffer )
		{
            m_BufferSize = _BufferSize;
			m_Length = m_BufferSize;
            // 计数内存分配
            InterlockedIncrement( &m_u64NewBufferCnt );
            return true;
            //_InterlockedAdd( &m_u64NewBufferSize, _length );
		}
	}
    return false;
}

} // vodnet_base
