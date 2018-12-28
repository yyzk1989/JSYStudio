#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <thread>
#include <process.h>
#include <ws2tcpip.h>
#include <list>
#include <vector>
#include <map>
//#include "TStd.h"

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "Svr_Lib.lib")
#define _CRT_SECURE_NO_WARNINGS

typedef std::basic_string<char>  C_STR;

template<class T> class Singleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};

#define SAFE_NEW(A, B)				{ if (!A) A = new B; }

#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }