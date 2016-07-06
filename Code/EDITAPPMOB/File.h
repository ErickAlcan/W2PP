#pragma once

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h> 
#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <string.h>        
#include <time.h>
#include <errno.h>

#include "Main.h"
#include "..\Basedef.h"

int  ReadMob(STRUCT_MOB *mob, char *dir);
void ReadMob(char *dir);