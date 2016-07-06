#include "ProcessClientMessage.h"

void Exec_MSG_SetShortSkill(int conn, char *pMsg)
{
	MSG_SetShortSkill *m = (MSG_SetShortSkill*)pMsg;

	memcpy(pMob[conn].MOB.SkillBar, m->Skill1, 4);
	memcpy(pUser[conn].CharShortSkill, m->Skill2, 16);
}