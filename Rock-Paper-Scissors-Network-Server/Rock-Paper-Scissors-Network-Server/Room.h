#pragma once
#include"iostream"
#include<string>
#include<vector>
#include"time.h"
using namespace std;
struct Player;
#include"Player.h"
struct Room {
	char name[10];
	int lengthname=0;
	vector<Player*>pl;
	char key[6];
	int onlineplayer = 0;
	int intkey = 0;
	int size=0;
	bool online = false;
};

void CreateRoom(Room* rm, int size, int key,const char name[10],int sizename);
void AddPlayer(Room* rm, Player* pl);
void GenertyKey(vector<Room*>& rm, Room* r);
void AddRoom(vector<Room*>& vrm, Room* rm);
void DeleteRoom(Room* rm);