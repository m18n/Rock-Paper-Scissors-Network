#include "Network.h"
void ConnectSocket(Connect& cn, vector<Player*>& conn, void(*Handle)(Player* pl)) {
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&cn.addr, sizeof(cn.addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;
	bool search = false;
	while (true)
	{
		search = false;
		newConnection = accept(sListen, (SOCKADDR*)&cn.addr, &cn.sizeofaddr);
		if (newConnection == 0)
			cout << "Error Connection\n";
		else
			cout << "Connect\n";
		Player* pl = new Player;
		pl->connect = newConnection;
		pl->online = true;
		for (int i = 0; i < conn.size(); i++)
		{
			if (conn[i]->online == false) {
				conn[i] = pl;
				search = true;
				break;
			}
		}
		if (search == false)
			conn.push_back(pl);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Handle, pl, NULL, NULL);
	}
}
void Inithilization(Connect& cn, string ip, short int port) {
	cn.DLLversion = MAKEWORD(2, 2);
	if (WSAStartup(cn.DLLversion, &cn.wsaData) != 0) {
		cout << "Error 1\n";
		exit(1);
	}
	cn.sizeofaddr = sizeof(cn.addr);
	cn.addr.sin_addr.s_addr = inet_addr(ip.c_str());
	cn.addr.sin_port = htons(port);
	cn.addr.sin_family = AF_INET;
}
int sendEx(Player* pl,const char* buff, int size) {
	int res = 0;
	res = send(pl->connect, buff, size, NULL);
	if (res < 0) {
		DeletePlayer(pl);
		cout << "Disconnet\n";
		throw "Disconnect";
	}
	
	return res;
}
int recvEx(Player* pl, char* buff, int size) {
	int res;
	int i=0;
	res = recv(pl->connect, buff, size, MSG_PEEK);
	if (res <= 0) {
		DeletePlayer(pl);
		cout << "Disconnet\n";
		throw "Disconnect";
	}
	for (i = 0; i < res; i++) {
		if (buff[i] == '\0')
			break;
	}
	
	res = recv(pl->connect, buff,i+1, NULL);
	if (res <= 0) {
		DeletePlayer(pl);
		cout << "Disconnet\n";
		throw "Disconnect";
	}
	return res;
}
int sendR(Player* pl, const char* buff, int size) {
	int res = 0;
	res = send(pl->connect, buff, size, NULL);
	if (res < 0) {
		DeletePlayer(pl);
		cout << "Disconnet\n";
		return -1;
	}

	return res;
}
int recvR(Player* pl, char* buff, int size) {
	int res;
	int i = 0;
	res = recv(pl->connect, buff, size, MSG_PEEK);
	if (res <= 0) {
		DeletePlayer(pl);
		cout << "Disconnet\n";
		return -1;
	}
	for (i = 0; i < res; i++) {
		if (buff[i] == '\0')
			break;
	}

	res = recv(pl->connect, buff, i + 1, NULL);
	if (res <= 0) {
		DeletePlayer(pl);
		cout << "Disconnet\n";
		return -1;
	}
	return res;
}
