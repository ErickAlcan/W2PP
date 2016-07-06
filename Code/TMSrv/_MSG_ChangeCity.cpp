#include "ProcessClientMessage.h"

void Exec_MSG_ChangeCity(int conn, char *pMsg)
{
	int tx = pMob[conn].TargetX;
	int ty = pMob[conn].TargetY;

	int city = BASE_GetVillage(tx, ty);

	if (city >= 0 && city <= 4)
	{
		pMob[conn].MOB.Merchant &= 0x3F;
		pMob[conn].MOB.Merchant |= city << 6;
	}

	sprintf(temp, "etc,changecity city:%d X:%d Y:%d", city, tx, ty);
	Log(temp, pUser[conn].AccountName, 0);
}