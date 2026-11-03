// cl: /DNDEBUG /MD /EHsc
// ?Rva004110DCGet@@YAPAXPBD@Z, retail 0x004110DC (54B).
// Chain over rowed ?rva00056F61@Rva00056F61@@QAEPAXPBVAsciiString@@@Z with a
// temp AsciiString from char*: lookup in global table at 0x00E02FF8,
// teardown via rowed releaseBuffer 0x00036410, returning node+8 or null.
// Same shape as rowed-adjacent 0x00411112 plus temp; caller at 0x004120C0.

class AsciiString;

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../Include/GameClient/Rva00056F61.h"

// g_Va00E02FF8: VA 0x00E02FF8 (.data/bss), defined by its data-row owner
// Rva004121B2HashMapInits.cpp. Retail's 0x14-byte bucket-table header is
// zero-filled; Find reads begin/end at +4/+8 and the rowed insert view
// establishes capacity/count at +0xC/+0x10.
extern unsigned g_Va00E02FF8;

void * __cdecl Rva004110DCGet(const char *key)
{
	void *node;
	{
		AsciiString tmp(key);
		node = reinterpret_cast<Rva00056F61 *>(&g_Va00E02FF8)->rva00056F61(&tmp);
	}
	if (node != 0)
		return *(void **)((char *)node + 8);
	return 0;
}
