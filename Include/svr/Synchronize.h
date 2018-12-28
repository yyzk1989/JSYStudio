#pragma once
#include "ServerObj.h"
class Synchronize
{
public:
	ServerObj * m_pSerObj;
public:
	Synchronize(ServerObj* pObj);
	virtual ~Synchronize();
};

