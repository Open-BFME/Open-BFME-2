// cl: /MD /GX /Ireference/shims/bfme2_ascii
// ??1Rva004211CA@@UAE@XZ @ 0x004211CA 92B
// Dtor with vtable 0x0083BDFC, Ascii at +0x10, Unicode at +0x14, heap at +0x18
// freed via _free, then base Overridable pinned dtor. Unblocks deleting dtor
// 0x00421226. Layout from member offsets, base size 0x10 from first member.
// Evidence: mov [esi] vtable, test+free +0x18, releaseBuffer +0x14 wide
// +0x10 narrow, base call 0x001E3624, caller 0x00421229, neighbours
// 0x004210B0 and 0x0042169B.
//
// The canonical frozen StringBase replaces the private copy; the switch
// declares the char destructor so both teardowns call the rowed workers
// (0x0048BA39 for char, 0x00036410 for the wide releaseBuffer).

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

class Overridable
{
public:
	virtual ~Overridable();
private:
	char m_pad[0x0C];
};

class Rva004211CA : public Overridable
{
public:
	virtual ~Rva004211CA();
private:
	StringBase<char> m_ansi10;
	StringBase<unsigned short> m_wide14;
	void *m_heap18;
};

Rva004211CA::~Rva004211CA()
{
	if (m_heap18)
		free(m_heap18);
}
