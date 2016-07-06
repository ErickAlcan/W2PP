#include "main.h"

STRUCT_MOB MOB[MAX_MOB];
int CurrentMob = 0;

using namespace std;

int ItemException[6500][2];
short CountException;

int main()
{
	ReadItensExceptions();
	LoadMobsInDir("./npc/*");

	FILE *fp = fopen("ItemDropList.txt", "w");
	FILE *fs = fopen("MobDropList.txt", "w");

	BASE_InitializeItemList();

	for (int i = 1; i < MAX_ITEMLIST; i++)
	{
		list<char *> MobList;

		for (int j = 0; j < CurrentMob; j++)
		{
			for (int k = 0; k < MAX_CARRY; k++)
			{
				int l = 0;

				for (l = 0; l < CountException; l++)
				{
					if (i >= ItemException[l][0] && i <= ItemException[l][1])
						break;
				}

				if (MOB[j].Carry[k].sIndex == i && l == CountException)
				{
					MobList.push_back(MOB[j].MobName);
					break;
				}
			}
		}

		int count = 0;
		fprintf(fp, "Item: %d:%s Mobs que dropam:%d\r\n", i, g_pItemList[i].Name, MobList.size());

		for (list<char*>::iterator l = MobList.begin(); l != MobList.end(); ++l)
		{
			list<char *>::iterator checkEnd = MobList.end();
			--checkEnd;
			
			fprintf(fp, "%s, ", *l);

			if (l == checkEnd)
			{
				fprintf(fp, "\r\n");
				continue;
			}

			if (++count % 8 == 0)
				fputs("\r\n", fp);
		}

		fputs("\r\n", fp);
	}

	for (int i = 0; i < CurrentMob; i++)
	{
		fprintf(fs, "Mob: %s\r\n", MOB[i].MobName);

		int count = 0;

		for (int j = 0; j < MAX_CARRY; j++)
		{
			if (MOB[i].Carry[j].sIndex == 0)
				continue;

			fprintf(fs, "%s, ", g_pItemList[MOB[i].Carry[j].sIndex].Name);

			if (++count % 8 == 0)
				fputs("\r\n", fs);
		}

		if (count % 8)
			fputs("\r\n", fs);

		fputs("\r\n", fs);
	}
	return 1;
}

void LoadMobsInDir(char *dir)
{
	HANDLE handle;
	WIN32_FIND_DATA win32_find_data;

	char tmp[1024];

	handle = FindFirstFile(dir, &win32_find_data);

	if (handle == INVALID_HANDLE_VALUE)
	{
		// TODO: Error: can't read initial file
	}
	else
	{
		while (FindNextFile(handle, &win32_find_data))
		{
			char *fileName = win32_find_data.cFileName;

			if (!strncmp(fileName, ".", 1))
				continue;

			if (win32_find_data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				sprintf(tmp, "./npc/*", fileName);
				LoadMobsInDir(tmp);
			}
			else
			{
				strcpy(tmp, dir);
				tmp[strlen(dir) - 1] = '\0';
				sprintf(tmp, "%s%s", tmp, fileName);

				errno = 0;

				FILE* fs;
				fopen_s(&fs, tmp, "rb");

				if (fs != NULL)
				{
					int fsize = 0;

					fseek(fs, 0, SEEK_END);
					fsize = ftell(fs);
					fseek(fs, 0, SEEK_SET);

					if (fsize == sizeof(STRUCT_MOB))
					{
						fread(&MOB[CurrentMob], sizeof(STRUCT_MOB), 1, fs);

						CurrentMob++;
					}
					else
					{
						// TODO: file don't have the right size
					}

					fclose(fs);
				}
				else
				{
					// TODO: Cant open file to read
				}
			}
		}
	}

	FindClose(handle);

	return;
}

void ReadItensExceptions()
{
	FILE *fp = NULL;

	fp = fopen("ItensExceptions.txt", "rb");

	if (fp == NULL)
	{
		MessageBoxA(NULL, "Não foi possivel encontrar ItensExceptions.txt", "Aviso", MB_OK);
		return;
	}
	char tmp[256];

	while (1)
	{
		char *ret = fgets(tmp, 255, fp);

		if (ret == NULL)
			break;

		if (tmp[0] == '#')
			continue;

		sscanf(tmp, "%d,%d", &ItemException[CountException][0], &ItemException[CountException][1]);


		CountException++;
	}

	fclose(fp);
}