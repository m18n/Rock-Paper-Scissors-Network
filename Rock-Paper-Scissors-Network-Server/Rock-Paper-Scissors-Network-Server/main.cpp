#define WIN32_LEAN_AND_MEAN
#include<iostream>
#include<vector>
#include<WinSock2.h>
#include<fstream>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
#include"Player.h"
#include"string.h"
#include"Network.h"
using namespace std;
void SingIn(Player& pl,char password[20]) {
	char temp[20];
	char score[10];
	ifstream fi("BD_Player/Player.txt");
	string temp2 = "";
	while (temp2 != pl.login)//search login
	{
		if (fi.tellg() == -1)
			break;
		fi >> temp2;
	}
	if (temp2 != pl.login) {
		strcpy_s(temp, "Error");
		sendEx(pl, temp, strlen(temp)+1);
		strcpy_s(temp, "");
		sendEx(pl, temp, strlen(temp)+1);
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
void SingUp(Player& pl, char password[20]) {
	ifstream fi("BD_Player/Player.txt");
	ofstream fs;
	char temp[10];
	string temp2 = "";
	while (temp2 != pl.login) {
		if (fi.tellg() ==-1)
			break;
		fi >> temp2;
	}
	if (temp2 == pl.login)
		strcpy_s(temp, "Error");
	else {
		strcpy_s(temp, "ok");
		fs.open("BD Player/Player.txt", ios_base::app);
		fs << "Login: " << pl.login << " Password: " << password << " Score: 0" << "\n";
		fs.close();
		fi.close();
	}
	sendEx(pl, temp, strlen(temp)+1);
	
}
void Login(Player& pl) {
	char password[20];
	char key[2];
	int size = sizeof(pl.login);
	try {
		recvEx(pl, key, sizeof(key));
		recvEx(pl, pl.login, size);
		recvEx(pl, password, sizeof(password));
	}
	catch(...){
		return;
	}
	if (key[0] == 'i') {
		SingIn(pl,password);
	}
	else if(key[0]=='u') {
		SingUp(pl,password);
	}
}
int main() {
	vector<Player*>conn;
	cout << "start server\n";
	Connect cn;
	Inithilization(cn, "192.168.0.103", 9999);
	ConnectSocket(cn,conn,Login);
	system("pause");
	return 0;
}
