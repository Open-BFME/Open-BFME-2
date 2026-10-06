// cl: /O1
// CopyProtection.cpp: the CopyProtect statics retail links from this TU (tu_map
// approved), folded from six split units with these exact flags. Each unit had
// been split so a caller could not inline it; within this TU the only internal
// call (rva00232D38's tail call to validate) precedes its callee, so it stays a
// call. Bodies are in retail order otherwise.

typedef void *HANDLE;
typedef unsigned long DWORD;
#define WINAPI __stdcall
#define ERROR_ALREADY_EXISTS 183
extern "C" __declspec(dllimport) HANDLE WINAPI CreateMutexA(void *attrs, int owned, const char *name);
extern "C" __declspec(dllimport) DWORD WINAPI GetLastError(void);
extern "C" __declspec(dllimport) int WINAPI CloseHandle(HANDLE obj);
const char *GetRegistryG1(void);
typedef unsigned int UINT;
typedef long LPARAM;
typedef unsigned int WPARAM;
#define WM_USER 0x0400
#define PM_NOREMOVE 0
#define PM_REMOVE 1
#define EVENT_MODIFY_STATE 2
#define FILE_MAP_ALL_ACCESS 0xF001F
struct MSG
{
	HANDLE hwnd;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
	DWORD time;
	long ptX;
	long ptY;
};
extern "C" __declspec(dllimport) int WINAPI PeekMessageA(MSG *msg, HANDLE hwnd, UINT min, UINT max, UINT remove);
extern "C" __declspec(dllimport) DWORD WINAPI timeGetTime(void);
extern "C" __declspec(dllimport) HANDLE WINAPI OpenEventA(DWORD access, int inherit, const char *name);
extern "C" __declspec(dllimport) void WINAPI Sleep(DWORD ms);
extern "C" __declspec(dllimport) int WINAPI SetEvent(HANDLE event);
extern "C" __declspec(dllimport) void *WINAPI MapViewOfFileEx(HANDLE mapping, DWORD access,
	DWORD high, DWORD low, DWORD bytes, void *base);
const char *GetRegistryG3(void);
typedef int BOOL;
extern "C" int __cdecl strcmp(const char *a, const char *b);
const char *GetRegistryG4(void);
extern "C" __declspec(dllimport) BOOL WINAPI UnmapViewOfFile(void *lpBaseAddress);

class CopyProtect
{
public:
	static bool isLauncherRunning(void);
	static bool notifyLauncher(void);
	static void checkForMessage(UINT message, LPARAM lParam);
	static bool validate(void);
	static bool rva00232D38(void);
	static void shutdown(void);

private:
	static void *s_protectedData;
};

// CopyProtect::isLauncherRunning, retail 0x00232BED, 50 bytes. Startup gate
// (sole caller at 0x000030B0 tests the return): creates the launcher mutex
// and reports whether it already existed. BFME1's
// Code/GameEngine/Source/Common/System/CopyProtection.cpp gives the source;
// two release-build repairs: the DEBUG_LOG calls are compiled away, and the
// mutex name comes from the rowed ?GetRegistryG1@@YAPBDXZ lazy registry
// getter at 0x0002FA80 rather than a plain GUID constant (call, then
// push eax, push 0, push 0). Kept in its own TU so the caller cannot see
// (and inline) this body.
bool CopyProtect::isLauncherRunning(void)
{
	HANDLE launcherMutex = CreateMutexA(0, 0, GetRegistryG1());

	bool isRunning = (GetLastError() == ERROR_ALREADY_EXISTS);

	if (launcherMutex != 0)
	{
		CloseHandle(launcherMutex);
	}

	return isRunning;
}

// CopyProtect::notifyLauncher, retail 0x00232C1F, 236 bytes. Signals the
// launcher and waits for the mapped view. BFME1's
// Code/GameEngine/Source/Common/System/CopyProtection.cpp gives the source;
// two release-build repairs: the DEBUG_LOG calls are compiled away as in
// the matched siblings, and the protect GUID comes from the rowed
// ?GetRegistryG3@@YAPBDXZ getter at 0x0002FAC0 rather than a plain
// constant. Kept in its own TU so callers cannot see (and inline) it.
bool CopyProtect::notifyLauncher(void)
{
	MSG msg;
	PeekMessageA(&msg, 0, WM_USER, WM_USER, PM_NOREMOVE);

	unsigned long eventTime = timeGetTime() + 60000;
	HANDLE event = 0;

	while (timeGetTime() < eventTime)
	{
		event = OpenEventA(EVENT_MODIFY_STATE, 1, GetRegistryG3());
		if (event != 0)
		{
			break;
		}
		Sleep(0);
	}

	if (event != 0)
	{
		SetEvent(event);
		CloseHandle(event);

		unsigned long endTime = timeGetTime() + 10000;
		while (timeGetTime() <= endTime)
		{
			if (PeekMessageA(&msg, 0, 0xBEEF, 0xBEEF, PM_REMOVE))
			{
				if (msg.message == 0xBEEF)
				{
					HANDLE mappedFile = (HANDLE)msg.lParam;
					s_protectedData = MapViewOfFileEx(mappedFile, FILE_MAP_ALL_ACCESS, 0, 0, 0, 0);
					if (s_protectedData == 0)
					{
						break;
					}
					return true;
				}
			}
			Sleep(0);
		}
		return false;
	}
	else
	{
		return false;
	}
}

// CopyProtect::checkForMessage, retail 0x00232CE7, 37 bytes. Called from
// WndProc (Code/GameEngine/Source/Main/WinMain.cpp, matched at 0x0000179F)
// via the REL32 pinned in reverse/symbols.csv. Kept in its own TU so
// WndProc, already matched, cannot see (and inline) this body.
//
// Zero Hour's Common/CopyProtection.h / Source/Common/System/CopyProtection.cpp
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/...)
// give the source: on message 0xBEEF, treat lParam as a mapping handle and
// MapViewOfFileEx it into s_protectedData. This is a release build, so the
// DEBUG_LOG calls and the "if (s_protectedData == NULL) return" (a no-op --
// the function has nothing left to do either way) are compiled away.
void *CopyProtect::s_protectedData;

void CopyProtect::checkForMessage(UINT message, LPARAM lParam)
{
	if (message == 0xBEEF)
	{
		DWORD zero = 0;
		s_protectedData = MapViewOfFileEx((HANDLE)lParam, FILE_MAP_ALL_ACCESS, zero, zero, zero, (void *)zero);
	}
}

// ?rva00232D38@CopyProtect@@SA_NXZ, retail 0x00232D38, 43 bytes. Full-string
// gate beside CopyProtect::validate: when the launcher view is present it
// compares the whole view against the rowed ?GetRegistryG4@@YAPBDXZ string,
// returns true on equality and otherwise tail-calls validate (which checks
// the 'M' guard and the +1 comparison). Prev/next rows give the TU and /O1.
bool CopyProtect::rva00232D38(void)
{
	if (s_protectedData != 0)
	{
		char *data = (char *)s_protectedData;
		bool matched = strcmp(data, GetRegistryG4()) ? false : true;
		if (matched)
		{
			return matched;
		}
		return validate();
	}
	return false;
}

// CopyProtect::validate, retail 0x00232D0C, 44 bytes. Checks the launcher
// view starts with 'M' and matches the G4 registry string past the first
// byte. BFME1's Code/GameEngine/Source/Common/System/CopyProtection.cpp
// gives the source; two release-build repairs: the DEBUG_LOG calls are
// compiled away as in the matched siblings, and the expected text comes
// from the rowed ?GetRegistryG4@@YAPBDXZ getter at 0x0002FAE0 rather than
// a hardcoded Generals string. Kept in its own TU so callers cannot see
// (and inline) this body.
bool CopyProtect::validate(void)
{
	void *data = s_protectedData;
	if (data != 0 && *(char *)data == 'M')
	{
		return strcmp((char *)data + 1, GetRegistryG4() + 1) ? false : true;
	}
	return false;
}

// CopyProtect::shutdown, retail 0x00232D63, 24 bytes. Unmaps the launcher
// view and clears the handle. BFME1's
// Code/GameEngine/Source/Common/System/CopyProtection.cpp gives the source;
// release-build repair: the DEBUG_LOG call is compiled away, as in the
// matched isLauncherRunning and checkForMessage siblings. Kept in its own
// TU so callers cannot see (and inline) this body.
void CopyProtect::shutdown(void)
{
	if (s_protectedData != 0)
	{
		UnmapViewOfFile(s_protectedData);
		s_protectedData = 0;
	}
}
