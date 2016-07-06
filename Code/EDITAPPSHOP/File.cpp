#include "File.h"
#include "resource.h"

extern HWND hWndMain;
extern char temp[1024];



int  ReadMob(STRUCT_MOB *mob, char *dir)
{
	sprintf(temp, "./%s/%s", dir, mob->MobName);

	int Handle = _open(temp, O_RDONLY | O_BINARY);

	if (Handle == -1)
	{
		if (errno == EINVAL)
			sprintf(temp, "err,ReadMob EEXIST", mob->MobName);

		else if (errno == EMFILE)
			sprintf(temp, "err,ReadMob EMFILE", mob->MobName);

		else if (errno == ENOENT)
			sprintf(temp, "err,ReadMob ENOENTN", mob->MobName);

		else
			sprintf(temp, "err,ReadMob UNKNOW", mob->MobName);

		SetWindowText(hWndMain, temp);
		return FALSE;
	}

	strcpy(temp, mob->MobName);

	int ret = _read(Handle, mob->MobName, sizeof(STRUCT_MOB));

	if (ret == -1)
	{
		_close(Handle);

		return FALSE;
	}

	_close(Handle);

	strcpy(mob->MobName, temp);

	BASE_GetEnglish(mob->MobName);

	mob->BaseScore = mob->CurrentScore;

	return TRUE;
}

void ReadMob(char *dir)
{
	char filename[256];
	char movefile[256];
	char *getret;
	struct _finddata_t c_file;
	FILE *fp;

	sprintf(temp, "./%s/*.*", dir);

	int hFindFile = _findfirst(temp, &c_file);

	if (hFindFile == -1)
		return;

	int count = 0;

	while (1)
	{
		if (c_file.name[0] == '.')
		{
			int ret = _findnext(hFindFile, &c_file);

			if (ret != 0)
				break;

			continue;
		}

		sprintf(filename, "./%s/%s", dir, c_file.name);

		strcpy(LoadMob[count].MobName, c_file.name);
		ReadMob(&LoadMob[count], dir);

		if (LoadMob[count].Merchant != 1 && LoadMob[count].Merchant != 19)
		{
			if (_findnext(hFindFile, &c_file) != 0)
				break;

			continue;
		}
		SendDlgItemMessage(hWndMain, IDC_LNPCList, LB_ADDSTRING, 0, (LPARAM)c_file.name);

		count++;

		if (_findnext(hFindFile, &c_file) != 0)
			break;

		continue;

	}

	if (hFindFile != -1)
		_findclose(hFindFile);
}