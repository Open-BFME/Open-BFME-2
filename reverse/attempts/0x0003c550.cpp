// _d_0088d240
// partial score=0.85 date=2026-09-22
// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// Crash minidump writer, retail 0x0003C550 (465 bytes); the exception
// filter (0x0003DCD0) calls it with the exception and the Debug flag at
// +0x9F56. BFME 1 has the body (b1 0x0088D240, 437 bytes) only as a
// generated dump. It resolves MiniDumpWriteDump from the dbghelp.dll that
// InitDbghelp loaded (debug_stack.cpp's g_dbghelp, 0x00DE08AC), names the
// file DUMP_<version>_<date>-<time>_<internal version>_<pid>_<tid>.dmp,
// enables SeDebugPrivilege on the thread (or process) token for the write,
// and writes a full-memory dump when asked, a data-segment dump otherwise.
// The name is descriptive; no symbol survives for it.

typedef void *HANDLE;
typedef unsigned long DWORD;

struct SYSTEMTIME
{
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDayOfWeek;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
};

struct LUID
{
	DWORD LowPart;
	long HighPart;
};

struct TOKEN_PRIVILEGES
{
	DWORD PrivilegeCount;
	LUID Luid;
	DWORD Attributes;
};

struct MINIDUMP_EXCEPTION_INFORMATION
{
	DWORD ThreadId;
	struct _EXCEPTION_POINTERS *ExceptionPointers;
	int ClientPointers;
};

extern "C"
{
	__declspec(dllimport) void *__stdcall GetProcAddress(HANDLE module, const char *procName);
	__declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME *time);
	__declspec(dllimport) DWORD __stdcall GetCurrentThreadId(void);
	__declspec(dllimport) DWORD __stdcall GetCurrentProcessId(void);
	__declspec(dllimport) HANDLE __stdcall GetCurrentThread(void);
	__declspec(dllimport) HANDLE __stdcall GetCurrentProcess(void);
	__declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *fmt, ...);
	__declspec(dllimport) HANDLE __stdcall CreateFileA(const char *fileName, DWORD access,
		DWORD shareMode, void *security, DWORD disposition, DWORD flags, HANDLE templateFile);
	__declspec(dllimport) DWORD __stdcall GetLastError(void);
	__declspec(dllimport) int __stdcall CloseHandle(HANDLE handle);
	__declspec(dllimport) int __stdcall OpenThreadToken(HANDLE thread, DWORD access, int openAsSelf,
		HANDLE *token);
	__declspec(dllimport) int __stdcall OpenProcessToken(HANDLE process, DWORD access, HANDLE *token);
	__declspec(dllimport) int __stdcall LookupPrivilegeValueA(const char *systemName, const char *name,
		LUID *luid);
	__declspec(dllimport) int __stdcall AdjustTokenPrivileges(HANDLE token, int disableAll,
		TOKEN_PRIVILEGES *newState, DWORD bufferLength, TOKEN_PRIVILEGES *previousState,
		DWORD *returnLength);
}

typedef int(__stdcall *MiniDumpWriteDumpProc)(HANDLE process, DWORD processId, HANDLE file,
	int dumpType, MINIDUMP_EXCEPTION_INFORMATION *exceptionParam, void *userStreamParam,
	void *callbackParam);

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
	virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27();
	virtual void pad28(); virtual void pad29(); virtual void pad30(); virtual void pad31();
	virtual void pad32(); virtual void pad33(); virtual void pad34(); virtual void pad35();
	virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39();
	virtual const char *GetVersion();
	virtual const char *GetInternalVersion();
};

extern Debug *theDebug;
extern HANDLE g_dbghelp; // dbghelp.dll, loaded by InitDbghelp

// ?DebugWriteMiniDump@@YAXPAU_EXCEPTION_POINTERS@@_N@Z
void DebugWriteMiniDump(struct _EXCEPTION_POINTERS *exptr, bool fullMemory)
{
	if (!g_dbghelp)
		return;
	MiniDumpWriteDumpProc writeDump =
		(MiniDumpWriteDumpProc)GetProcAddress(g_dbghelp, "MiniDumpWriteDump");
	if (!writeDump)
		return;

	SYSTEMTIME time;
	GetLocalTime(&time);
	const char *internalVersion = theDebug->GetInternalVersion();
	const char *version = theDebug->GetVersion();
	char fileName[262];
	_snprintf(fileName, sizeof(fileName), "DUMP_%s_%04d%02d%02d-%02d%02d%02d_%s_%ld_%ld.dmp",
		version, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond,
		internalVersion, GetCurrentProcessId(), GetCurrentThreadId());

	HANDLE file = CreateFileA(fileName, 0xC0000000, 3, 0, 2, 0, 0);
	if (file == (HANDLE)-1)
		return;

	HANDLE token = 0;
	if (!OpenThreadToken(GetCurrentThread(), 0x28, 1, &token))
	{
		if (GetLastError() != 0x3F0) // ERROR_NO_TOKEN
			return;
		if (!OpenProcessToken(GetCurrentProcess(), 0x28, &token))
			return;
	}

	MINIDUMP_EXCEPTION_INFORMATION info = { 0 };
	info.ThreadId = GetCurrentThreadId();
	info.ExceptionPointers = exptr;
	info.ClientPointers = 1;

	// the dump wants the debug privilege
	TOKEN_PRIVILEGES privileges;
	privileges.PrivilegeCount = 1;
	privileges.Attributes = 2; // SE_PRIVILEGE_ENABLED
	TOKEN_PRIVILEGES previous;
	DWORD previousSize;
	int adjusted = 1;
	if (!LookupPrivilegeValueA(0, "SeDebugPrivilege", &privileges.Luid))
		adjusted = 0;
	else
	{
		previousSize = sizeof(previous);
		if (!AdjustTokenPrivileges(token, 0, &privileges, sizeof(previous), &previous, &previousSize)
			|| GetLastError() == 0x514) // ERROR_NOT_ALL_ASSIGNED
			adjusted = 0;
	}

	writeDump(GetCurrentProcess(), GetCurrentProcessId(), file, fullMemory ? 2 : 1, &info, 0, 0);

	if (adjusted)
		AdjustTokenPrivileges(token, 0, &previous, 0, 0, 0);
	CloseHandle(token);
	CloseHandle(file);
}
