// ?Rva004128F0GetParam@@YA_NPBD0AAVAsciiString@@@Z
// partial score=0.6 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// Rva004128F0GetParam @ 0x004128F0 (239B): query-string key lookup. Bank: logic and
// callees (strlen thunk, strncmp import, isspace import via the static
// skipSpaces at 0x00412689 with esi = &cursor) are complete; codegen differs.
#include "ascii_string.h"

#include <ctype.h>
#include <string.h>

static void skipSpaces(const char **p)
{
	while (**p && isspace(**p))
		++*p;
}

bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value)
{
	if (params == 0 || *params == 0 || key == 0 || *key == 0)
		return false;

	int keyLen = strlen(key);
	const char *p = params;
	for (;;)
	{
		skipSpaces(&p);
		if (*p == 0)
			return false;

		bool match;
		if (strncmp(p, key, keyLen) == 0)
		{
			const char *after = p + keyLen;
			skipSpaces(&after);
			if (*after == '=')
				match = true;
			else
				match = false;
		}
		else
		{
			match = false;
		}

		char c;
		while ((c = *p) != 0)
		{
			++p;
			if (c == '=')
				break;
		}
		skipSpaces(&p);

		if (match)
		{
			const char *start = p;
			const char *end = p;
			while (*end && *end != '&')
				++end;
			if (end == start)
				value.clear();
			else
				((StringBase<char> *)&value)->set(start, end - start);
			return true;
		}

		while ((c = *p) != 0)
		{
			++p;
			if (c == '&')
				break;
		}
	}
}
