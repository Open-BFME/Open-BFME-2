// cl: /DNDEBUG /MD /EHs-c-
// platformsdk
// Late-bound ImmDisableTextFrameService(-1) call recovered from retail.

#include <windows.h>

typedef BOOL(__stdcall *ImmDisableTextFrameServiceProc)(DWORD threadId);

// ?Rva0005D6D0DisableImmTextFrameService@@YAXXZ
void Rva0005D6D0DisableImmTextFrameService(void)
{
	HMODULE module = LoadLibraryA("IMM32.dll");
	if (module != 0) {
		ImmDisableTextFrameServiceProc disable =
			(ImmDisableTextFrameServiceProc)GetProcAddress(module,
				"ImmDisableTextFrameService");
		if (disable != 0) {
			disable((DWORD)-1);
		}
		FreeLibrary(module);
	}
}
