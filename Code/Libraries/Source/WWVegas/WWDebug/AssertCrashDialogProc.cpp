// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Oy-
//
// Dialog procedure of the assert/crash dialog, retail 0x0003D6A0 (203
// bytes); the dialog driver at 0x0003D880 passes it to
// DialogBoxIndirectParamA.
//
// Ported from Open-BFME-1 Rva0088E000DialogProc.cpp (b1 0x0088E000). BFME2
// changes, read from the retail bytes:
// - WM_INITDIALOG hides control 4 (not 2) unless a debugger is attached,
//   asked through DebugIsDebuggerAttached (0x0003E3E0).
// - WM_COMMAND ends the dialog with the id for 1/3/5/7, maps control 2 to
//   1 and control 4 to 2, and control 9 copies the report to the clipboard
//   (DebugCopyDialogReport, 0x0003D3A0) without closing.

typedef void *HWND;

extern "C"
{
	__declspec(dllimport) int __stdcall EndDialog(HWND dialog, int result);
	__declspec(dllimport) HWND __stdcall GetDlgItem(HWND dialog, int id);
	__declspec(dllimport) int __stdcall ShowWindow(HWND window, int command);
	__declspec(dllimport) int __stdcall SetWindowTextA(HWND window, const char *text);
	__declspec(dllimport) long __stdcall SendDlgItemMessageA(HWND dialog, int id,
		unsigned int message, unsigned int wParam, long lParam);

	// Title and report text, set by the dialog driver before it opens the box.
	extern const char *g_rva0088E000MessageText;
	extern const char *g_rva0088E000WindowText;
}

bool DebugIsDebuggerAttached();
void DebugCopyDialogReport();

// ?AssertCrashDialogProc@@YGHPAXIIJ@Z
int __stdcall AssertCrashDialogProc(HWND dialog, unsigned int message, unsigned int wParam, long)
{
	switch (message)
	{
	case 0x110: // WM_INITDIALOG
		if (!DebugIsDebuggerAttached())
			ShowWindow(GetDlgItem(dialog, 4), 0);
		SetWindowTextA(dialog, g_rva0088E000WindowText);
		SendDlgItemMessageA(dialog, 100, 0xC, 0, (long)g_rva0088E000MessageText);
		return 1;

	case 0x111: // WM_COMMAND
		{
			unsigned short id = (unsigned short)wParam;
			if (id == 1 || id == 3 || id == 5 || id == 7)
				EndDialog(dialog, id);
			else if (id == 2)
				EndDialog(dialog, 1);
			else if (id == 4)
				EndDialog(dialog, 2);
			else if (id == 9)
				DebugCopyDialogReport();
		}
	}

	return 0;
}
