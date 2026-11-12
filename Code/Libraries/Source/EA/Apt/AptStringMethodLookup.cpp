// cl: /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
#include <string.h>

#include "../../../../GameEngine/Include/Common/R4Word.h"

int bfmeSkipVE(const unsigned char *text, int length);

// Complete native method records at VA 0xDDC030..0xDDC098. The names and
// integer selectors are target data; the address-derived function/type names
// retain the original recovery's uncertainty about the C++ owner.
extern const R4Word g008A9710[13] = {
	{ "split", 9 },
	{ "charAt", 2 },
	{ "concat", 4 },
	{ "indexOf", 6 },
	{ "substring", 11 },
	{ "charCodeAt", 3 },
	{ "lastIndexOf", 7 },
	{ "slice", 8 },
	{ "length", 1 },
	{ "substr", 10 },
	{ "toLowerCase", 12 },
	{ "toUpperCase", 13 },
	{ "fromCharCode", 5 }
};
// VA 0xDDC098: 23 signed lookup bytes plus the native zero alignment byte.
// Negative entries encode collision spans used by the second search loop.
extern const signed char g008A9710lookup[24] = {
	-1, -1, -1, -1, -1, 0, -26, 3, -1, 4, 5, 6,
	-12, -2, -1, 7, 8, -1, -3, -2, 9, -32, 12, 0
};

const R4Word *Rva008A9710(const char *str, unsigned int len)
{
	if (len <= 12 && len >= 5)
	{
		register int key = bfmeSkipVE((const unsigned char *)str, (int)len);
		if (key <= 0x16 && key >= 0)
		{
			register int index = g008A9710lookup[key];
			if (index >= 0)
			{
				register const char *s = g008A9710[index].name;
				if (*str == *s && !strcmp(str + 1, s + 1))
					return &g008A9710[index];
			}
			else if (index < -13)
			{
				register int offset = -1 - 13 - index;
				register const R4Word *wordptr = (g008A9710 + 13) + g008A9710lookup[offset];
				register const R4Word *wordendptr = wordptr - g008A9710lookup[offset + 1];
				while (wordptr < wordendptr)
				{
					register const char *s = wordptr->name;
					if (*str == *s && !strcmp(str + 1, s + 1))
						return wordptr;
					wordptr++;
				}
			}
		}
	}
	return 0;
}
