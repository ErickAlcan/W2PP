#include "CUser.h"

extern HWND hWndMain;

CUser::CUser()
{
	Mode = USER_EMPTY;
	IP   = 0;
	Count = 0;
	DisableID = 0;
	Level = -1;
	Encode1 = 0;
	Encode2 = 0;
}

CUser::~CUser()
{
}
