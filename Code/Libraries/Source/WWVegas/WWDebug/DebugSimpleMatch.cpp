// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug

// TU-scoped declarations (mirrors Rva0088A7E0UpdateFrameStatus.cpp in this
// directory, which already calls Debug::SimpleMatch).
#include "../../../../GameEngine/Source/Common/debug.h"

// BFME wildcard comparison ported from reference/open-bfme-1/.../DebugSimpleMatch.cpp:
// unlike the Zero Hour body (kept in debug_debug.cpp), BFME folds ASCII
// uppercase on the input only.
#pragma optimize("y", off)

// ?SimpleMatch@Debug@@SA_NPBD0@Z
bool Debug::SimpleMatch(const char *str, const char *pattern)
{
	for (;;) {
		if (*str == 0)
			break;
		if (*pattern == 0)
			break;
		if (*pattern == '*')
			break;

		if (*str >= 'A' && *str <= 'Z') {
			if ((*str++ + ('a' - 'A')) != *pattern++)
				return false;
			continue;
		}

		char s = *str;
		char p = *pattern;
		++pattern;
		++str;
		if (s == p)
			continue;
		return false;
	}

	if (*pattern == '*') {
		++pattern;
		while (*str)
			if (SimpleMatch(str++, pattern))
				return true;
		return *str == *pattern;
	}
	return *str == *pattern;
}
