#include "Player.h"
void DeletePlayer(Player* pl) {
	pl->online = false;
	closesocket(pl->connect);
}