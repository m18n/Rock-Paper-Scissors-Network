#pragma once
#include"iostream"
#include"Player.h"
#include<vector>
using namespace std;
struct Room {
	string name="";
	vector<Player**>pl;
	int key=0;
	int size=0;
	string ops="";
};
void CreateRoom(Room* rm, int size, int key, string name, string ops);
void AddPlayer(Room* rm, Player** pl);
