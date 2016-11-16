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
/*!	File:		MemoryFragmentManager.h
 *	Version:	1.0.0.0-2012-10-2
 *	Desc:		内存碎片管理，用于管理小内存的，预分配一批各种规格的内存，放在队列中
 *	History:	version		date		author		action
 *				1.0.0.0		2012-10-2	Yuan.Peng	创建
 *              1.0.0.1     2012-10-16  Yuan.Peng   由单例改为全局变量，方便控制构析时间
 */
#ifndef __MEMORYFRAGMENTMANAGER_H__INCLUDE__
#define __MEMORYFRAGMENTMANAGER_H__INCLUDE__

#pragma once

#define MSS_34K 34816
#define MSS_17K 17408
#define MSS_4K  4096
#define MSS_3K  3072
#define MSS_2K  2048
#define MSS_1K  1024
#define MSS_512 512
#define MSS_128 128

#include "UnitQueue.h"
#include "singleton.h"
//#include <boost/thread/recursive_mutex.hpp>
#include <map>

using namespace std;

_NAMESPACE_BEGIN

class CMFM // : public singleton<CMFM>
{
public:
    CMFM();
    /*! Yuan.Peng
     *  从预分配队列中获得内存，若失败，则返回空
     */
	psl_live::CUnit * AllocBufferFromQueue( unsigned int _BufferSize );
    /*! Yuan.Peng
     *  将不再使用的内存还给预分配队列
     */
	void FreeBufferBackToQueue( psl_live::CUnit * _pUnit, unsigned int _BufferSize );
    unsigned char * AllocMemery( unsigned int _Size );
    void FreeMemery( unsigned char * _Address );
protected:
    psl_live::CLock m_csStatus;//临界区
	map<unsigned char *, pair<psl_live::CUnit *, unsigned int> >   m_mapMemery;
	psl_live::CUnitQueue                          m_cmd36KMsgQueue;
	psl_live::CUnitQueue                          m_cmd17KMsgQueue;
	psl_live::CUnitQueue                          m_cmd4KMsgQueue;
	psl_live::CUnitQueue                          m_cmd3KMsgQueue;
	psl_live::CUnitQueue                          m_cmd2KMsgQueue;
	psl_live::CUnitQueue                          m_cmd1KMsgQueue;
	psl_live::CUnitQueue                          m_cmd512MsgQueue;
	//add by xuxiaoyi
	psl_live::CUnitQueue                          m_cmd128MsgQueue;
};

#endif // __MEMORYFRAGMENTMANAGER_H__INCLUDE__

extern  CMFM    g_MFM;

_NAMESPACE_END
