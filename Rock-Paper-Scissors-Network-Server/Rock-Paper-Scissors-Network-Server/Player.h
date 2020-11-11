#pragma once
#include<WinSock2.h>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
struct Room;
#include"Room.h"
struct Player {
	char login[20] = "";
	int password = 0;
	int score = 0;
	SOCKET connect = NULL;
	Room* roome = NULL;
	bool online = false;
	bool ready = false;
};
void DeletePlayer(Player* pl);
