// cl: /O1 /arch:SSE /G7
// platformsdk
// ?rva002047CF@ScriptEngine@@QAEXXZ at 0x002047CF (55B). Identity: ScriptEngine field offset matches the adjacent named client updater; shared frame getter and debug DLL state.

#include <windows.h>
extern int st_DebugDLL;
extern unsigned char g_00DFE15D;
void Rva002040E7GetFrameNumber();

#include "../../../Include/GameLogic/ScriptEngine.h"

void ScriptEngine::rva002047CF()
{
	if (!m_1A4D9)
		return;
	Rva002040E7GetFrameNumber();
	if (st_DebugDLL)
	{
		typedef unsigned char (__stdcall *CanAppContinueProc)();
		CanAppContinueProc proc = (CanAppContinueProc)GetProcAddress(reinterpret_cast<HMODULE>(st_DebugDLL), "CanAppContinue");
		if (proc)
			g_00DFE15D = proc();
		return;
	}
	g_00DFE15D = 1;
}
