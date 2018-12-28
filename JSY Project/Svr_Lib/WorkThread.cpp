#include "WorkThread.h"
#include "ServerIOCP.h"
#include "User.h"

bool WorkThread::Run()
{
	DWORD dwTransfer;
	ULONG_PTR		keyValue;
	LPOVERLAPPED	overlapped;
	BOOL		rReturn;
	while (1)
	{
		rReturn = ::GetQueuedCompletionStatus(I_ServerIOCP.m_hIOCP,	&dwTransfer, &keyValue,	&overlapped, INFINITE);
		User* pUser = (User*)keyValue;
		if (rReturn == TRUE)
		{
			if (dwTransfer == 0)
			{
				// ���� ���� ó��
				pUser->DeleteUser();
			}
			if (dwTransfer != 0 && overlapped != 0)
			{
				pUser->Dispatch(dwTransfer, overlapped);
			}
		}
		else
		{
			// �Ѱ��� �������� ������ �ް� �� ��쿡 �߻�
			if (GetLastError() !=
				ERROR_OPERATION_ABORTED)
			{
				if (dwTransfer == 0)
				{
					// ���� ���� ó��
					pUser->DeleteUser(pUser->m_Socket);
				}
			}
		}
	}
	return true;
}

WorkThread::WorkThread(void)
{
}


WorkThread::~WorkThread(void)
{
}

