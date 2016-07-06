#pragma once

#include <stdio.h>
#include "..\Basedef.h"


class CWarTower
{
public:
	CWarTower();

public:

	static void GuildProcess(tm *timeinfo);

	static void MobKilled(int target, int conn, int PosX, int PosY);
	static void GGenerateMob(int index, int PosX, int PosY, int tmob);
	static BOOL TowerAttack(int conn, int idx);
};
