// cl: /O1
// CopyProtect::notifyLauncher, retail 0x00232C1F, 236 bytes. Signals the
// launcher and waits for the mapped view. BFME1's
// Code/GameEngine/Source/Common/System/CopyProtection.cpp gives the source;
// two release-build repairs: the DEBUG_LOG calls are compiled away as in
// the matched siblings, and the protect GUID comes from the rowed
// ?GetRegistryG3@@YAPBDXZ getter at 0x0002FAC0 rather than a plain
// constant. Kept in its own TU so callers cannot see (and inline) it.

typedef void *HANDLE;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef long LPARAM;
typedef unsigned int WPARAM;

#define WINAPI __stdcall
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
extern "C" __declspec(dllimport) int WINAPI CloseHandle(HANDLE obj);
extern "C" __declspec(dllimport) void *WINAPI MapViewOfFileEx(HANDLE mapping, DWORD access,
	DWORD high, DWORD low, DWORD bytes, void *base);

const char *GetRegistryG3(void);

class CopyProtect
{
public:
	static bool notifyLauncher(void);

private:
	static void *s_protectedData;
};

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
