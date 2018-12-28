#include "Synchronize.h"



Synchronize::Synchronize(ServerObj* pObj) : m_pSerObj(pObj)
{
	if (pObj == NULL) return;
	EnterCriticalSection(&pObj->m_cs);
}


Synchronize::~Synchronize()
{
	if (m_pSerObj == NULL) return;
	LeaveCriticalSection(&m_pSerObj->m_cs);
}
