#include <Windows.h>

void strip_xtrap()
{
	*(char*)0x5D9491 = 0xEB;
}

void strip_odd_connection_request()
{
	// This weird connection request to 211.115.86.66:2424 that always fails make the client laggy.
	// This patch kill the call.
	*(short*)0x5D8E8C = 0x9090;
}

int __stdcall DllMain(HINSTANCE hInstDLL, DWORD catchReason, LPVOID lpResrv)
{
	if (catchReason == DLL_PROCESS_ATTACH)
	{
		DWORD dwOldProtectFlag_text;

		VirtualProtect((void*)0x401000, 0x1F3000, PAGE_READWRITE, &dwOldProtectFlag_text);

		strip_xtrap();
		strip_odd_connection_request();

		VirtualProtect((void*)0x401000, 0x1F3000, dwOldProtectFlag_text, &dwOldProtectFlag_text);
	}
	else if (catchReason == DLL_PROCESS_DETACH)
	{
		FreeLibrary(hInstDLL);
	}

	return TRUE;
}