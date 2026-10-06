// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00411112Get@@YAPAXPBVAsciiString@@@Z, retail 0x00411112 (25B).
// Chain over rowed ?rva00056F61@Rva00056F61@@QAEPAXPBVAsciiString@@@Z: lookup
// AsciiString key in the global bucket table at 0x00E0300C, returning the
// dword at node+8 or null. Caller at 0x00412140 tests for null.

#include "ascii_string.h"

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);
};

struct Rva00411112GlobalTable
{
	void *m_unused;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_capacity;
	unsigned int m_numElements;
};

// Same 0x14-byte bucket-table view as the rowed adjacent tables at 0x00E02FE4
// and 0x00E02FF8. This header is zero-filled in the target's BSS image.
Rva00411112GlobalTable g_Va00E0300C;

void * __cdecl Rva00411112Get(const AsciiString *key)
{
	void *node = reinterpret_cast<Rva00056F61 *>(&g_Va00E0300C)->rva00056F61(key);
	if (node != 0)
		return *(void **)((char *)node + 8);
	return 0;
}
