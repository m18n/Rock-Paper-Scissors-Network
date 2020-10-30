#pragma once
#include<iostream>
#include"Player.h"
#include<vector>
#include<WinSock2.h>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
using namespace std;
struct Connect {
	WSAData wsaData;
	WORD DLLversion;
	SOCKADDR_IN addr;
	int sizeofaddr = 0;
};
void recvEx(Player& pl, char* buff, int size);
void sendEx(Player& pl, const char* buff, int size);
void Inithilization(Connect& cn, string ip, short int port);
void ConnectSocket(Connect& cn, vector<Player*>& conn, void(*Handle)(Player& pl));