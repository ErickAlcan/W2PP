#include "ProcessClientMessage.h"

void Exec_MSG_DeleteItem(int conn, char *pMsg)
{
	MSG_DeleteItem *m = (MSG_DeleteItem*)pMsg;

	if (m->Slot < 0 || m->Slot >= MAX_CARRY - 4)
		return;

	if (m->sIndex <= 0 || m->sIndex >= MAX_ITEMLIST)
		return;

	if (pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}
	char itemtmp[2048];
	BASE_GetItemCode(&pMob[conn].MOB.Carry[m->Slot], itemtmp);

	sprintf(temp, "deleteitem, %s", itemtmp);
	ItemLog(temp, pMob[conn].MOB.MobName, pUser[conn].IP);

	memset(&pMob[conn].MOB.Carry[m->Slot], 0, sizeof(STRUCT_ITEM));
}