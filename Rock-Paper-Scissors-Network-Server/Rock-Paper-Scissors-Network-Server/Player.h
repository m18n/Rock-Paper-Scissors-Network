#pragma once
#include<WinSock2.h>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
struct Player {
	char login[20] = "";
	int password = 0;
	int score = 0;
	SOCKET connect = NULL;
	bool online = false;
};