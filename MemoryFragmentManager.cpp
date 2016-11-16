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
/*!	File:		MemoryFragmentManager.cpp
 *	Version:	1.0.0.0-2012-10-2
 *	Desc:		内存碎片管理，用于管理小内存的，预分配一批各种规格的内存，放在队列中
 *	History:	version		date		author		action
 *				1.0.0.0		2012-10-2	Yuan.Peng	创建
 */

#include "MemoryFragmentManager.h"

_NAMESPACE_BEGIN
CMFM    g_MFM;
CMFM::CMFM()
{
    m_cmd36KMsgQueue.init( 10, MSS_34K );
    m_cmd17KMsgQueue.init( 50, MSS_17K );
    m_cmd4KMsgQueue.init( 40, MSS_4K );
    m_cmd3KMsgQueue.init( 30, MSS_3K );
    m_cmd2KMsgQueue.init( 100, MSS_2K );
    m_cmd1KMsgQueue.init( 200, MSS_1K );
    m_cmd512MsgQueue.init( 200, MSS_512 );
	m_cmd128MsgQueue.init( 200, MSS_128);
}

CUnit * CMFM::AllocBufferFromQueue( unsigned int _BufferSize )
{
	CUnit * pUnit = NULL;
	if( _BufferSize <= MSS_128 )
	{
		pUnit = m_cmd128MsgQueue.getNextAvailUnit();
	}
    else if( _BufferSize <= MSS_512 )
    {
        pUnit = m_cmd512MsgQueue.getNextAvailUnit();
    }
    else if( _BufferSize <= MSS_1K )
    {
        pUnit = m_cmd1KMsgQueue.getNextAvailUnit();
    }
    else if( _BufferSize <= MSS_2K )
    {
        pUnit = m_cmd2KMsgQueue.getNextAvailUnit();
    }
    else if( _BufferSize <= MSS_3K )
    {
        pUnit = m_cmd3KMsgQueue.getNextAvailUnit();
    }
    else if( _BufferSize <= MSS_4K )
    {
        pUnit = m_cmd4KMsgQueue.getNextAvailUnit();
    }
    else if( _BufferSize <= MSS_17K )
    {
        pUnit = m_cmd17KMsgQueue.getNextAvailUnit();
    }
    else if( _BufferSize <= MSS_34K )
    {
        pUnit = m_cmd36KMsgQueue.getNextAvailUnit();
    }
    return pUnit;
}

void CMFM::FreeBufferBackToQueue( CUnit * _pUnit, unsigned int _BufferSize )
{
	if( _BufferSize <= MSS_128)
	{
		m_cmd128MsgQueue.freeUnit( _pUnit );
	}
    else if( _BufferSize <= MSS_512 )
    {
        m_cmd512MsgQueue.freeUnit( _pUnit );
    }
    else if( _BufferSize <= MSS_1K )
    {
        m_cmd1KMsgQueue.freeUnit( _pUnit );
    }
    else if( _BufferSize <= MSS_2K )
    {
        m_cmd2KMsgQueue.freeUnit( _pUnit );
    }
    else if( _BufferSize <= MSS_3K )
    {
        m_cmd3KMsgQueue.freeUnit( _pUnit );
    }
    else if( _BufferSize <= MSS_4K )
    {
        m_cmd4KMsgQueue.freeUnit( _pUnit );
    }
    else if( _BufferSize <= MSS_17K )
    {
        m_cmd17KMsgQueue.freeUnit( _pUnit );
    }
    else if( _BufferSize <= MSS_34K )
    {
        m_cmd36KMsgQueue.freeUnit( _pUnit );
    }
}

unsigned char * CMFM::AllocMemery( unsigned int _Size )
{
    unsigned char * pBuffer = NULL;
    // boost::lock_guard<boost::recursive_mutex> lock(m_mutex);
	AutoLock cs(m_csStatus);
	CUnit * pUnit = AllocBufferFromQueue( _Size );
    if( NULL != pUnit )
    {
        pBuffer = (unsigned char *)(pUnit->m_pcData);
        m_mapMemery.insert( make_pair( pBuffer, make_pair( pUnit, _Size ) ) );
    }
    else
    {
        pBuffer = new unsigned char[_Size];
        if( NULL != pBuffer )
        {
            m_mapMemery.insert( make_pair( pBuffer, make_pair( pUnit, _Size ) ) );
        }
    }
    return pBuffer;
}

void CMFM::FreeMemery( unsigned char * _Address )
{
    // boost::lock_guard<boost::recursive_mutex> lock(m_mutex);
	psl_live::AutoLock cs(m_csStatus);
    map<unsigned char *, pair<CUnit *, unsigned int> >::iterator itMapMemery = m_mapMemery.find( _Address  );
    if( itMapMemery != m_mapMemery.end() )
    {
        CUnit * pUnit = itMapMemery->second.first;
        unsigned int Size = itMapMemery->second.second;
        if( NULL != pUnit )
        {
            FreeBufferBackToQueue( pUnit, Size );
        }
        else
        {
            delete [] _Address;
        }
        m_mapMemery.erase( itMapMemery );
    }
}
_NAMESPACE_END
