// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva00573B23@@UAE@XZ @0x00573B23 59B
// Dtor: vptr store, inline StringBase<char> member dtor at +0x2c (inlined to
// a direct releaseBuffer call, arming EH state 0), then the virtual public
// base dtor ??1Rva0055B0CC@@UAE@XZ (pin-only). Empty body: everything implicit.
// Evidence: mov [esi] vtable, and [ebp-4]0, lea ecx [esi+2c] call
// releaseBuffer@StringBase@D, or [ebp-4]-1, mov ecx esi call 0x0055B0CC.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"


struct Rva0055B0CC
{
	virtual ~Rva0055B0CC();
};
struct Rva00573B23 : Rva0055B0CC
{
	char m_pad04[0x28];
	StringBase<char> m_2c;
	virtual ~Rva00573B23();
};
Rva00573B23::~Rva00573B23()
{
}
// ??1Rva00573F03@@UAE@XZ @0x00573F03 11B
// Derived dtor: stores its own vtable, then tail-jumps to the rowed base
// dtor ??1Rva00573B23@@UAE@XZ. Empty body, no new members.
// Evidence: mov [ecx] 0x0086E2C8 then jmp 0x00573B23.
struct Rva00573F03 : Rva00573B23
{
	virtual ~Rva00573F03();
};
Rva00573F03::~Rva00573F03()
{
}
