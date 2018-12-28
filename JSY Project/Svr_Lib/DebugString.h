#pragma once
#include "ServerObj.h"

class DebugString : public Singleton<DebugString>, public ServerObj
{
private:
	friend class Singleton<DebugString>;
public:
	HWND	  m_hList;
public:
	void		Print(char* fmt, ...);
	void		Print(const char* fmt, ...);
public:
	bool		Init();
	bool		Release();
	WCHAR* GetMbToWcs(const char* strMsg);
	char* GetWcsToMbs(const WCHAR* strMsg);
	HRESULT ConvertWideStringToAnsiCch(char* msg,
		const WCHAR* strMsg, int iRen);
	HRESULT ConverAnsiStringToWideCch(WCHAR* msg,
		const char* strMsg,
		int nRen);
	void	T_ERROR(bool bPrint = false);

public:
	DebugString();
	virtual ~DebugString();
};

#define I_Debug DebugString::GetInstance()