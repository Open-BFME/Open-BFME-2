// flags: region default (reverse/retail_inventory/flag_regions.csv)
// platformsdk
// ScriptEngine app-continuation gate at retail 0x00203B47 (106B).
// Decoded from retail bytes (all verified):
// - TheGameLogic->isGamePaused() row gate (matched 7B leaf at 0x23CD97).
// - GlobalData byte flag at [0xDFE758]+0xBBD.
// - App module handle at [0xDFE158]; RunAppFast/CanAppContinue via
//   kernel32!GetProcAddress import (IAT 0xBBA1F8, dllimport auto).
// - Latch at [0xDFE168]: set on proc success, cleared on next failure.
// Human-readable names; opaque host (caller sets ecx, body ignores this).

extern class GlobalData *TheWritableGlobalData;

#include <windows.h>

// g_00DFE158: VA 0x00dfe158 (.data/bss); retail zero-filled.
extern int st_DebugDLL;
// g_00DFE168: VA 0x00dfe168 (.data/bss); retail zero-filled.
unsigned char g_00DFE168;

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#define TheGlobalData (*(unsigned char **)&TheWritableGlobalData)
#define TheAppModule st_DebugDLL
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

	GetProcAddress(reinterpret_cast<HMODULE>(TheAppModule), "CanAppContinue");
	FARPROC runFast = GetProcAddress(reinterpret_cast<HMODULE>(TheAppModule), "RunAppFast");

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

extern int st_DebugDLL;
// ?st_DebugDLL@@3HA (data_ledger RVA 0x9FE158, null .data, unowned): debug
// DLL handle, LoadLibrary'd on demand; defined here, nothing else defines it.
int st_DebugDLL = 0;

void Rva00203BB1ForceAppContinue()
{
	if (!st_DebugDLL)
		return;

	FARPROC proc = GetProcAddress(reinterpret_cast<HMODULE>(st_DebugDLL), "ForceAppContinue");
	if (proc)
		((void (__cdecl *)())proc)();
}
