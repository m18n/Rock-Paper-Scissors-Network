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
void CreateRoom(Room* rm, int size, int key, string name, string ops) {
	rm->key = key;
	rm->size = size;
	rm->name = name;
	rm->ops;
	rm->pl.resize(size);
}