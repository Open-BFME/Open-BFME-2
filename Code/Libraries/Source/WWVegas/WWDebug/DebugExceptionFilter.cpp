// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// The exception half of Zero Hour's debug_except.cpp as BFME2 ships it:
// ExceptionDlgProc (retail 0x0003CFB0, 957 bytes) and
// DebugExceptionhandler::ExceptionFilter (0x0003DCD0, 1255 bytes including
// the int3 after the final ExitProcess). They share the dialog state as file
// statics, as in Zero Hour; the filter's retail scheduling (the exPtrs store
// sinking past the DialogBoxIndirectParamA pushes) only reproduces when the
// compiler knows those globals cannot alias.
//
// ExceptionDlgProc, BFME2 changes read from the retail bytes:
// - WM_COMMAND closes the dialog for controls 1 and 4 (with that id) and
//   copies the prepared report text to the clipboard for control 9.
// - WM_INITDIALOG hides control 4 unless kernel32's IsDebuggerPresent,
//   looked up at run time, reports a debugger. Ghidra splits the body at
//   this block (0x0003D004); it is one function.
// - The register listing drops '\r' characters before splitting lines.
//
// ExceptionFilter, installed by the Debug constructor and reached from
// LocalSETranslator and the RaiseException hook, BFME2 changes:
// - The stack walk runs first (full walk), and the registered crash
//   attachments are packed into an _alloca'd "____" / id / data / "----"
//   blob before the minidump writer (0x0003C550) runs.
// - crashmailer.exe is started with the process id and the game's path.
// - The log goes through InterlockedIncrement(disableAssertsEtc); the
//   exception location is logged inline; the FPU state is cleared and
//   masked before LogFPURegisters; the text of the exception log is kept
//   for the dialog's copy button.
// - All I/O targets are flushed, the game window minimised, and Windows
//   Error Reporting (faultrep.dll ReportFault) gets the exception first; the
//   dialog only follows for results 3, 4 and 5, and never for a crash
//   raised by CrashDone (code 0x04560123). Answering the dialog with the
//   debugger button breaks into it.
// - The process always ends with ExitProcess(666).
// - Two local buffers are named exePath and buf because MSVC orders stack
//   slots by name; these names reproduce retail's frame.

#include <string.h>
#include <malloc.h>

typedef void *HWND;
typedef void *HMODULE;
typedef unsigned long DWORD;

struct _CONTEXT
{
	unsigned char m_head[0xB8];
	unsigned long Eip;
};

struct _EXCEPTION_RECORD
{
	DWORD ExceptionCode;
};

struct _EXCEPTION_POINTERS
{
	_EXCEPTION_RECORD *ExceptionRecord;
	_CONTEXT *ContextRecord;
};

struct STARTUPINFOA
{
	DWORD cb;
	unsigned char m_rest[0x40];
};

struct PROCESS_INFORMATION
{
	void *hProcess;
	void *hThread;
	DWORD dwProcessId;
	DWORD dwThreadId;
};

extern "C"
{
	__declspec(dllimport) int __stdcall MessageBoxA(HWND owner, const char *text,
		const char *caption, unsigned int type);
	__declspec(dllimport) void __stdcall OutputDebugStringA(const char *text);
	__declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HMODULE module, char *name, DWORD size);
	__declspec(dllimport) DWORD __stdcall GetCurrentProcessId(void);
	__declspec(dllimport) DWORD __stdcall GetCurrentThreadId(void);
	__declspec(dllimport) int __cdecl wsprintfA(char *out, const char *fmt, ...);
	__declspec(dllimport) int __stdcall CreateProcessA(const char *application, char *commandLine,
		void *processAttributes, void *threadAttributes, int inheritHandles, DWORD creationFlags,
		void *environment, const char *currentDirectory, STARTUPINFOA *startupInfo,
		PROCESS_INFORMATION *processInformation);
	__declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value);
	__declspec(dllimport) unsigned int __cdecl _control87(unsigned int newValue, unsigned int mask);
	__declspec(dllimport) void __stdcall InitCommonControls(void);
	__declspec(dllimport) int __stdcall DialogBoxIndirectParamA(void *instance, const void *dialogTemplate,
		HWND parent, int(__stdcall *dialogProc)(HWND, unsigned int, unsigned int, long), long initParam);
	__declspec(dllimport) __declspec(noreturn) void __stdcall ExitProcess(unsigned int exitCode);
	__declspec(dllimport) int __stdcall EnumThreadWindows(DWORD threadId,
		int(__stdcall *callback)(void *, long), long param);
	__declspec(dllimport) int __stdcall ShowWindow(HWND window, int command);
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *procName);
	__declspec(dllimport) int __stdcall FreeLibrary(HMODULE module);
	__declspec(dllimport) int __stdcall EndDialog(HWND dialog, int result);
	__declspec(dllimport) HWND __stdcall GetDlgItem(HWND dialog, int id);
	__declspec(dllimport) long __stdcall SendMessageA(HWND window, unsigned int message,
		unsigned int wParam, long lParam);
	__declspec(dllimport) long __stdcall SendDlgItemMessageA(HWND dialog, int id,
		unsigned int message, unsigned int wParam, long lParam);
	__declspec(dllimport) void *__stdcall CreateFontA(int height, int width, int escapement,
		int orientation, int weight, unsigned long italic, unsigned long underline,
		unsigned long strikeOut, unsigned long charSet, unsigned long outPrecision,
		unsigned long clipPrecision, unsigned long quality, unsigned long pitchAndFamily,
		const char *faceName);
}

struct LVCOLUMNA
{
	unsigned int mask;
	int fmt;
	int cx;
	char *pszText;
	int cchTextMax;
	int iSubItem;
	int iImage;
	int iOrder;
};

struct LVITEMA
{
	unsigned int mask;
	int iItem;
	int iSubItem;
	unsigned int state;
	unsigned int stateMask;
	char *pszText;
	int cchTextMax;
	int iImage;
	long lParam;
	int iIndent;
};

#define ListView_InsertColumn(list, index, column) \
	SendMessageA((list), 0x101B, (unsigned int)(index), (long)(column))
#define ListView_InsertItem(list, item) SendMessageA((list), 0x1007, 0, (long)(item))
#define ListView_SetItem(list, item) SendMessageA((list), 0x1006, 0, (long)(item))

struct DebugIOInterface
{
	enum StringType { Assert, Check, Crash, Exception };
};

class DebugStackwalk
{
public:
	struct Signature
	{
	private:
		unsigned m_numAddr;
		unsigned m_addr[256];

	public:
		unsigned Size() const { return m_numAddr; }
		unsigned GetAddress(int n) const;
		static void GetSymbol(unsigned addr, char *buf, unsigned bufSize);
	};

	static int StackWalk(Signature &sig, _CONTEXT *context, bool fullWalk);
};

class Debug
{
public:
	class RepeatChar
	{
		char m_char;
		int m_count;

	public:
		RepeatChar(char ch, int count) : m_char(ch), m_count(count) {}
	};

	class MemDump
	{
		const unsigned char *m_startPtr;
		unsigned m_numItems;
		unsigned m_bytePerItem;
		bool m_absAddr;
		bool m_withChars;

		MemDump(const void *startPtr, unsigned numItems, unsigned bytePerItem, bool absAddr,
			bool withChars)
			: m_startPtr((const unsigned char *)startPtr), m_numItems(numItems),
			  m_bytePerItem(bytePerItem), m_absAddr(absAddr), m_withChars(withChars)
		{
		}

	public:
		static MemDump Char(const void *startPtr, unsigned numItems)
		{
			return MemDump(startPtr, numItems, 1, true, true);
		}
	};

	// The stream writers form one overload group placed, in reverse
	// declaration order, from MemDump (slot 0x04) to RepeatChar (0x3C).
	virtual ~Debug();
	virtual Debug &operator<<(const RepeatChar &c);
	virtual Debug &operator<<(const char *str);
	virtual Debug &operator<<(int val);
	virtual Debug &operator<<(unsigned val);
	virtual Debug &operator<<(long val);
	virtual Debug &operator<<(unsigned long val);
	virtual Debug &operator<<(bool val);
	virtual Debug &operator<<(float val);
	virtual Debug &operator<<(double val);
	virtual Debug &operator<<(short val);
	virtual Debug &operator<<(unsigned short val);
	virtual Debug &operator<<(__int64 val);
	virtual Debug &operator<<(unsigned __int64 val);
	virtual Debug &operator<<(const void *ptr);
	virtual Debug &operator<<(const MemDump &dump);
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void WriteBuildInfo();         // slot 0x54

	const char *GetOutputBuffer(DebugIOInterface::StringType type) const;

private:
	friend class DebugExceptionhandler;

	struct IOBuffer
	{
		char *buffer;
		unsigned int used;
		unsigned int alloc;
		bool lastWasCR;
	};

	virtual void StartOutput(DebugIOInterface::StringType type, const char *fmt, ...);
	virtual void FlushOutput(bool defaultLog);

	unsigned char m_pad04[0x9C80];
	IOBuffer ioBuffer[7];                // +0x9C84
	int curType;                         // +0x9CF4
	char curSource[256];                 // +0x9CF8
	long disableAssertsEtc;              // +0x9DF8
	unsigned char m_pad9DFC[0x15A];
	bool m_fullMiniDump;                 // +0x9F56
	unsigned char m_pad9F57[0xD];
	bool m_inAssertDialog;               // +0x9F64
};

Debug &operator<<(Debug &dbg, const DebugStackwalk::Signature &sig);

struct Rva0088A1F0Owner
{
	void broadcast();
};

// One entry of the crash attachment list packed into the report blob.
struct CrashAttachment
{
	DWORD id;
	const void *data;
	unsigned size;
};

class DebugExceptionhandler
{
public:
	static const char *GetExceptionType(_EXCEPTION_POINTERS *exptr, char *explanation);
	static long __stdcall ExceptionFilter(_EXCEPTION_POINTERS *pExPtrs);

private:
	static void LogRegisters(Debug &dbg, _EXCEPTION_POINTERS *exptr);
	static void LogFPURegisters(Debug &dbg, _EXCEPTION_POINTERS *exptr);
};

void *DebugReAllocMemory(void *oldPtr, unsigned newSize);
int __stdcall EnumThreadWndProc(void *window, long param);
int __stdcall ExceptionDlgProc(HWND hWnd, unsigned int uMsg, unsigned int wParam, long lParam);
extern "C" void d_0088d240(_EXCEPTION_POINTERS *exptr, bool fullDump);

void DebugCopyToClipboard(const char *text);

typedef int(__stdcall *ReportFaultProc)(_EXCEPTION_POINTERS *exptr, DWORD mode);

extern Debug *theDebug;
// Dialog state shared by the filter and the dialog procedure (file statics
// in Zero Hour debug_except.cpp).
static _EXCEPTION_POINTERS *g_exceptionPointers;          // 0x00DE0DE8
static const char *g_exceptionReportText;                 // 0x00DE0DF4
static char g_exceptionRegisterInfo[1024];                // 0x00DE09E8
static char g_exceptionVersionInfo[256];                  // 0x00DE08E8
static DebugStackwalk::Signature g_exceptionStackSignature; // 0x00DE0E08
extern CrashAttachment *g_crashAttachments;              // 0x00DE0DEC
extern unsigned g_numCrashAttachments;                   // 0x00DE0DF0
extern char g_crashMailerCommand[512];                   // 0x00DE1210
extern unsigned char g_exceptionDialogTemplate[];        // 0x00DB35D0

typedef int(__stdcall *IsDebuggerPresentProc)(void);

// ?ExceptionDlgProc@@YGHPAXIIJ@Z
int __stdcall ExceptionDlgProc(HWND hWnd, unsigned int uMsg, unsigned int wParam, long lParam)
{
	switch (uMsg)
	{
	case 0x110: // WM_INITDIALOG
		break;
	case 0x111: // WM_COMMAND
		if ((unsigned short)wParam == 1 || (unsigned short)wParam == 4)
			EndDialog(hWnd, (unsigned short)wParam);
		else if ((unsigned short)wParam == 9)
			DebugCopyToClipboard(g_exceptionReportText);
	default:
		return 0;
	}

	// the debugger button only makes sense with a debugger attached
	HMODULE kernel = LoadLibraryA("kernel32");
	if (kernel)
	{
		IsDebuggerPresentProc isDebuggerPresent =
			(IsDebuggerPresentProc)GetProcAddress(kernel, "IsDebuggerPresent");
		if (isDebuggerPresent && !isDebuggerPresent())
			ShowWindow(GetDlgItem(hWnd, 4), 0);
	}

	// version
	SendDlgItemMessageA(hWnd, 103, 0xC, 0, (long)g_exceptionVersionInfo);

	// registers
	char *p = g_exceptionRegisterInfo;
	for (char *q = p;; q++)
	{
		if (!*q || *q == '\n')
		{
			bool quit = !*q;
			*q = 0;
			SendDlgItemMessageA(hWnd, 105, 0x180, 0, (long)p);
			if (quit)
				break;
			p = q + 1;
		}
		else if (*q == '\r')
			*q = 0;
	}

	// yes, this generates a GDI leak but we're crashing anyway
	SendDlgItemMessageA(hWnd, 105, 0x30, (unsigned int)CreateFontA(13, 0, 0, 0, 400,
		0, 0, 0, 0, 0, 0, 0, 0x31, 0), 1);

	// exception type
	SendDlgItemMessageA(hWnd, 100, 0xC, 0, (long)
		DebugExceptionhandler::GetExceptionType(g_exceptionPointers, g_exceptionRegisterInfo));
	SendDlgItemMessageA(hWnd, 101, 0xC, 0, (long)g_exceptionRegisterInfo);

	// address
	_CONTEXT &ctx = *g_exceptionPointers->ContextRecord;
	DebugStackwalk::Signature::GetSymbol(ctx.Eip, g_exceptionRegisterInfo,
		sizeof(g_exceptionRegisterInfo));
	SendDlgItemMessageA(hWnd, 102, 0xC, 0, (long)g_exceptionRegisterInfo);

	// stack
	// (this code is a little messy because we're dealing with a raw list control)
	HWND list;
	list = GetDlgItem(hWnd, 104);
	if (!g_exceptionStackSignature.Size())
	{
		LVCOLUMNA c;
		c.mask = 6;
		c.pszText = "";
		c.cx = 690;
		ListView_InsertColumn(list, 0, &c);

		LVITEMA item;
		item.iItem = 0;
		item.iSubItem = 0;
		item.mask = 1;
		item.pszText = "No stack data available - check for dbghelp.dll";

		item.iItem = ListView_InsertItem(list, &item);
	}
	else
	{
		// add columns first
		LVCOLUMNA c;
		c.mask = 6;
		c.pszText = "";
		c.cx = 0; // first column is empty (can't right-align 1st column)
		ListView_InsertColumn(list, 0, &c);

		c.mask = 7;
		c.pszText = "Address";
		c.cx = 60;
		c.fmt = 1;
		ListView_InsertColumn(list, 1, &c);

		c.mask = 6;
		c.pszText = "Module";
		c.cx = 120;
		ListView_InsertColumn(list, 2, &c);

		c.pszText = "Symbol";
		c.cx = 300;
		ListView_InsertColumn(list, 3, &c);

		c.pszText = "File";
		c.cx = 130;
		ListView_InsertColumn(list, 4, &c);

		c.pszText = "Line";
		c.cx = 80;
		ListView_InsertColumn(list, 5, &c);

		// now add stack walk lines
		for (unsigned k = 0; k < g_exceptionStackSignature.Size(); k++)
		{
			DebugStackwalk::Signature::GetSymbol(g_exceptionStackSignature.GetAddress(k),
				g_exceptionRegisterInfo, sizeof(g_exceptionRegisterInfo));

			LVITEMA item;
			item.iItem = k;
			item.iSubItem = 0;
			item.mask = 0;
			item.iItem = ListView_InsertItem(list, &item);
			item.mask = 1;

			item.iSubItem++;
			item.pszText = strtok(g_exceptionRegisterInfo, " ");
			ListView_SetItem(list, &item);

			item.iSubItem++;
			item.pszText = strtok(0, ",");
			ListView_SetItem(list, &item);

			item.iSubItem++;
			item.pszText = strtok(0, ",");
			ListView_SetItem(list, &item);

			item.iSubItem++;
			item.pszText = strtok(0, ":");
			ListView_SetItem(list, &item);

			item.iSubItem++;
			item.pszText = strtok(0, "");
			ListView_SetItem(list, &item);
		}
	}

	return 1;
}

// ?ExceptionFilter@DebugExceptionhandler@@SGJPAU_EXCEPTION_POINTERS@@@Z
long __stdcall DebugExceptionhandler::ExceptionFilter(_EXCEPTION_POINTERS *pExPtrs)
{
	// we should not be calling ourselves!
	static bool inExceptionFilter;
	if (inExceptionFilter)
	{
		MessageBoxA(0, "Exception in exception handler", "Fatal error", 0);
		return 0;
	}
	inExceptionFilter = true;

	if (pExPtrs->ExceptionRecord->ExceptionCode == 0xC00000FD) // EXCEPTION_STACK_OVERFLOW
	{
		// almost everything we are about to do will generate a second
		// stack overflow... double fault... so give at least a little warning
		OutputDebugStringA("EA/DEBUG: EXCEPTION_STACK_OVERFLOW\n");
	}

	Debug &dbg = *theDebug;
	bool raisedByCrash = pExPtrs->ExceptionRecord->ExceptionCode == 0x04560123;
	DebugStackwalk::StackWalk(g_exceptionStackSignature, pExPtrs->ContextRecord, true);

	// pack the crash attachments for the dump
	unsigned size = 8;
	for (unsigned k = 0; k < g_numCrashAttachments; k++)
		size += g_crashAttachments[k].size + 8;
	char *blob = (char *)_alloca(size);
	if (blob)
	{
		*(DWORD *)blob = 0x5F5F5F5F; // "____"
		blob += 4;
		for (unsigned i = 0; i < g_numCrashAttachments; i++)
		{
			*(DWORD *)blob = g_crashAttachments[i].id;
			blob += 4;
			memcpy(blob, g_crashAttachments[i].data, g_crashAttachments[i].size);
			blob += g_crashAttachments[i].size;
			*(DWORD *)blob = 0x2D2D2D2D; // "----"
			blob += 4;
		}
		*(DWORD *)blob = 0x5F5F5F5F;
	}
	d_0088d240(pExPtrs, dbg.m_fullMiniDump);

	// hand the crash to the mailer
	char exePath[512];
	GetModuleFileNameA(0, exePath, sizeof(exePath));
	wsprintfA(g_crashMailerCommand, "crashmailer.exe %i %s", GetCurrentProcessId(), exePath);
	STARTUPINFOA startup;
	memset(&startup, 0, sizeof(startup));
	startup.cb = sizeof(startup);
	PROCESS_INFORMATION process;
	CreateProcessA(0, g_crashMailerCommand, 0, 0, 0, 0x20, 0, 0, &startup, &process);

	// we're logging an exception
	InterlockedIncrement(&dbg.disableAssertsEtc);
	if (dbg.curType != 7)
		dbg.Debug::FlushOutput(true);
	dbg.Debug::StartOutput(DebugIOInterface::Exception, "");

	// start off with the exception type & buf
	dbg << "\n" << Debug::RepeatChar('=', 80) << "\n";
	dbg << GetExceptionType(pExPtrs, g_exceptionRegisterInfo) << ":\n"
		<< g_exceptionRegisterInfo << "\n\n";
	char buf[512];
	DebugStackwalk::Signature::GetSymbol(pExPtrs->ContextRecord->Eip, buf, sizeof(buf));
	dbg << "Exception occured at\n" << buf << ".";
	dbg << "\n\n";

	// build info must be saved off for dialog...
	unsigned curOfs = dbg.ioBuffer[3].used;
	dbg.WriteBuildInfo();
	unsigned len = dbg.ioBuffer[3].used - curOfs;
	if (len >= sizeof(g_exceptionVersionInfo))
		len = sizeof(g_exceptionVersionInfo) - 1;
	memcpy(g_exceptionVersionInfo, dbg.ioBuffer[3].buffer + curOfs, len);
	g_exceptionVersionInfo[len] = 0;
	dbg << "\n\n";

	// save off register info as well...
	curOfs = dbg.ioBuffer[3].used;
	LogRegisters(dbg, pExPtrs);
	dbg << "\n";
	__asm fnclex
	_control87(0x8001F, 0x8001F);
	LogFPURegisters(dbg, pExPtrs);
	dbg << "\n";
	len = dbg.ioBuffer[3].used - curOfs;
	if (len >= sizeof(g_exceptionRegisterInfo))
		len = sizeof(g_exceptionRegisterInfo) - 1;
	memcpy(g_exceptionRegisterInfo, dbg.ioBuffer[3].buffer + curOfs, len);
	g_exceptionRegisterInfo[len] = 0;

	// now finally add stack & EIP dump
	dbg << g_exceptionStackSignature << "\n";
	dbg << "Bytes around EIP:"
		<< Debug::MemDump::Char(((char *)(pExPtrs->ContextRecord->Eip)) - 32, 80);

	// keep the report for the dialog's copy button
	const char *report = dbg.GetOutputBuffer(DebugIOInterface::Exception);
	if (report)
	{
		char *copy = (char *)DebugReAllocMemory((void *)g_exceptionReportText, strlen(report));
		g_exceptionReportText = copy;
		if (copy)
			strcpy(copy, report);
	}

	dbg.Debug::FlushOutput(true);
	((Rva0088A1F0Owner *)&dbg)->broadcast();

	HWND window = 0;
	EnumThreadWindows(GetCurrentThreadId(), EnumThreadWndProc, (long)&window);
	if (window)
		ShowWindow(window, 6);

	// let Windows Error Reporting have a go first
	int reported = 3;
	HMODULE faultrep = LoadLibraryA("faultrep.dll");
	if (faultrep)
	{
		ReportFaultProc reportFault = (ReportFaultProc)GetProcAddress(faultrep, "ReportFault");
		if (reportFault)
			reported = reportFault(pExPtrs, 0);
		FreeLibrary(faultrep);
	}

	if ((reported == 3 || reported == 5 || reported == 4) && !raisedByCrash)
	{
		// Show a dialog box
		InitCommonControls();
		g_exceptionPointers = pExPtrs;
		dbg.m_inAssertDialog = true;
		if (DialogBoxIndirectParamA(0, g_exceptionDialogTemplate, 0, ExceptionDlgProc, 0) == 4)
		{
			dbg.m_inAssertDialog = false;
			__asm int 3
		}
		dbg.m_inAssertDialog = false;
	}

	// Now die
	inExceptionFilter = false;
	ExitProcess(666);
}
