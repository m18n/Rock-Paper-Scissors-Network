#include "Player.h"
void DeletePlayer(Player* pl) {
	if (pl->roome != NULL)
		pl->roome->onlineplayer--;
	pl->online = false;
	pl->ready = false;
	pl->roome = NULL;
	closesocket(pl->connect);
}