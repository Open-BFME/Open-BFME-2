// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ScriptEngine client-debug-frame updater at retail 0x00204806 (55B).
// BFME1 ScriptEngineDebugFrame.cpp _bfme_updateClientDebugFrame port: the
// middle (debug-window inputs + SetFrameNumber proc call) is factored into
// the 0x00204094 frame-bundle row in BFME2, called unconditionally here.
// Decoded from retail bytes (all verified):
// - Early-out when the logic-frame-mode flag at +0x1A4D9 is set (client
//   updater polarity, cf BFME1 `if (m_useLogicDebugFrame) return;`).
// - Frame bundle via the rva00204094 row, then the module global re-read
//   (BFME1 re-reads TheScriptDebugWindowDLL after its inputs call too).
// - Null module stores latch true (BFME1 trailing assignment); null proc
//   returns leaving the latch alone (BFME1 inner return).
// Human-readable names; TU-local ScriptEngine view (flag offset only).

typedef int HMODULE;
extern HMODULE g_00DFE158;

// g_00DFE15C: VA 0x00dfe15c (.data); retail initial bytes 00 00 00 00.
unsigned char g_00DFE15C;

extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *name);

void rva00204094();

#define TheScriptDebugWindowDLL g_00DFE158
#define ClientCanAppContinue g_00DFE15C

class ScriptEngine
{
public:
	void _bfme_updateClientDebugFrame();
private:
	unsigned char m_padToDebugFlag[0x1A4D9];
	bool m_useLogicDebugFrame;
};

void ScriptEngine::_bfme_updateClientDebugFrame()
{
	if (m_useLogicDebugFrame)
		return;

	rva00204094();

	HMODULE module = TheScriptDebugWindowDLL;
	if (module)
	{
		typedef unsigned char (__stdcall *CanAppContinueProc)();
		CanAppContinueProc proc = (CanAppContinueProc)GetProcAddress(module, "CanAppContinue");
		if (!proc)
			return;
		ClientCanAppContinue = proc();
		return;
	}
	ClientCanAppContinue = true;
}
