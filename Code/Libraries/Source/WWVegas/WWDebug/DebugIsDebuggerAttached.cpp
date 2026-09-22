// cl: /DNDEBUG /MD /EHs-c-
//
// Late-bound debugger probe, retail 0x0003E3E0 (108 bytes), between
// DebugFreeMemory and DebugAllocMemory in the debug library. The Debug
// constructor (0x00038440) calls it and turns the stack walk off
// (+0x9E79) when it reports a debugger.
//
// Ported from Open-BFME-1 Rva0088EAF0IsDebuggerPresent.cpp (b1 0x0088EAF0):
// kernel32 is loaded by name and IsDebuggerPresent resolved at run time.
// BFME2 additionally asks CheckRemoteDebuggerPresent for the current
// process and ORs both answers.

#pragma optimize("y", off)

typedef void *HMODULE;
typedef int(__stdcall *IsDebuggerPresentProc)(void);
typedef int(__stdcall *CheckRemoteDebuggerPresentProc)(void *process, int *present);

extern "C"
{
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *procName);
	__declspec(dllimport) void *__stdcall GetCurrentProcess(void);
}

// ?DebugIsDebuggerAttached@@YA_NXZ
bool DebugIsDebuggerAttached()
{
	bool attached = false;
	HMODULE kernel = LoadLibraryA("kernel32");
	if (kernel)
	{
		IsDebuggerPresentProc isDebuggerPresent =
			(IsDebuggerPresentProc)GetProcAddress(kernel, "IsDebuggerPresent");
		if (isDebuggerPresent)
			attached = isDebuggerPresent() != 0;

		CheckRemoteDebuggerPresentProc checkRemote = (CheckRemoteDebuggerPresentProc)
			GetProcAddress(kernel, "CheckRemoteDebuggerPresent");
		int remote = 0;
		if (checkRemote && checkRemote(GetCurrentProcess(), &remote))
			attached |= remote != 0;
	}
	return attached;
}
