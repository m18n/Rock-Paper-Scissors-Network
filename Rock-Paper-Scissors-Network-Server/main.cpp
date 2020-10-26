#include<iostream>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
struct Player {
	char login[20];
	int password=0;
	int score=0;
};
struct Connect {
	WSAData wsaData;
	WORD DLLversion;
	SOCKADDR_IN addr;
};

void Inithilization(Connect& cn,string ip,short int port) {
	cn.DLLversion = MAKEWORD(2, 1);
	if (WSAStartup(cn.DLLversion, &cn.wsaData)!=0) {
		cout << "Error 1\n";
		exit(1);
	}
	cn.addr.sin_addr.s_addr = inet_addr(ip.c_str());
	cn.addr.sin_port = htons(port);
	cn.addr.sin_family = AF_INET;
}
int main() {
	cout << "start server\n";
	Connect cn;
	Inithilization(cn,"192.168.0.103",9999);
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&cn.addr,sizeof(cn.addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;
	
	
	system("pause");
	return 0;
}