#pragma once
#include "Acceptor.h"
#include "FSM_Timer.h"
class FSM_Sample : public Acceptor
{
public:
	FSM_Timer t_Timer;
public:
	bool   Init();
public:
	FSM_Sample();
	~FSM_Sample();
};

