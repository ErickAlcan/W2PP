#ifndef _CUSER_ // Last updated July 2012
#define _CUSER_

#include "../Basedef.h"
#include "../CPSock.h"

#include "Main.h"

#define USER_EMPTY    0   // is empty
#define USER_ACCEPT   1   // ACCEPT state after connected

class CUser
{
public:
	unsigned int    IP;
	int    Mode;
	CPSock cSock;
	int    Count;
	int    Level;
	int    Encode1;
	int    Encode2;
	char   Name[ACCOUNTNAME_LENGTH];
	int    DisableID;
	int	   DB;
	int	   Session;
	int	   State;
	STRUCT_ACCOUNTFILE NPAccount;
public:
	CUser();
	~CUser();
};

#endif