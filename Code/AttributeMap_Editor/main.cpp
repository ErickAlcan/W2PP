#include <Windows.h>
#include <stdio.h>

unsigned char g_pAttribute[1024][1024];

int main()
{
	FILE *fp = fopen("AttributeMap.dat", "rb");

	if (fp == NULL)
	{
		MessageBoxA(NULL, "There is no file", "AttributeMap.dat", MB_OK);

		return FALSE;
	}

	fread(g_pAttribute, 1024, 1024, fp);

	fclose(fp);

	int xx = g_pAttribute[2100 / 4][2100 / 4];

	for (int x = 0; x < 1024; x++)
	{
		for (int y = 0; y < 1024; y++)
		{
			//if ((g_pAttribute[y][x] & 64) != 0 && (g_pAttribute[y][x] & 1) != 0)
			//	g_pAttribute[y][x] |= 64;

			if (g_pAttribute[y][x] < 64 && g_pAttribute[y][x] != 1)
				g_pAttribute[y][x] |= 64;
		}
	}
	
	fp = fopen("AttributeMap_New.dat", "wb");

	fwrite(g_pAttribute, 1024, 1024, fp);

	fclose(fp);

	//0: PvE sem PvP
	//1: Cidade
	//4: Não é permitido marcar Gema
	//64: PvP que perde XP
	system("pause");
	return 1;
}