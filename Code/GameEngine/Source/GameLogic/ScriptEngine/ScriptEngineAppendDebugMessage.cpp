// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?AppendDebugMessage@ScriptEngine@@QAEXABVAsciiString@@_N@Z @0x00205263 171B
// Retail ScriptEngine debug-window append: disabled/DLL guards, AppendMessage
// proc via GetProcAddress, frame from TheGameLogic+0x40 or TheRva00DFEF10+0xFC
// gated by GameLogic::rva001DCD1C, "%d " format plus concat, proc(msg.str()).
// Donor: BFME1 ScriptEngineAppendDebugMessage.cpp (ignores forcePause, always
// AppendMessage) plus BFME2 ScriptEngine_setFrame.cpp frame-gate pattern.
// Evidence: pinned name, callers at 0x00205CC3 0x00205F67 0x00206168,
// rowed callees format 0x38150 concat 0x6987 releaseBuffer 0x36410 gate 0x1DCD1C.

class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern bool BFME2ScriptDebugLiteMode;

typedef bool Bool;
typedef int Int;
typedef int HMODULE;
// The existing ScriptEngine_appGate.cpp definition and this retail DLL load
// both identify the same zero-filled global at VA 0x00DFE158.
extern HMODULE g_00DFE158;
typedef int (__stdcall *FARPROC)();

extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(
	HMODULE module, const char *procName);

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"

class GameLogic
{
public:
	bool rva001DCD1C();

private:
	char m_pad00[0x40];

public:
	Int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

#define TheRva00DFEF10 (*(void **)&(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))
#define TheScriptDebugWindowDLL g_00DFE158
#define ScriptDebugMessagesDisabled BFME2ScriptDebugLiteMode

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause);
};

void ScriptEngine::AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause)
{
	if (ScriptDebugMessagesDisabled || !TheScriptDebugWindowDLL)
		return;
	FARPROC proc = GetProcAddress(TheScriptDebugWindowDLL, "AppendMessage");
	if (!proc)
		return;
	AsciiString msg;
	GameLogic *logic = TheGameLogic;
	if (!logic->rva001DCD1C())
		msg.format("%d ", logic->m_frame);
	else
		msg.format("%d ", *(Int *)((char *)TheRva00DFEF10 + 0xFC));
	((StringBase<char> *)&msg)->concat(*(const StringBase<char> *)&strToAdd);
	((void (__cdecl *)(const char *))proc)(msg.str());
}
