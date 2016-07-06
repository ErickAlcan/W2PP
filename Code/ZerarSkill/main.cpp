#include "main.h"

int readAccountsInDir(char *dir)
{
	HANDLE handle;
	WIN32_FIND_DATA win32_find_data;

	int entryCount = 0;

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
				sprintf(tmp, "./account/%s/*", fileName);
				entryCount += readAccountsInDir(tmp);
			}
			else
			{
				strcpy(tmp, dir);
				tmp[strlen(dir) - 1] = '\0';
				sprintf(tmp, "%s%s", tmp, fileName);

				errno = 0;

				FILE* fs;
				fopen_s(&fs, tmp, "rb");

				STRUCT_ACCOUNTFILE accBuffer;

				if (fs != NULL)
				{
					int fsize = 0;

					fseek(fs, 0, SEEK_END);
					fsize = ftell(fs);
					fseek(fs, 0, SEEK_SET);

					if ((fsize >= 7500 && fsize <= 8900) || fsize == sizeof(STRUCT_ACCOUNTFILE))
					{
						//STRUCT_ACCOUNTFILE accBuffer;
						memset(&accBuffer, 0, sizeof(STRUCT_ACCOUNTFILE));

						fread(&accBuffer, sizeof(STRUCT_ACCOUNTFILE), 1, fs);

						for (int i = 0; i < MOB_PER_ACCOUNT; i++)
						{
							if (accBuffer.Char[i].MobName[0] == '\0')
								continue;
#pragma region Skill
							if ((1 << 7) & accBuffer.Char[i].LearnedSkill)
							{
								accBuffer.Char[i].LearnedSkill &= 0xFFFFFF7F;
								accBuffer.Char[i].Coin += 5000000;
							}
							if ((1 << 15) & accBuffer.Char[i].LearnedSkill)
							{
								accBuffer.Char[i].LearnedSkill &= 0xFFFF7FFF;
								accBuffer.Char[i].Coin += 5000000;
							}
							if ((1 << 23) & accBuffer.Char[i].LearnedSkill)
							{
								accBuffer.Char[i].LearnedSkill &= 0xFF7FFFFF;
								accBuffer.Char[i].Coin += 5000000;
							}
#pragma endregion

							for (int j = 0; j < MAX_CARRY; j++)
							{
								if (accBuffer.Char[i].Carry[j].sIndex == 3338)
								{
									memset(&accBuffer.Char[i].Carry[j], 0, sizeof(STRUCT_ITEM));
									accBuffer.Donate += 50;
								}

								if (accBuffer.Char[i].Carry[j].sIndex == 4043)
								{
									memset(&accBuffer.Char[i].Carry[j], 0, sizeof(STRUCT_ITEM));
									accBuffer.Donate += 75;
								}
							}

							entryCount++;
						}

						for (int j = 0; j < MAX_CARGO; j++)
						{
							if (accBuffer.Cargo[j].sIndex == 3338)
							{
								memset(&accBuffer.Cargo[j], 0, sizeof(STRUCT_ITEM));
								accBuffer.Donate += 50;
							}

							if (accBuffer.Cargo[j].sIndex == 4043)
							{
								memset(&accBuffer.Cargo[j], 0, sizeof(STRUCT_ITEM));
								accBuffer.Donate += 75;
							}
						}
					}
					else
					{
						// TODO: file don't have the right size
					}

					fclose(fs);

					fopen_s(&fs, tmp, "wb");
					fwrite(&accBuffer, sizeof(STRUCT_ACCOUNTFILE), 1, fs);
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

	return entryCount;
}

int main()
{
	readAccountsInDir("./account/*");
	return 1;
}