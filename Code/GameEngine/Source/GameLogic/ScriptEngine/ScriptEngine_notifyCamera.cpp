// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00203B2B@Rva00203B2BHost@@QAEXXZ at retail 0x00203B2B (28B).
// Opaque-host App-module tail-jump sibling of Rva00203B47Host::rva00203B47:
// NotifyCameraChange via kernel32!GetProcAddress (IAT 0xBBA1F8).
// Target evidence: mov eax,[0xDFE158]; test; je ret; push label;
// push eax; call [0xBBA1F8]; test; je ret; jmp eax. Caller at 0x0008C201
// passes TheScriptEngine in ecx (ignored). Label string at 0x007E3998.

typedef int HMODULE;

extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *name);

extern HMODULE g_00DFE158;
#define TheAppModule g_00DFE158

class Rva00203B2BHost
{
public:
	void rva00203B2B();
};

void Rva00203B2BHost::rva00203B2B()
{
	if (!TheAppModule)
		return;
	void *proc = GetProcAddress(TheAppModule, "NotifyCameraChange");
	if (!proc)
		return;
	((void (__stdcall *)())proc)();
}
