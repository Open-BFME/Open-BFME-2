// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Oy-
//
// Exception dialog procedure, retail 0x0003CFB0 (957 bytes; Ghidra splits
// it at the WM_INITDIALOG block, 0x0003D004). DebugExceptionhandler::
// ExceptionFilter (0x0003DCD0) runs the dialog.
//
// Zero Hour's static ExceptionDlgProc from debug_except.cpp. BFME2 changes,
// all read from the retail bytes:
// - WM_COMMAND closes the dialog for controls 1 and 4 (with that id) and
//   copies the prepared report text to the clipboard for control 9.
// - WM_INITDIALOG hides control 4 unless kernel32's IsDebuggerPresent,
//   looked up at run time, reports a debugger.
// - The register listing drops '\r' characters before splitting lines.
// The dialog state lives in debug_except.cpp's statics in Zero Hour; they
// are declared here under descriptive names at their retail addresses.

#include <string.h>

typedef void *HWND;
typedef void *HMODULE;

extern "C"
{
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *procName);
	__declspec(dllimport) int __stdcall EndDialog(HWND dialog, int result);
	__declspec(dllimport) HWND __stdcall GetDlgItem(HWND dialog, int id);
	__declspec(dllimport) int __stdcall ShowWindow(HWND window, int command);
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

struct _CONTEXT
{
	unsigned char m_head[0xB8];
	unsigned long Eip;
};

struct _EXCEPTION_POINTERS
{
	struct _EXCEPTION_RECORD *ExceptionRecord;
	_CONTEXT *ContextRecord;
};

class DebugStackwalk
{
public:
	class Signature
	{
		unsigned m_numAddr;
		unsigned m_addr[256];

	public:
		unsigned Size() const { return m_numAddr; }
		unsigned GetAddress(int n) const;
		static void GetSymbol(unsigned addr, char *buf, unsigned bufSize);
	};
};

class DebugExceptionhandler
{
public:
	static const char *GetExceptionType(_EXCEPTION_POINTERS *exptr, char *explanation);
};

void DebugCopyToClipboard(const char *text);

// Dialog state prepared by ExceptionFilter before it opens the box.
extern _EXCEPTION_POINTERS *g_exceptionPointers;         // 0x00DE0DE8
extern const char *g_exceptionReportText;                // 0x00DE0DF4
extern char g_exceptionRegisterInfo[1024];               // 0x00DE09E8
extern char g_exceptionVersionInfo[256];                 // 0x00DE08E8
extern DebugStackwalk::Signature g_exceptionStackSignature; // 0x00DE0E08

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
