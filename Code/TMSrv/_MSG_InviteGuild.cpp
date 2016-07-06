#include "ProcessClientMessage.h"

void Exec_MSG_InviteGuild(int conn, char *pMsg)
{
	MSG_STANDARDPARM2 *m = (MSG_STANDARDPARM2*)pMsg;

	int TargetID = m->Parm1;
	int InviteType = m->Parm2;

	if (TargetID <= 0 || TargetID >= MAX_USER)
		return;

	if (InviteType < 0 || InviteType >= 4)
		return;

	if (pMob[conn].MOB.Guild == 0)
		return;
							 

	if (pMob[TargetID].MOB.Guild != 0)
		return;
							 
	if (pMob[conn].MOB.Clan != pMob[TargetID].MOB.Clan)
		return;
							 

	if (pMob[conn].MOB.GuildLevel == 0)
		return;
							 

	if (InviteType != 0 && pMob[conn].MOB.GuildLevel != 9)
		return;
							 

	time_t rawtime;
	tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if(timeinfo->tm_wday == 0)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_NotEquip_Saturday]);
		return;
	}

	int custo = 4000000;

	if (InviteType != 0)
		custo = 100000000;

	if (pMob[conn].MOB.Coin < custo)
		return;

	pMob[conn].MOB.Coin -= custo;
	SendEtc(conn);

	pMob[TargetID].MOB.Guild = pMob[conn].MOB.Guild;
	pMob[TargetID].MOB.GuildLevel = 0;

	sprintf(temp, "etc,inviteguild guild:%d target_name:%s", pMob[conn].MOB.Guild, pMob[TargetID].MOB.MobName);
	Log(temp, pMob[conn].MOB.MobName, pUser[conn].IP);

	int Group = ServerGroup;
	int Server = pMob[conn].MOB.Guild / MAX_GUILD;
	int usGuild = pMob[conn].MOB.Guild;

	char guildname[256];

	BASE_GetGuildName(Group, usGuild, guildname);

	sprintf(temp, g_pMessageStringTable[_SN_JOINGUILD], guildname);
	SendClientMessage(TargetID, temp);

	MSG_CreateMob sm_ig;
	memset(&sm_ig, 0, sizeof(MSG_STANDARDPARM2));

	GetCreateMob(TargetID, &sm_ig);

	GridMulticast(pMob[TargetID].TargetX, pMob[TargetID].TargetY, (MSG_STANDARD*)&sm_ig, 0);
}