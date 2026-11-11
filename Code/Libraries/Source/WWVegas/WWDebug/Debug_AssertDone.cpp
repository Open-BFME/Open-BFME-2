// platformsdk
// Preserve the old opaque breakpoint block's memory ordering: the debugger
// must observe the dialog-answered store before INT3 and subsequent accesses after it.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// cl: /DNDEBUG /MD /EHsc /Oy-
//
// Debug::AssertDone, retail 0x0003A8A0 (948 bytes incl. its switch table,
// ret 4). Debug vtable (RVA 0x7BE810) slot 0x44.
//
// Identity (target evidence): the body only runs while curType is
// Assert (0), uses the "Assertion failed" dialog title (0xBBEBE8) and the
// "Assert hit too often - turning check off.\n" literal (0xBBEBBC). BFME 1
// carries the same bytes (b1 0x0088B530, one literal apart) as a lift it
// misnamed AssertBegin; Zero Hour's debug_debug.cpp AssertDone is the
// semantic base. Its CrashDone twin sits at 0x0003AED0 (slot 0x4C).
//
// BFME2 changes against Zero Hour (all read from the retail bytes):
// - One dword argument, compared against 0 and 1 (not a bool): 1 appends
//   the "severity" note, forces the stack trace and takes the fatal path.
// - The stack walk runs unless the +0x9E79 flag is set, and passes
//   (die == 1) as StackWalk's third argument.
// - The windowed path asks the singleton's IsWindowed (slot 0xAC), skips
//   entries whose status is 3, and shows the custom assert/crash dialog at
//   0x0003D880 while the +0x9F64 flag is raised.
// - The fatal path flushes every I/O target (0x000392C0), minimises the
//   thread's window, shows "Game crash" and calls _exit(1).
// - The exit path releases the Debug critical section and decrements
//   disableAssertsEtc with InterlockedDecrement.

#include <windows.h>
#include <string.h>
#include <stdlib.h>

struct DebugCriticalSection
{
	unsigned char m_data[0x18];
};

extern DebugCriticalSection g_bfmeCsDWC;
// Raised whenever the assert dialog was answered with anything but
// retry/yes; its reader is not recovered.
extern bool g_debugAssertDialogAnswered;
// g_debugAssertDialogAnswered: matched references place it at VA 0xde089d (zero-filled .bss).
bool g_debugAssertDialogAnswered;

void *DebugAllocMemory(unsigned int numBytes);
int __stdcall EnumThreadWndProc(void *window, long param);
extern "C" int Rva0088E1A0ShowAssertCrashDialog(const char *windowText, const char *messageText);

struct DebugIOInterface
{
	enum StringType { Assert, Check, Log, Crash, Exception, CmdReply, Other, MAX };
};

class DebugStackwalk
{
public:
	// A class, as debug_stack.cpp defines it: the key is part of the mangled
	// StackWalk and operator<< names this unit calls.
	class Signature
	{
	public:
		unsigned int m_numAddr;
		unsigned int m_addr[256];

		Signature() : m_numAddr(0) {}
	};

	static int StackWalk(Signature &sig, struct _CONTEXT *context, bool fullWalk);
};

// The same body as the BFME1 Rva0088A1F0 donor: pushes the current output to
// every I/O target and flushes them.
#include "Rva0088A1F0Owner.h"

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
	// overloads in reverse declaration order), AssertDone at 0x44 and
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
	virtual bool AssertDone(int die);
	virtual void pad18();
	virtual void pad19();
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
	unsigned char m_pad9E7A[0xDE];
	bool m_noAssertDialog;               // +0x9F58
	unsigned char m_pad9F59[0xB];
	bool m_inAssertDialog;               // +0x9F64
};

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

Debug &operator<<(Debug &debug, const DebugStackwalk::Signature &sig);

// ?AssertDone@Debug@@UAE_NH@Z
bool Debug::AssertDone(int die)
{
	if (curType == DebugIOInterface::Assert)
	{
		if (curFrameEntry->hits > 1)
			(*this) << " (hit #" << curFrameEntry->hits << ")";

		if (!ioBuffer[curType].lastWasCR)
			operator<<("\n");

		const char *addInfo = die == 1 ?
			"\nBecause of the severity of this error the game will now exit." : "";
		char *help = (char *)DebugAllocMemory(ioBuffer[curType].used + strlen(addInfo) + 1);
		strcpy(help, ioBuffer[curType].buffer + 84);
		strcat(help, addInfo);

		if (!m_noStackWalk || die == 1)
		{
			DebugStackwalk::Signature sig;
			if (DebugStackwalk::StackWalk(sig, 0, die == 1))
				(*this) << sig;
		}

		operator<<("\n\n");
		Debug::FlushOutput(true);

		if (die == 0)
		{
			bool windowed = false;
			if (theDebug->IsWindowed() && curFrameEntry->status != SkipAlways)
				windowed = true;

			if (!m_noAssertDialog && windowed)
			{
				FrameHashEntry *entry = curFrameEntry;
				m_inAssertDialog = true;
				int result = Rva0088E1A0ShowAssertCrashDialog("Assertion failed", help);
				m_inAssertDialog = false;
				curFrameEntry = entry;

				switch (result)
				{
					case 2:
						g_debugAssertDialogAnswered = true;
						_ReadWriteBarrier(); __debugbreak(); _ReadWriteBarrier();
						break;
					case 3:
						curFrameEntry = 0;
						LeaveCriticalSection((LPCRITICAL_SECTION)&g_bfmeCsDWC);
						exit(1);
					case 5:
						{
							char pattern[200];
							wsprintfA(pattern, "%s(%i)", curFrameEntry->fileOrGroup,
								curFrameEntry->line);
							AddPatternEntry(1, false, pattern);
							curFrameEntry->status = Skip;
						}
						g_debugAssertDialogAnswered = true;
						break;
					case 7:
						{
							char pattern[200];
							wsprintfA(pattern, "%s(%i)", curFrameEntry->fileOrGroup,
								curFrameEntry->line);
							AddPatternEntry(1, false, pattern);
							curFrameEntry->status = SkipAlways;
						}
						g_debugAssertDialogAnswered = true;
						break;
					case 1:
						g_debugAssertDialogAnswered = true;
						break;
				}
			}
			else if (curFrameEntry->hits == 20)
			{
				Debug::StartOutput(DebugIOInterface::Other, "");
				(*this) << "Assert hit too often - turning check off.\n";
				Debug::FlushOutput(true);

				char pattern[200];
				wsprintfA(pattern, "%s(%i)", curFrameEntry->fileOrGroup, curFrameEntry->line);
				AddPatternEntry(1, false, pattern);
				curFrameEntry->status = Skip;
			}
		}
		else
		{
			((Rva0088A1F0Owner *)this)->broadcast();

			HWND window = 0;
			EnumThreadWindows(GetCurrentThreadId(), (WNDENUMPROC)EnumThreadWndProc, (long)&window);
			if (window)
				ShowWindow(window, 6);
			MessageBoxA(0, help, "Game crash", 0x11010);

			curFrameEntry = 0;
			LeaveCriticalSection((LPCRITICAL_SECTION)&g_bfmeCsDWC);
			((Rva0088A1F0Owner *)this)->broadcast();
			_exit(1);
		}
	}

	curFrameEntry = 0;
	LeaveCriticalSection((LPCRITICAL_SECTION)&g_bfmeCsDWC);
	InterlockedDecrement(&disableAssertsEtc);
	return false;
}
