#include <windows.h>
#include <stdio.h>

int a[4];
HANDLE hThr;	// десткриптер потока
unsigned long uThrID;

HANDLE hMutex = 0;

void ThreadFunction(void* pParams)
{
	int i, n = 0;
	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);
		for (i = 0; i < 4; i++)
		{
			a[i] = n;
		}
		n++;
		ReleaseMutex(hMutex);
	}
}

int main()
{
	hMutex = CreateMutex(NULL, FALSE, NULL);
	hThr = CreateThread(
		NULL,	// настройка безопасности
		0,		// индентификатор процесса
		(LPTHREAD_START_ROUTINE)ThreadFunction,
		NULL,
		0,
		&uThrID
	);

	for (int era = 0; era <= 20; era++)
	{
		WaitForSingleObject(hMutex, 0);
		printf("%4d era: %8d %8d %8d %8d\n", era, a[0], a[1], a[2], a[3]);
		ReleaseMutex(hMutex);
	}

	return 0;
}
