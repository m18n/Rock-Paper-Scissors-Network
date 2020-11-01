#include "Player.h"
void DeletePlayer(Player* pl) {
	pl->online = false;
	pl->ready = false;
	closesocket(pl->connect);
}