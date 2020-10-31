#pragma once
#include"iostream"
#include"Player.h"
#include<vector>
#include"time.h"
using namespace std;
struct Room {
	char name[10];
	vector<Player*>pl;
	int key=0;
	int size=0;
	bool online = false;
};
void CreateRoom(Room* rm, int size, int key,const char name[10]);
void AddPlayer(Room* rm, Player* pl);
void GenertyKey(vector<Room*>& rm, Room* r);
void AddRoom(vector<Room*>& vrm, Room* rm);
void DeleteRoom(Room* rm);