#include "Player.h"
void DeletePlayer(Player* pl) {
	if (pl->room != NULL)
		pl->room->onlineplayer--;
	pl->online = false;
	pl->ready = false;
	pl->room = NULL;
	closesocket(pl->connect);
}