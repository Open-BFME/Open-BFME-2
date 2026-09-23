// cl: /O1
// CopyProtect::shutdown, retail 0x00232D63, 24 bytes. Unmaps the launcher
// view and clears the handle. BFME1's
// Code/GameEngine/Source/Common/System/CopyProtection.cpp gives the source;
// release-build repair: the DEBUG_LOG call is compiled away, as in the
// matched isLauncherRunning and checkForMessage siblings. Kept in its own
// TU so callers cannot see (and inline) this body.

typedef void *HANDLE;
typedef int BOOL;

#define WINAPI __stdcall

extern "C" __declspec(dllimport) BOOL WINAPI UnmapViewOfFile(void *lpBaseAddress);

class CopyProtect
{
public:
	static void shutdown(void);

private:
	static void *s_protectedData;
};

void CopyProtect::shutdown(void)
{
	if (s_protectedData != 0)
	{
		UnmapViewOfFile(s_protectedData);
		s_protectedData = 0;
	}
}
