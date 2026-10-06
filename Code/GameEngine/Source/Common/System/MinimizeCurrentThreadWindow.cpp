// cl: /DNDEBUG /MD /Ob2

typedef void *HWND;
typedef long LPARAM;
typedef int BOOL;
typedef unsigned long DWORD;

extern "C" __declspec(dllimport) DWORD __stdcall GetCurrentThreadId(void);
extern "C" __declspec(dllimport) BOOL __stdcall EnumThreadWindows(
	DWORD threadId,
	BOOL (__stdcall *callback)(HWND, LPARAM),
	LPARAM context);
extern "C" __declspec(dllimport) BOOL __stdcall ShowWindow(HWND window, int command);

// Retail 0x0056DD12, 15 bytes. The matched EnumThreadWindows caller
// supplies &window as LPARAM; the callback stores HWND there and returns
// FALSE to stop enumeration. Demo reloc mapping supplies the missing start;
// retail's ret 8 and argument loads establish the callback ABI.
BOOL __stdcall bfmeCaptureCurrentThreadWindow(HWND window, LPARAM context)
{
	*reinterpret_cast<HWND *>(context) = window;
	return 0;
}

void bfmeMinimizeCurrentThreadWindow(void)
{
	HWND window = 0;
	EnumThreadWindows(
		GetCurrentThreadId(),
		bfmeCaptureCurrentThreadWindow,
		reinterpret_cast<LPARAM>(&window));

	if (window != 0) {
		ShowWindow(window, 6);
	}
}
