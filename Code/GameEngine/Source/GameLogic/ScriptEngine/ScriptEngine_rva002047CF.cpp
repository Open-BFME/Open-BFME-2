// cl: /O1 /arch:SSE /G7
// ?rva002047CF@ScriptEngine@@QAEXXZ at 0x002047CF (55B). Identity: ScriptEngine field offset matches the adjacent named client updater; shared frame getter and debug DLL state.

typedef int HMODULE;
extern "C" HMODULE st_DebugDLL;
extern unsigned char g_00DFE15D;
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *name);
void Rva002040E7GetFrameNumber();

class ScriptEngine
{
public:
	void rva002047CF();
private:
	unsigned char m_padToDebugFlag[0x1A4D9];
	bool m_useLogicDebugFrame;
};

void ScriptEngine::rva002047CF()
{
	if (!m_useLogicDebugFrame)
		return;
	Rva002040E7GetFrameNumber();
	if (st_DebugDLL)
	{
		typedef unsigned char (__stdcall *CanAppContinueProc)();
		CanAppContinueProc proc = (CanAppContinueProc)GetProcAddress(st_DebugDLL, "CanAppContinue");
		if (proc)
			g_00DFE15D = proc();
		return;
	}
	g_00DFE15D = 1;
}
