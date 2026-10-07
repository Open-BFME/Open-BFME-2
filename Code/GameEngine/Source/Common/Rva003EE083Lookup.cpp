// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /MD /EHs-c-
//
// ?rva003EE083@Rva003EE083@@QAEPAXABVAsciiString@@@Z @0x003EE083 76B.
// Caller 0x00568718 in Rva005686F5Lookup.cpp; adjacent BitRange names are
// confirmed by the rowed 0x00568BE2 method and the caller's two-string entry.
#include "ascii_string.h"

struct BitRange
{
	unsigned const *m_begin;
	unsigned const *m_end;
	unsigned char m_pad08[8];
	AsciiString m_str10;
	AsciiString rva00568BE2();
};

class Rva003EE083
{
	unsigned char m_pad00[0x1c];
	BitRange **m_begin;
	BitRange **m_end;

public:
	void *rva003EE083(const AsciiString &arg);
};

void *Rva003EE083::rva003EE083(const AsciiString &arg)
{
	BitRange **item = m_begin;
	while (item != m_end)
	{
		unsigned char equal;
		{
			equal = (unsigned char)((*item)->rva00568BE2().compareNoCase(arg) == 0);
		}
		if (equal != 0)
			return *item;
		++item;
	}
	return 0;
}
