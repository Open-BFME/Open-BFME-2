// cl: /DNDEBUG /MD
//
// ?rva002C7492@Rva002C7492@@QAEXPBV1@@Z @0x002C7492, 25B.
// 19-dword OR-merge: this[i] |= other[i]. Retail computes other-this once
// then loops with mov esi [eax+ecx] / or [ecx] esi over 0x13 dwords.
// Evidence: this is the 76-byte (0x4C) temp at [ebp-0x4C] in 0x002C777E and
// 0x0034707A copied via WeaponTemplateSetHead copy ctor at 0x00045455;
// arg is the 19-dword mask built by 0x002C760B. Same family as
// Rva00263546Overlap.cpp (19-dword overlap with sub eax ecx shape) and
// Rva00271C8ALoop.cpp (19-dword merge with push 0x13 pop dec-jne).
#include <string.h>

class Rva002C7492
{
public:
	void rva002C7492(const Rva002C7492 *other);
	Rva002C7492 *rva002C760B(int v0, int idx1, int idx2, int idx3, int idx4, int idx5, int idx6, int idx7);
private:
	int m_mask[19]; // +0x00
};

void Rva002C7492::rva002C7492(const Rva002C7492 *other)
{
	for (unsigned i = 0; i < 19; ++i) {
		m_mask[i] |= other->m_mask[i];
	}
}

// ?rva002C760B@Rva002C7492@@QAEPAV1@HHHHHHHH@Z @0x002C760B, 167B.
// 8-bit setter: memset 0x4C then set one bit per int arg (index val>>5).
// Evidence: sole caller 0x002C777E passes zero plus 7 bit ids per case;
// neighbour Rva002C76B2Build.cpp proves extern C memset import 0x6291AE
// and unsigned bit idiom; class layout int[19] from the OR-merge above.
Rva002C7492 *Rva002C7492::rva002C760B(int v0, int idx1, int idx2, int idx3, int idx4, int idx5, int idx6, int idx7)
{
	(void)v0;
	memset(this, 0, 0x4C);
	unsigned *bits = (unsigned *)m_mask;
	bits[(unsigned)idx1 >> 5] |= 1u << ((unsigned)idx1 & 31);
	bits[(unsigned)idx2 >> 5] |= 1u << ((unsigned)idx2 & 31);
	bits[(unsigned)idx3 >> 5] |= 1u << ((unsigned)idx3 & 31);
	bits[(unsigned)idx4 >> 5] |= 1u << ((unsigned)idx4 & 31);
	bits[(unsigned)idx5 >> 5] |= 1u << ((unsigned)idx5 & 31);
	bits[(unsigned)idx6 >> 5] |= 1u << ((unsigned)idx6 & 31);
	bits[(unsigned)idx7 >> 5] |= 1u << ((unsigned)idx7 & 31);
	return this;
}
