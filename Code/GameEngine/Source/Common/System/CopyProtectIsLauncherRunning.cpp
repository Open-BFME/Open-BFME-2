// flags: region default (reverse/retail_inventory/flag_regions.csv)
// CopyProtect::isLauncherRunning, retail 0x00232BED, 50 bytes. Startup gate
// (sole caller at 0x000030B0 tests the return): creates the launcher mutex
// and reports whether it already existed. BFME1's
// Code/GameEngine/Source/Common/System/CopyProtection.cpp gives the source;
// two release-build repairs: the DEBUG_LOG calls are compiled away, and the
// mutex name comes from the rowed ?GetRegistryG1@@YAPBDXZ lazy registry
// getter at 0x0002FA80 rather than a plain GUID constant (call, then
// push eax, push 0, push 0). Kept in its own TU so the caller cannot see
// (and inline) this body.

typedef void *HANDLE;
typedef unsigned long DWORD;

#define WINAPI __stdcall
#define ERROR_ALREADY_EXISTS 183

extern "C" __declspec(dllimport) HANDLE WINAPI CreateMutexA(void *attrs, int owned, const char *name);
extern "C" __declspec(dllimport) DWORD WINAPI GetLastError(void);
extern "C" __declspec(dllimport) int WINAPI CloseHandle(HANDLE obj);

const char *GetRegistryG1(void);

class CopyProtect
{
public:
	static bool isLauncherRunning(void);
};

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
