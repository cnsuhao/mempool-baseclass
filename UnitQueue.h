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
/*	File:		UniQueue.h
 *	Version:	1.0.0.0-2007.11.15
 *	Desc:		小内存管理类，减少频繁的内存请求。分配一整块内存
 *	History:	version		date		author		action
 *				1.0.0.0		2007.11.15	YuanPeng	创建，参考udt中queue的源码
 *              1.0.0.1     2010-8-4    YuanPeng    添加clear方法
 *              1.0.0.2     2012-9-28   Yuan.Peng   改为临界区改为boost的互斥体
 */

#ifndef __UDT_QUEUE_H__INCLUDE__
#define __UDT_QUEUE_H__INCLUDE__

#include "basetype.h"
#include "psl_lock.h"
#include "_PSL.h"


namespace psl_live{

struct CUnit
{
	friend class CUnitQueue;
	char * m_pcData;		// packet

	int	m_iFlag;			// 0: free, 1: occupied, 2: msg read but not freed (out-of-order), 3: msg dropped
protected:
};

class CUnitQueue
{
friend class CRcvQueue;
friend class CRcvBuffer;

public:
   CUnitQueue();
   ~CUnitQueue();

public:
      // Functionality:
      //    Initialize the unit queue.
      // Parameters:
      //    1) [in] size: queue size
      //    2) [in] mss: maximum segament size
      //    3) [in] version: IP version
      // Returned value:
      //    0: success, -1: failure.

   int init(const int& size, const int& mss);

      // Functionality:
      //    Increase (double) the unit queue size.
      // Parameters:
      //    None.
      // Returned value:
      //    0: success, -1: failure.

   int increase();

      // Functionality:
      //    Decrease (halve) the unit queue size.
      // Parameters:
      //    None.
      // Returned value:
      //    0: success, -1: failure.

   int shrink();

   // Functionality:
   //    find an available unit for incoming packet.
   // Parameters:
   //    None.
   // Returned value:
   //    Pointer to the available unit, NULL if not found.

   CUnit* getNextAvailUnit();

   //释放一个unit
   void freeUnit(CUnit * unit);
   /*	YP.2010-8-4
    *	清空内存
	*/
   void clear();
private:
   struct CQEntry
   {
      CUnit* m_pUnit;		// unit queue
      char* m_pBuffer;		// data buffer
      int m_iSize;		// size of each queue

      CQEntry* m_pNext;
   }
   *m_pQEntry,			// pointer to the first unit queue
   *m_pCurrQueue,		// pointer to the current available queue
   *m_pLastQueue;		// pointer to the last unit queue

   CUnit* m_pAvailUnit;         // recent available unit

   int m_iSize;			// total size of the unit queue, in number of packets
   int m_iCount;		// total number of valid packets in the queue

   int m_iMSS;			// unit buffer size

protected:
	CLock m_csStatus;
};

}

#endif // __UDT_QUEUE_H__INCLUDE__
