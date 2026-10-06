// cl: /MD /EHsc
//
// The profile library's external dependencies, for the harness link only.
// Each stands in for another library's definition (debug library, WWLib);
// none is a profile symbol (subsystem_link.py refuses that).

#include <windows.h>
#include "../../../Code/Libraries/Source/debug/debug.h"
#include "../../../Code/Libraries/Source/WWVegas/WWLib/mutex.h"

Debug *theDebug;

bool Debug::SkipNext(bool)
{
	return false;
}

bool Debug::SimpleMatch(const char *str, const char *pattern)
{
	while (*str && *pattern)
	{
		if (*pattern == '*')
		{
			pattern++;
			while (*str)
				if (SimpleMatch(str++, pattern))
					return true;
			return *str == *pattern;
		}
		if (*str++ != *pattern++)
			return false;
	}
	return *str == *pattern;
}

void __fastcall FastCriticalSectionClass::LockClass::spin(void *lock)
{
	while (InterlockedExchange((LONG *)lock, 1))
		Sleep(0);
}
