#include "ProcessClientMessage.h"

void Exec_MSG_Deposit(int conn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		AddCrackError(conn, 10, 1);
		return;
	}

	int coin = m->Parm;

	if (pMob[conn].MOB.Coin >= coin && coin >= 0 && coin <= 2000000000)
	{
		int tcoin = coin + pUser[conn].Coin;

		if (tcoin >= 0 && tcoin <= 2000000000)
		{
			pMob[conn].MOB.Coin -= coin;
			pUser[conn].Coin = tcoin;

			m->ID = ESCENE_FIELD;

			pUser[conn].cSock.AddMessage((char*)m, sizeof(MSG_STANDARDPARM));

			SendCargoCoin(conn);

			sprintf(temp, "etc,deposito no bau D:%d R:%d", coin, tcoin);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		}
		else
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
	}
	else
		SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Deposit_That_Much]);
}