// cl: /MD /GX-
// stlport
// ?Rva002CF35CCopy@@YAXPAURva002CF120@@PBU1@@Z @0x002CF35C 18B.
// Null-guarded placement copy through the rowed 0x002CF120 copy ctor:
// if (dest) new (dest) Rva002CF120(*src). Test/je on the dest pointer then
// a thiscall to the ctor. Caller at 0x002CF861. The struct repeats the
// Rva002CF120Copy.cpp layout identically; its ctor stays declared-only here
// so the call resolves through its ledger row.
#include "Object872.h"
#include <new>

struct Rva002CF120
{
	BfmeObject872Header m_header;
	int m_field10;
	Rva002CF120(const Rva002CF120 &other);
};

void __cdecl Rva002CF35CCopy(Rva002CF120 *dest, const Rva002CF120 *src)
{
	if (dest != 0)
		new (dest) Rva002CF120(*src);
}
