#include <stdio.h>
#include <windows.h>
#include <string.h>
HANDLE hmutex = CreateMutex(0, 0, 0);

DWORD WINAPI myFunc(LPVOID cnt)
{
	for (int i = 0; i < 10000; i++)
	{
		WaitForSingleObject(hmutex, INFINITE);
		(*(int *)cnt)++;
		ReleaseMutex(hmutex);
	}
	return 0;
}
//win32多线程命名规则
//函数 每个单词首字母大写
//类型 所有字母大写


int main()
{
	DWORD thdId;
	HANDLE thd;
	int cnt = 0;
	
	
	thd = CreateThread(NULL, 0, myFunc, (LPVOID)&cnt, 0, &thdId);

	for (int i = 0; i < 10000; i++)
	{
		WaitForSingleObject(hmutex,INFINITE);
		cnt++;
		ReleaseMutex(hmutex);
	}
	
	WaitForSingleObject(thd,INFINITE);
	printf("%d", cnt);
	
}

