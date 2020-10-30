#include "Room.h"
void AddPlayer(Room* rm, Player** pl) {
	bool search = false;
	for (int i = 0; i < rm->size; i++)
	{
		if ((*rm->pl[i])->online == false) {
			rm->pl[i] = pl;
			search = true;
			break;
		}
	}
	if (search == false)
		rm->pl.push_back(pl);
}
void CreateRoom(Room* rm, int size, int key, const char name[10]) {
	rm->key = key;
	rm->size = size;
	strcpy_s(rm->name, name);
	rm->pl.resize(size);
}
void GenertyKey(vector<Room*>& rm, Room* r) {
	srand(time(0));
	int key = rand() % 10000;
	for (int i = 0; i < rm.size(); i++) {
		if (rm[i]->key == key) {
			key = rand() % 10000;
			i = 0;
		}
	}
	r->key = key;
}