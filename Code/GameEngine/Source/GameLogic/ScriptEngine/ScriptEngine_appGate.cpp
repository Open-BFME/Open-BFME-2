// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ScriptEngine app-continuation gate at retail 0x00203B47 (106B).
// Decoded from retail bytes (all verified):
// - TheGameLogic->isGamePaused() row gate (matched 7B leaf at 0x23CD97).
// - GlobalData byte flag at [0xDFE758]+0xBBD.
// - App module handle at [0xDFE158]; RunAppFast/CanAppContinue via
//   kernel32!GetProcAddress import (IAT 0xBBA1F8, dllimport auto).
// - Latch at [0xDFE168]: set on proc success, cleared on next failure.
// Human-readable names; opaque host (caller sets ecx, body ignores this).

extern class GlobalData *TheWritableGlobalData;

typedef int HMODULE;

// g_00DFE158: VA 0x00dfe158 (.data/bss); retail zero-filled.
HMODULE g_00DFE158;
// g_00DFE168: VA 0x00dfe168 (.data/bss); retail zero-filled.
unsigned char g_00DFE168;

extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *name);

class GameLogic
{
public:
	unsigned char isGamePaused();
};
extern GameLogic *TheGameLogic;

#define TheGlobalData (*(unsigned char **)&TheWritableGlobalData)
#define TheAppModule g_00DFE158
#define AppFastLatch g_00DFE168

class Rva00203B47Host
{
public:
	bool rva00203B47();
};

bool Rva00203B47Host::rva00203B47()
{
	if (!TheGameLogic->isGamePaused())
	{
		if (TheGlobalData[0xBBD] != 0)
			return true;
	}

	if (!TheAppModule)
		return false;

	GetProcAddress(TheAppModule, "CanAppContinue");
	void *runFast = GetProcAddress(TheAppModule, "RunAppFast");

	typedef bool (__stdcall *AppProc)();
	if (!runFast || !((AppProc)runFast)())
		goto latchFail;

	AppFastLatch = 1;
	return true;

latchFail:
	if (AppFastLatch)
		AppFastLatch = 0;
	return false;
}

extern HMODULE st_DebugDLL;

void Rva00203BB1ForceAppContinue()
{
	if (!st_DebugDLL)
		return;

	void *proc = GetProcAddress(st_DebugDLL, "ForceAppContinue");
	if (proc)
		((void (__cdecl *)())proc)();
}
