#define WIN32_LEAN_AND_MEAN
#include<iostream>
#include<vector>
#include<WinSock2.h>
#include<fstream>
#include"string"
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
#include"Player.h"
#include"string.h"
#include"Network.h"
#include"Room.h"
using namespace std;
vector<Room*>rm;
bool SingIn(Player* pl, char password[20]) {
	char temp[20];
	char score[10];
	ifstream fi("BD_Player/Player.txt");
	string temp2 = "";
	bool suc = false;
	while (temp2 != pl->login)//search login
	{
		if (fi.tellg() == -1)
			break;
		fi >> temp2;
	}
	if (temp2 != pl->login) {
		strcpy_s(temp, "Error");
		sendEx(pl, temp, strlen(temp) + 1);
		strcpy_s(temp, "");
		sendEx(pl, temp, strlen(temp) + 1);
	}
	else {
		fi >> temp2;
		fi >> temp2;//password
		fi >> score;
		fi >> score;
		if (strcmp(temp2.c_str(), password) != 0) {
			strcpy_s(pl->login, "");
			pl->password = 0;
			strcpy_s(temp, "Error");
			strcpy_s(score, "");
		}
		else {
			pl->password = atoi(password);
			strcpy_s(temp, "ok");
			suc = true;
		}
		sendEx(pl, temp, strlen(temp) + 1);
		sendEx(pl, score, strlen(score) + 1);
	}
	fi.close();
	return suc;
}
int SearchRoom(int keyroom) {
	for (int i = 0; i < rm.size(); i++)
	{
		if (rm[i]->key == keyroom) {
			return i;
		}
	}
}
int NumberPlayerRoom(Room* r) {
	int player = 0;
	for (int i = 0; i < r->size; i++) {
		if (r->pl[i] != NULL && r->pl[i]->online == true) {
			player++;
		}
	}
	return player;
}
void ConnectRoom(Player* pl, Room** r) {
	char keyroom[6];
	recvEx(pl, keyroom, sizeof(keyroom));
	*r = rm[SearchRoom(atoi(keyroom))];
	sendEx(pl, (*r)->name, strlen((*r)->name)+1);
	AddPlayer(*r, pl);
	int pler = NumberPlayerRoom(*r);
	cout << "Room: " << (*r)->key << " Name: " << (*r)->name << " Maxplayer: " << (*r)->size << " Player: " << pler << "\n";
}
void CreteRoom(Player* pl,Room* r) {
	char name[10];
	char maxplayer[4];
	char keyroom[6];
	recvEx(pl, name, sizeof(name));
	recvEx(pl, maxplayer, sizeof(maxplayer));
	CreateRoom(r, atoi(maxplayer), 0, name);
	GenertyKey(rm, r);
	AddRoom(rm, r);
	AddPlayer(r, pl);
	strcpy_s(keyroom, to_string(r->key).c_str());
	sendEx(pl, keyroom, strlen(keyroom)+1);
	cout << "Room: " << r->key << " Name: " << r->name << " Maxplayer: " << maxplayer << "\n";
}
bool Notification(Room* r) {
	char buff[30];
	char maxplayer[4];
	int number = NumberPlayerRoom(r);
	strcpy_s(maxplayer,to_string(number).c_str());
	int index = 0;
	try
	{
		for (int i = 0; i < r->size; i++) {
			if (r->pl[i] != NULL && r->pl[i]->online == true) {
				index = i;
				sendEx(r->pl[i], maxplayer, strlen(maxplayer) + 1);
				for (int j = 0; j < r->size; j++) {
					if (r->pl[j] != NULL && r->pl[j]->online == true) {
						strcpy(buff, "Name: ");
						strcat(buff, r->pl[j]->login);
						strcat(buff, " Ready: ");
						if(r->pl[j]->ready==true)
							strcat(buff, "true");
						else
							strcat(buff, "false");
						index = j;
						sendEx(r->pl[i],buff,strlen(buff)+1);
					}
				}
			}
		}
	}
	catch (...)
	{
		DeletePlayer(r->pl[index]);
		return false;
	}
	return true;
}
void Menu(Player* pl) {
	char key[2];
	try
	{
		recvEx(pl, key, sizeof(key));
		if (key[0] == 'r') {//create
			Room* r = new Room;
			CreteRoom(pl,r);
		}
		else if (key[0] == 's') {//search

		}
		else if (key[0] == 'c') {//connect
			Room* r=NULL;
			ConnectRoom(pl,&r);
			bool temp=false;
			while (temp != true) {
				temp = Notification(r);
			}
		}
	}
	catch (...)
	{
		return;
	}
}
bool SingUp(Player* pl, char password[20]) {
	ifstream fi("BD_Player/Player.txt");
	ofstream fs;
	bool suc = false;
	char temp[10];
	string temp2 = "";
	while (temp2 != pl->login) {
		if (fi.tellg() == -1)
			break;
		fi >> temp2;
	}
	if (temp2 == pl->login)
		strcpy_s(temp, "Error");
	else {
		strcpy_s(temp, "ok");
		fs.open("BD_Player/Player.txt", ios_base::app);
		fs << "Login: " << pl->login << " Password: " << password << " Score: 0" << "\n";
		fs.close();
		fi.close();
		suc = true;
	}
	sendEx(pl, temp, strlen(temp) + 1);
	return suc;
}
int Login(Player* pl) {
	char password[20];
	char key[2];
	bool suc = false;
	int size = sizeof(pl->login);
	try {
		recvEx(pl, key, sizeof(key));
		recvEx(pl, pl->login, size);
		recvEx(pl, password, sizeof(password));
	}
	catch (...) {
		return 3;
	}
	if (key[0] == 'i') 
		suc=SingIn(pl, password);
	else if (key[0] == 'u')
		suc=SingUp(pl, password);
	return suc;
}
void Meneger(Player* pl) {
	int suc=0;
	while (suc != 1) {
		suc = Login(pl);
		if (suc == 3)
			return;
	}
	Menu(pl);
}
int main() {
	vector<Player*>conn;

	cout << "start server\n";
	Connect cn;
	Inithilization(cn, "192.168.0.104", 9999);
	ConnectSocket(cn, conn, Meneger);
	system("pause");
	return 0;
}
