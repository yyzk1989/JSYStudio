#pragma once
class FSM_Megaman_Info
{
public:
	int				m_iIndex;
	float			m_fPositionX;
	float			m_fPositionY;
	bool			m_bDirection;

	int				i_HP = 15;
	int				i_Attack = 1; //charge´Â 4

	int				i_NOW_Stage = 0;
	bool			m_bCharacter = false;
public:
	FSM_Megaman_Info();
	virtual ~FSM_Megaman_Info();
};

