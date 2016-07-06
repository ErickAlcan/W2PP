#ifndef __CMOB__
#define __CMOB__

#include "..\Basedef.h"

#define MAX_ENEMY 13

#define MOB_EMPTY 0  // There's no mob on the slot
#define MOB_USERDOCK    1
#define MOB_USER		2
#define MOB_IDLE        3
#define MOB_PEACE		4
#define MOB_COMBAT      5
#define MOB_RETURN		6
#define MOB_FLEE		7
#define MOB_ROAM		8
#define MOB_WAITDB		9

class CMob
{
public:
	STRUCT_MOB    MOB;//
	STRUCT_AFFECT Affect[MAX_AFFECT];
	int Mode;
	int Leader;
    int Formation;
	int RouteType;
	int LastX;
	int LastY;
	int LastTime;
	int LastSpeed;
	int TargetX;
	int TargetY;
	int NextX;
	int NextY;
	int NextAction;
	char Route[MAX_ROUTE];
	int WaitSec;
	char Unk5[12];
	int Segment;
	int SegmentX;
	int SegmentY;
	int SegmentListX[5];
	int SegmentListY[5];
	int SegmentWait[5];
	int SegmentRange[5];
	int SegmentDirection;
	int SegmentProgress;
	int GenerateIndex;
	short CurrentTarget;
	short EnemyList[MAX_ENEMY];
	short PartyList[MAX_PARTY];
	short Unk7;
	int WeaponDamage;
	int Summoner;
	int PotionCount;
	int Parry;
	int GuildDisable;
	int DropBonus;
	int ExpBonus;
	int ForceDamage;
	int ReflectDamage; 


	//********************
	STRUCT_MOBEXTRA extra;

	char Tab[36];
	char Snd[96];

	int ForceMobDamage;
	int Accuracy;
	int HpAbs;

	int PvPDamage;
	int ReflectPvP; 

	int MaxCarry;
	int QuestFlag;

	int LastReqParty;
	unsigned int ProcessorCounter;
public:

	CMob();
	~CMob();

	void ProcessorSecTimer         ();
	int StandingByProcessor       (void);
	int BattleProcessor           ();
	void AddEnemyList              (short TargetId);
	void RemoveEnemyList	       (short TargetId);
	void SelectTargetFromEnemyList (void);
	int SetSegment                (void);                // 1:ShipMove   0:DeleteObject
	void GetCurrentScore           (int idx); 
	void GetTargetPosDistance      (int tz);
	void GetRandomPos              ();
	void GetTargetPos              (int tz);
	int  CheckGetLevel             ();
	void GetNextPos                (int battle);
   	int  GetEnemyFromView	       (void);
};

extern CMob pMob[MAX_MOB];
#endif