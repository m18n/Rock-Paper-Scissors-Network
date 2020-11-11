#include "Room.h"
void AddPlayer(Room* rm, Player* pl) {
	for (int i = 0; i < rm->size; i++)
	{
		if (rm->pl[i] == NULL || rm->pl[i]->online == false) {
			rm->pl[i] = pl;
			break;
		}
	}
}
void CreateRoom(Room* rm, int size, int key, const char name[10],int sizename) {
	rm->intkey = key;
	strcpy_s(rm->key, to_string(key).c_str());
	rm->size = size;
	rm->online = true;
	rm->lengthname = sizename;
	strcpy_s(rm->name, name);
	rm->pl.resize(size);
}
void GenertyKey(vector<Room*>& rm, Room* r) {
	srand(time(0));
	int key = rand() % 10000;
	for (int i = 0; i < rm.size(); i++) {
		if (rm[i]->intkey == key) {
			key = rand() % 10000;
			i = 0;
		}
	}
	r->intkey = key;
	strcpy_s(r->key,to_string(key).c_str());
}
void DeleteRoom(Room* rm) {
	rm->intkey = 0;
	rm->size = 0;
	for (int i = 0; i < rm->pl.size(); i++) {
		DeletePlayer(rm->pl[i]);
	}
	rm->online = false;
}
void AddRoom(vector<Room*>& vrm, Room* rm) {
	bool search = false;
	for (int i = 0; i < vrm.size(); i++)
	{
		if (vrm[i]->online == false) {
			vrm[i] = rm;
			search = true;
			break;
		}
	}
	if (search == false)
		vrm.push_back(rm);
}