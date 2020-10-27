#include<iostream>
#include<vector>
#include<WinSock2.h>
#include<fstream>
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
void Inithilization(Connect& cn, string ip, short int port) {
	cn.DLLversion = MAKEWORD(2, 1);
	if (WSAStartup(cn.DLLversion, &cn.wsaData) != 0) {
		cout << "Error 1\n";
		exit(1);
	}
	cn.sizeofaddr = sizeof(cn.addr);
	cn.addr.sin_addr.s_addr = inet_addr(ip.c_str());
	cn.addr.sin_port = htons(port);
	cn.addr.sin_family = AF_INET;
}
void Login(Player& pl) {
	char password[20];
	char key[1];
	char temp[10];
	recv(pl.connect, key, sizeof(key), NULL);
	recv(pl.connect,pl.login,sizeof(pl.login),NULL);
	recv(pl.connect,password,sizeof(password),NULL);
	ifstream fi("BD Player/Player.txt");
	string login = "";
	if (key[0] == 'i') {
		while (login != pl.login)
			fi >> login;
		if (login != pl.login) {
			strcpy_s(temp, "Error");
			send(pl.connect, temp, strlen(temp), NULL);
		}
		else {
			fi >> login;
			if(strcmp(login.c_str(),password)!=0)
				strcpy_s(temp, "Error");
			else
				strcpy_s(temp, "ok");
			send(pl.connect, temp, strlen(temp), NULL);
		}
	}
	else if(key[0]=='u') {
		ofstream fs;
		while (login != pl.login)
			fi >> login;
		if (login == pl.login)
			strcpy_s(temp, "Error");
		else
			strcpy_s(temp, "ok");
		send(pl.connect, temp, strlen(temp), NULL);
		fs.open("BD Player/Player.txt", ios_base::app);
		fs << "Login: " << pl.login << " Password: " << password;
		fs.close();
		
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
