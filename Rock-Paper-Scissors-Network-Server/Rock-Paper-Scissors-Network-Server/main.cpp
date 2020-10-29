#define WIN32_LEAN_AND_MEAN
#include<iostream>
#include<vector>
#include<WinSock2.h>
#include<fstream>
#include"string.h"
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
using namespace std;
struct Player {
	char login[20]="";
	int password = 0;
	int score = 0;
	SOCKET connect=NULL;
	bool online=false;
};
vector<Player*> conn;
struct Connect {
	WSAData wsaData;
	WORD DLLversion;
	SOCKADDR_IN addr;
	int sizeofaddr;
};
void recvEx(Player& pl, char* buff, int size) {
	int res = recv(pl.connect, buff, size, NULL);
	if (res <= 0) {
		closesocket(pl.connect);
		pl.online = false;
		cout << "Disconnet\n";
		throw "Disconnect";
	}
}
void sendEx(Player& pl, const char* buff, int size) {
	int res = send(pl.connect, buff, size, NULL);
	if (res < 0) {
		closesocket(pl.connect);
		pl.online = false;
		cout << "Disconnet\n";
		throw "Disconnect";
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
void SingIn(Player& pl,char password[20]) {
	char temp[10];
	char score[10];
	ifstream fi("BD Player/Player.txt");
	string temp2 = "";
	while (temp2 != pl.login)//search login
		fi >> temp2;
	if (temp2 != pl.login) {
		strcpy_s(temp, "Error");
		sendEx(pl, temp, strlen(temp));
	}
	else {
		fi >> temp2;
		fi >> temp2;//password
		fi >> score;
		fi >> score;
		if (strcmp(temp2.c_str(), password) != 0) {
			strcpy_s(pl.login, "");
			pl.password = 0;
			strcpy_s(temp, "Error");
			strcpy_s(score, "");
		}
		else {
			pl.password = atoi(password);
			strcpy_s(temp, "ok");
		}
		sendEx(pl, temp, strlen(temp) + 1);
		sendEx(pl, score, strlen(score) + 1);
	}
	fi.close();
}
void SingUp(Player& pl) {
	ifstream fi("BD Player/Player.txt");
	ofstream fs;
	char temp[10];
	char password[20];
	string temp2 = "";
	while (temp2 != pl.login)
		fi >> temp2;
	if (temp2 == pl.login)
		strcpy_s(temp, "Error");
	else
		strcpy_s(temp, "ok");
	sendEx(pl, temp, strlen(temp));
	fs.open("BD Player/Player.txt", ios_base::app);
	fs << "Login: " << pl.login << " Password: " << password << " Score: 0" << "\n";
	fs.close();
	fi.close();
}
void Login(Player& pl) {
	char password[20];
	char key[2];
	int size = sizeof(pl.login);
	try {
		recvEx(pl, key, sizeof(key));
		recvEx(pl, pl.login, size);
		recvEx(pl, password, 20);
	}
	catch(...){
		return;
	}
	if (key[0] == 'i') {
		SingIn(pl,password);
	}
	else if(key[0]=='u') {
		SingUp(pl);
	}
}
void ConnectSocket(Connect& cn) {
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
		if(search==false)
			conn.push_back(pl);
		CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)Login,pl,NULL,NULL);
	}
}
int main() {
	cout << "start server\n";
	Connect cn;
	Inithilization(cn, "192.168.0.103", 9999);
	ConnectSocket(cn);
	system("pause");
	return 0;
}
