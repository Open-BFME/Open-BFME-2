// cl: /O1
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

typedef unsigned int UINT;
typedef long LPARAM;
typedef unsigned long DWORD;
typedef void *HANDLE;
typedef int BOOL;

#define WINAPI __stdcall
#define FILE_MAP_ALL_ACCESS 0xF001F

extern "C" __declspec(dllimport) void *WINAPI MapViewOfFileEx(HANDLE hFileMappingObject, DWORD dwDesiredAccess,
                                                                DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow,
                                                                DWORD dwNumberOfBytesToMap, void *lpBaseAddress);

class CopyProtect
{
public:
	static void checkForMessage(UINT message, LPARAM lParam);

private:
	static void *s_protectedData;
};

void *CopyProtect::s_protectedData;

void CopyProtect::checkForMessage(UINT message, LPARAM lParam)
{
	if (message == 0xBEEF)
	{
		DWORD zero = 0;
		s_protectedData = MapViewOfFileEx((HANDLE)lParam, FILE_MAP_ALL_ACCESS, zero, zero, zero, (void *)zero);
	}
}
