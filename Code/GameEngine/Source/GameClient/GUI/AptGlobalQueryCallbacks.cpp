// cl: /O1 /DNDEBUG /MD
//
// BFME2's global Apt queries, free functions bound by these names
// ("InBetaDemo", "InGame", "DoTrace" ...) through the free-function holder
// 0x004106FA by the global registration 0x00412F14; that binding is their
// only reference. Each answers into the result buffer unless the query is
// a write (skip). A body bound under several names keeps an address name.

extern "C" char *__cdecl strcpy(char *destination, const char *source);

// TheGlobalData's +0x9D4 (the demo kind the queries compare against).
class GlobalData;
extern GlobalData *TheGlobalData;

struct AptGlobalQueryData
{
	unsigned char m_pad000[0x9D4];
	int m_demoKind; // +0x9D4
};

// The trace flag GlobalByteFlagSetters.cpp's Rva004128E8SetFlag sets.
extern unsigned char g_Va00E0302C;

// Retail 0x0041273C, 75 bytes: bound as "InBetaDemo" (query 1) and
// "InDreamMachineDemo" (query 2).
void __cdecl Rva0041273C(int query, char *result, bool skip)
{
	if (!result || skip)
		return;
	switch (query)
	{
	case 1:
		strcpy(result, ((AptGlobalQueryData *)TheGlobalData)->m_demoKind == 1 ? "1" : "0");
		break;
	case 2:
		strcpy(result, ((AptGlobalQueryData *)TheGlobalData)->m_demoKind == 2 ? "1" : "0");
		break;
	}
}

// Retail 0x00412787, 31 bytes: "InGame".
void __cdecl InGame(int query, char *result, bool skip)
{
	if (result && !skip)
		strcpy(result, "1");
}

// Retail 0x004127A6, 45 bytes: "DoTrace".
void __cdecl DoTrace(int query, char *result, bool skip)
{
	if (result && !skip)
		strcpy(result, g_Va00E0302C ? "1" : "0");
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
