// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva00407AF9Run@@YA_NABVAsciiString@@0@Z @0x00407AF9 202B: cdecl bool building command line from two AsciiStrings plus g_00BBD40C via rowed concat then _mbscpy to 256B stack buf then CreateProcessA plus WaitForSingleObject plus CloseHandle. Evidence: memset 0x6291AE STARTUPINFO 0x44 concat 0x6987 0x5629 _mbscpy 0x629176 CreateProcessA IAT WaitForSingleObject CloseHandle releaseBuffer 0x36410 ret; callers 0x409744 0x40976F.
#include "ascii_string.h"
#include <string.h>
struct STARTUPINFOA
{
	unsigned long cb;
	unsigned char m_rest[0x40];
};
struct PROCESS_INFORMATION
{
	void *hProcess;
	void *hThread;
	unsigned long dwProcessId;
	unsigned long dwThreadId;
};
extern "C"
{
	__declspec(dllimport) int __stdcall CreateProcessA(const char *application, char *commandLine,
		void *processAttributes, void *threadAttributes, int inheritHandles, unsigned long creationFlags,
		void *environment, const char *currentDirectory, STARTUPINFOA *startupInfo,
		PROCESS_INFORMATION *processInformation);
	__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long timeout);
	__declspec(dllimport) int __stdcall CloseHandle(void *handle);
	extern char *__cdecl _mbscpy(char *dst, const char *src);
}
extern const char g_00BBD40C[];
bool Rva00407AF9Run(const AsciiString &a, const AsciiString &b)
{
	STARTUPINFOA si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	AsciiString cmd;
	((StringBase<char> *)&cmd)->concat(*(const StringBase<char> *)&a);
	((StringBase<char> *)&cmd)->concat(g_00BBD40C);
	((StringBase<char> *)&cmd)->concat(*(const StringBase<char> *)&b);
	char buf[256];
	_mbscpy(buf, cmd.str());
	PROCESS_INFORMATION pi;
	if (!CreateProcessA(0, buf, 0, 0, 0, 0, 0, 0, &si, &pi))
		return false;
	WaitForSingleObject(pi.hProcess, 0xFFFFFFFF);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return true;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00BBD40C@@3QBDB=??_C@_01CLKCMJKC@?5?$AA@")
