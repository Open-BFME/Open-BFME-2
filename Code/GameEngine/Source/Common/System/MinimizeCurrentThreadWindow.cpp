// cl: /DNDEBUG /MD /Ob2
// platformsdk

// The callback's symbol carries the SDK's non-strict handle type
// (?bfmeCaptureCurrentThreadWindow@@YGHPAXJ@Z: HWND is void *), so
// WNDENUMPROC is the untyped FARPROC and the callback is cast to it.
#define NO_STRICT
#include <windows.h>

// Retail 0x0056DD12, 15 bytes. The matched EnumThreadWindows caller
// supplies &window as LPARAM; the callback stores HWND there and returns
// FALSE to stop enumeration. Demo reloc mapping supplies the missing start;
// retail's ret 8 and argument loads establish the callback ABI.
BOOL __stdcall bfmeCaptureCurrentThreadWindow(HWND window, LPARAM context)
{
	*reinterpret_cast<HWND *>(context) = window;
	return FALSE;
}

void bfmeMinimizeCurrentThreadWindow(void)
{
	HWND window = 0;
	EnumThreadWindows(
		GetCurrentThreadId(),
		(WNDENUMPROC)bfmeCaptureCurrentThreadWindow,
		reinterpret_cast<LPARAM>(&window));

	if (window != 0) {
		ShowWindow(window, SW_MINIMIZE);
	}
}
