#include "DebugString.h"
#include "Synchronize.h"
bool		DebugString::Init()
{
	m_hList = NULL;
	return true;
}
bool		DebugString::Release()
{
	return true;
}
void DebugString::Print(const char* fmt, ...)
{
	if (m_hList == NULL) return;
	{
		Synchronize Sync(this);
		va_list arg;
		va_start(arg, fmt);
		char buf[256] = { 0, };
		vsprintf_s(buf, fmt, arg);
		SendMessage(m_hList, LB_ADDSTRING, 0,
			(LPARAM)I_Debug.GetMbToWcs(buf));
		int index = SendMessage(m_hList, LB_GETCOUNT, 0, 0);
		if (index > 30)
		{
			SendMessage(m_hList, LB_RESETCONTENT, 0, 0);
		}
		va_end(arg);
	}
}
void DebugString::Print(char* fmt, ...)
{

	if (m_hList == NULL) return;
	{
		Synchronize Sync(this);
		va_list arg;
		va_start(arg, fmt);
		char buf[256] = { 0, };
		vsprintf_s(buf, fmt, arg);
		SendMessage(m_hList, LB_ADDSTRING, 0,
			(LPARAM)I_Debug.GetMbToWcs(buf));
		int index = SendMessage(m_hList, LB_GETCOUNT, 0, 0);
		if (index > 30)
		{
			SendMessage(m_hList, LB_RESETCONTENT, 0, 0);
		}
		va_end(arg);
	}
}
void DebugString::T_ERROR(bool bPrint)
{
	{
		Synchronize Sync(this);
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			char* lpMsgBuf;
			FormatMessageA(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM, NULL,
				WSAGetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(char*)&lpMsgBuf, 0, NULL);
			if (bPrint)
			{
				MessageBoxA(NULL, lpMsgBuf, "ERROR", MB_OK);
			}
			else
			{
				OutputDebugStringA((char*)lpMsgBuf);
			}
			LocalFree(lpMsgBuf);
		}
	}
}
WCHAR* DebugString::GetMbToWcs(const char* strMsg)
{
	TCHAR msg[4096] = { 0, };
	{
		Synchronize Sync(this);
		int nRen = MultiByteToWideChar(CP_ACP, 0, strMsg,
			-1, 0, 0);
		ConverAnsiStringToWideCch(msg, strMsg, nRen);
	}
	return msg;
}
HRESULT DebugString::ConverAnsiStringToWideCch(WCHAR* msg,
	const char* strMsg,
	int nRen)
{
	{
		Synchronize Sync(this);
		if (msg == NULL || strMsg == NULL || nRen < 1)
		{
			return E_INVALIDARG;
		}
		int nRetrun = MultiByteToWideChar(CP_ACP, 0,
			strMsg, -1,
			msg, nRen);
		if (nRen == 0) return E_FAIL;
		msg[nRen - 1] = 0;
	}
	return S_OK;
};

char* DebugString::GetWcsToMbs(const WCHAR* strMsg)
{
	char msg[4096] = { 0, };
	{
		Synchronize Sync(this);
		int iRen = WideCharToMultiByte(CP_ACP, 0, strMsg, -1, 0, 0, NULL, NULL);
		ConvertWideStringToAnsiCch(msg, strMsg, iRen);
	}
	return msg;
}
HRESULT DebugString::ConvertWideStringToAnsiCch(char* msg,
	const WCHAR* strMsg, int iRen)
{
	{
		Synchronize Sync(this);
		if (msg == NULL || strMsg == NULL || iRen < 1)
		{
			return E_INVALIDARG;
		}
		int iReturn = WideCharToMultiByte(CP_ACP, 0,
			strMsg, -1,
			msg, iRen, NULL, NULL);
		if (iReturn == 0) return E_FAIL;
	}
	return S_OK;
};


DebugString::DebugString()
{
}


DebugString::~DebugString()
{
}
