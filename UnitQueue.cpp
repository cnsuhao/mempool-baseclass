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
/*	File:		UniQueue.cpp
 *	Version:	1.0.0.0-2007.11.15
 *	Desc:		小内存管理类，减少频繁的内存请求。分配一整块内存
 *	History:	version		date		author		action
 *				1.0.0.0		2007.11.15	YuanPeng	创建，来源于udt中queue的修改
 */
#include "UnitQueue.h"
#include<string>
using namespace std;

_NAMESPACE_BEGIN

CUnitQueue::CUnitQueue():
m_pQEntry(NULL),
m_pCurrQueue(NULL),
m_pLastQueue(NULL),
m_iSize(0),
m_iCount(0)
{
}

CUnitQueue::~CUnitQueue()
{
   clear();
}

void CUnitQueue::clear()
{
	CQEntry* p = m_pQEntry;

	while (p != NULL)
	{
		delete [] p->m_pUnit;
		delete [] p->m_pBuffer;

		CQEntry* q = p;
		if (p == m_pLastQueue)
			p = NULL;
		else
			p = p->m_pNext;
		delete q;
	}
}

int CUnitQueue::init(const int& size, const int& mss)
{
	psl_live::AutoLock  cs(m_csStatus);

	clear();

	CQEntry* tempq = NULL;
	CUnit* tempu = NULL;
	char* tempb = NULL;

	tempq = new CQEntry;
	tempu = new CUnit[size];
	tempb = new char [size * mss];
	for (int i = 0; i < size; ++ i)
	{
		tempu[i].m_iFlag = 0;
		tempu[i].m_pcData = tempb + i * mss;
	}
	tempq->m_pUnit = tempu;
	tempq->m_pBuffer = tempb;
	tempq->m_iSize = size;

	m_pQEntry = m_pCurrQueue = m_pLastQueue = tempq;
	m_pQEntry->m_pNext = m_pQEntry;

	m_pAvailUnit = m_pCurrQueue->m_pUnit;

	m_iSize = size;
	m_iMSS = mss;

	return 0;
}

int CUnitQueue::increase()
{
   // adjust/correct m_iCount
   int real_count = 0;
   CQEntry* p = m_pQEntry;
   while (p != NULL)
   {
      CUnit* u = p->m_pUnit;
      for (CUnit* end = u + p->m_iSize; u != end; ++ u)
         if (u->m_iFlag != 0)
            ++ real_count;

      if (p == m_pLastQueue)
         p = NULL;
      else
         p = p->m_pNext;
   }
   m_iCount = real_count;
   if (double(m_iCount) / m_iSize < 0.9)
      return -1;

   CQEntry* tempq = NULL;
   CUnit* tempu = NULL;
   char* tempb = NULL;

   // all queues have the same size
   int size = m_pQEntry->m_iSize;

  tempq = new CQEntry;
  tempu = new CUnit [size];
  tempb = new char [size * m_iMSS];
   for (int i = 0; i < size; ++ i)
   {
      tempu[i].m_iFlag = 0;
      tempu[i].m_pcData = tempb + i * m_iMSS;
   }
   tempq->m_pUnit = tempu;
   tempq->m_pBuffer = tempb;
   tempq->m_iSize = size;

   m_pLastQueue->m_pNext = tempq;
   m_pLastQueue = tempq;
   m_pLastQueue->m_pNext = m_pQEntry;

   m_iSize += size;

   return 0;
}

int CUnitQueue::shrink()
{
	// currently queue cannot be shrunk.
	return -1;
}
void CUnitQueue::freeUnit(CUnit * unit)
{
	psl_live::AutoLock  cs(m_csStatus);
	if(unit->m_iFlag == 1)
		m_iCount --;
	unit->m_iFlag = 0;
}
CUnit* CUnitQueue::getNextAvailUnit()
{
	psl_live::AutoLock  cs(m_csStatus);
	if (double(m_iCount) / m_iSize > 0.9)
	{
		if(-1 == increase())
		{
			increase();
		}
	}

	if (m_iCount >= m_iSize)
		return NULL;

	CQEntry* entrance = m_pCurrQueue;

	do
	{
		for (CUnit* sentinel = m_pCurrQueue->m_pUnit + m_pCurrQueue->m_iSize - 1; m_pAvailUnit != sentinel; ++ m_pAvailUnit)
		{
			if (m_pAvailUnit->m_iFlag == 0)
			{
				m_pAvailUnit->m_iFlag = 1;
				m_iCount ++;
				return m_pAvailUnit;
			}
		}

		if (m_pAvailUnit->m_iFlag == 0)//该组内的最后一个
		{
			m_pAvailUnit->m_iFlag = 1;
			CUnit * pUnit = m_pAvailUnit;
			m_pCurrQueue = m_pCurrQueue->m_pNext;
			m_pAvailUnit = m_pCurrQueue->m_pUnit;
			m_iCount ++;
			return pUnit;
		}

		m_pCurrQueue = m_pCurrQueue->m_pNext;
		m_pAvailUnit = m_pCurrQueue->m_pUnit;
	} while (m_pCurrQueue != entrance);

	//increase();

	return NULL;
}

_NAMESPACE_END
