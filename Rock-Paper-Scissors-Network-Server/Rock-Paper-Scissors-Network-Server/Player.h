#pragma once
#include"Room.h"
#include<WinSock2.h>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
struct Player {
	char login[20] = "";
	int password = 0;
	int score = 0;
	SOCKET connect = NULL;
	Room* room = NULL;
	bool online = false;
	bool ready = false;
};
void DeletePlayer(Player* pl);