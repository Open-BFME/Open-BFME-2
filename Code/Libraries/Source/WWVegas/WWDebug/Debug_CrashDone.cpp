// cl: /DNDEBUG /MD /EHsc
//
// Debug::CrashDone, retail 0x0003AED0 (1132 bytes incl. its switch table,
// ret 4). Debug vtable (RVA 0x7BE810) slot 0x4C.
//
// Identity (target evidence): the body only runs while curType is Crash
// (2), titles its dialog "Error hit" (0xBBECD4) and turns noisy entries off
// with "Error hit too often - turning check off.\n" (0xBBECA8). It is the
// twin of Debug::AssertDone at 0x0003A8A0 (Debug_AssertDone.cpp); BFME 1
// has it only as a lift. Zero Hour's CrashDone is the semantic base.
//
// BFME2 changes against Zero Hour (all read from the retail bytes):
// - One dword mode argument: 0 reports (dialog or hit counting), 1 is
//   fatal, 2 only appends the report to errors.txt when the +0x9F57 flag
//   is set. Mode 2 also suppresses the hit counter and the stack walk.
// - Hit-count patterns register with frame type 2 (Crash), the dialog ones
//   with 1, exactly as retail pushes them.
// - The fatal path flushes every I/O target, minimises the thread's
//   window, shows "Game crash", raises exception 0x04560123 and _exit(1)s.
// - The exit path releases the Debug critical section and decrements
//   disableAssertsEtc with InterlockedDecrement.

#pragma optimize("y", off)

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *out, const char *fmt, ...);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void *owner, const char *text,
	const char *caption, unsigned int type);
extern "C" __declspec(dllimport) int __stdcall ShowWindow(void *window, int command);
extern "C" __declspec(dllimport) int __stdcall EnumThreadWindows(unsigned long threadId,
	int(__stdcall *callback)(void *, long), long param);
extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentThreadId(void);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *value);
extern "C" __declspec(dllimport) void *__stdcall CreateFileA(const char *fileName,
	unsigned long access, unsigned long shareMode, void *security,
	unsigned long disposition, unsigned long flags, void *templateFile);
extern "C" __declspec(dllimport) unsigned long __stdcall SetFilePointer(void *file,
	long distance, long *distanceHigh, unsigned long method);
extern "C" __declspec(dllimport) int __stdcall WriteFile(void *file, const void *buffer,
	unsigned long bytes, unsigned long *written, void *overlapped);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" __declspec(dllimport) void __stdcall RaiseException(unsigned long code,
	unsigned long flags, unsigned long argCount, const unsigned long *args);
extern "C" __declspec(dllimport) __declspec(noreturn) void __cdecl exit(int code);
extern "C" __declspec(dllimport) __declspec(noreturn) void __cdecl _exit(int code);
extern "C" size_t strlen(const char *text);
extern "C" char *strcpy(char *dest, const char *src);
extern "C" char *strcat(char *dest, const char *src);

struct DebugCriticalSection
{
	unsigned char m_data[0x18];
};

extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(DebugCriticalSection *lock);

extern DebugCriticalSection g_bfmeCsDWC;
// Raised whenever the assert/crash dialog was answered with anything but
// retry/yes; its reader is not recovered. File-static as in retail's
// debug_debug.cpp: only then may MSVC sink the store past the wsprintfA
// argument loads of `this` members, which is where retail has it.
static bool g_debugAssertDialogAnswered;

void *DebugAllocMemory(unsigned int numBytes);
int __stdcall EnumThreadWndProc(void *window, long param);
extern "C" int Rva0088E1A0ShowAssertCrashDialog(const char *windowText, const char *messageText);

struct DebugIOInterface
{
	// Only Crash (2) and Other (6) are read from this body; the middle names
	// follow the Zero Hour list.
	enum StringType { Assert, Check, Crash, Log, Exception, CmdReply, Other, MAX };
};

class DebugStackwalk
{
public:
	struct Signature
	{
		unsigned int m_numAddr;
		unsigned int m_addr[256];

		Signature() : m_numAddr(0) {}
	};

	static int StackWalk(Signature &sig, struct _CONTEXT *context, bool fullWalk);
};

// The same body as the BFME1 Rva0088A1F0 donor: pushes the current output to
// every I/O target and flushes them.
struct Rva0088A1F0Owner
{
	void broadcast();
};

class Debug
{
public:
	class RepeatChar;

	enum FrameStatus
	{
		Unknown,
		Skip,
		NoSkip,
		SkipAlways
	};

	struct FrameHashEntry
	{
		FrameHashEntry *next;
		unsigned int frameAddr;
		unsigned int frameType;
		const char *fileOrGroup;
		int line;
		int hits;
		FrameStatus status;
	};

	// Placeholders keep operator<< at 0x34/0x38/0x3C (MSVC assigns
	// overloads in reverse declaration order), CrashDone at 0x4C and
	// IsWindowed at 0xAC.
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual Debug &operator<<(const RepeatChar &rep);
	virtual Debug &operator<<(const char *str);
	virtual Debug &operator<<(int val);
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual bool IsWindowed();

private:
	struct IOBuffer
	{
		char *buffer;
		unsigned int used;
		unsigned int alloc;
		bool lastWasCR;
	};

	virtual void StartOutput(DebugIOInterface::StringType type, const char *fmt, ...);
	virtual void FlushOutput(bool defaultLog);
	void AddPatternEntry(unsigned int types, bool isActive, const char *pattern);

	unsigned char m_pad04[0x9C80];
	IOBuffer ioBuffer[7];                // +0x9C84
	int curType;                         // +0x9CF4
	char curSource[256];                 // +0x9CF8
	long disableAssertsEtc;              // +0x9DF8
	FrameHashEntry *curFrameEntry;       // +0x9DFC
	unsigned char m_pad9E00[0x79];
	bool m_noStackWalk;                  // +0x9E79
	unsigned char m_pad9E7A[0xDD];
	bool m_logErrorsToFile;              // +0x9F57
	bool m_noAssertDialog;               // +0x9F58
	unsigned char m_pad9F59[0xB];
	bool m_inAssertDialog;               // +0x9F64
};

Debug *theDebug;

Debug &operator<<(Debug &debug, const DebugStackwalk::Signature &sig);

// ?CrashDone@Debug@@UAE_NH@Z
bool Debug::CrashDone(int mode)
{
	if (curType == DebugIOInterface::Crash)
	{
		if (curFrameEntry->hits > 1 && mode != 2)
			(*this) << " (hit #" << curFrameEntry->hits << ")";

		if (!ioBuffer[curType].lastWasCR)
			operator<<("\n");

		const char *addInfo = mode == 1 ?
			"\nBecause of the severity of this error the game will now exit." : "";

		if ((!m_noStackWalk && mode != 2) || mode == 1)
		{
			DebugStackwalk::Signature sig;
			if (DebugStackwalk::StackWalk(sig, 0, mode == 1))
				(*this) << sig;
		}

		char *help = (char *)DebugAllocMemory(ioBuffer[curType].used + strlen(addInfo) + 1);
		strcpy(help, ioBuffer[curType].buffer + 84);
		strcat(help, addInfo);

		operator<<("\n\n");
		Debug::FlushOutput(true);

		if (mode == 0)
		{
			if (theDebug->IsWindowed() && curFrameEntry->status != SkipAlways &&
				!m_noAssertDialog)
			{
				m_inAssertDialog = true;
				int result = Rva0088E1A0ShowAssertCrashDialog("Error hit", help);
				m_inAssertDialog = false;

				switch (result)
				{
					case 1:
						g_debugAssertDialogAnswered = true;
						break;
					case 2:
						g_debugAssertDialogAnswered = true;
						__asm int 3
						break;
					case 3:
						curFrameEntry = 0;
						LeaveCriticalSection(&g_bfmeCsDWC);
						exit(1);
					case 5:
						{
							g_debugAssertDialogAnswered = true;
							char pattern[200];
							wsprintfA(pattern, "%s(%i)", curFrameEntry->fileOrGroup,
								curFrameEntry->line);
							AddPatternEntry(1, false, pattern);
							curFrameEntry->status = Skip;
						}
						break;
					case 7:
						{
							g_debugAssertDialogAnswered = true;
							char pattern[200];
							wsprintfA(pattern, "%s(%i)", curFrameEntry->fileOrGroup,
								curFrameEntry->line);
							AddPatternEntry(1, false, pattern);
							curFrameEntry->status = SkipAlways;
						}
						break;
				}
			}
			else if (curFrameEntry->hits == 20)
			{
				Debug::StartOutput(DebugIOInterface::Other, "");
				(*this) << "Error hit too often - turning check off.\n";
				Debug::FlushOutput(true);

				char pattern[200];
				wsprintfA(pattern, "%s(%i)", curFrameEntry->fileOrGroup, curFrameEntry->line);
				AddPatternEntry(2, false, pattern);
				curFrameEntry->status = Skip;
			}
		}
		else if (mode == 2)
		{
			if (m_logErrorsToFile)
			{
				void *file = CreateFileA("errors.txt", 0x40000000, 0, 0, 4, 0x80, 0);
				SetFilePointer(file, 0, 0, 2);
				unsigned long written;
				const char *separator =
					"\r\n---------------------------------------------------------------\r\n\r\n";
				WriteFile(file, separator, strlen(separator), &written, 0);
				WriteFile(file, help, strlen(help), &written, 0);
				CloseHandle(file);
			}
		}
		else
		{
			((Rva0088A1F0Owner *)this)->broadcast();

			void *window = 0;
			EnumThreadWindows(GetCurrentThreadId(), EnumThreadWndProc, (long)&window);
			if (window)
				ShowWindow(window, 6);
			MessageBoxA(0, help, "Game crash", 0x11010);

			curFrameEntry = 0;
			LeaveCriticalSection(&g_bfmeCsDWC);
			((Rva0088A1F0Owner *)this)->broadcast();
			RaiseException(0x04560123, 0, 0, 0);
			_exit(1);
		}
	}

	curFrameEntry = 0;
	LeaveCriticalSection(&g_bfmeCsDWC);
	InterlockedDecrement(&disableAssertsEtc);
	return false;
}
