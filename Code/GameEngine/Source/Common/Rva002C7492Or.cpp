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

class Rva002C7492
{
public:
	void rva002C7492(const Rva002C7492 *other);
	Rva002C7492 *rva002C760B(int v0, int v1, int v2, int v3, int v4, int v5, int v6, int v7);

private:
	int m_mask[19];
};

extern "C" void *memset(void *dst, int c, unsigned n);

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
Rva002C7492 *Rva002C7492::rva002C760B(int v0, int v1, int v2, int v3, int v4, int v5, int v6, int v7)
{
	(void)v0;
	memset(this, 0, 0x4C);
	unsigned *bits = (unsigned *)m_mask;
	bits[(unsigned)v1 >> 5] |= 1u << ((unsigned)v1 & 31);
	bits[(unsigned)v2 >> 5] |= 1u << ((unsigned)v2 & 31);
	bits[(unsigned)v3 >> 5] |= 1u << ((unsigned)v3 & 31);
	bits[(unsigned)v4 >> 5] |= 1u << ((unsigned)v4 & 31);
	bits[(unsigned)v5 >> 5] |= 1u << ((unsigned)v5 & 31);
	bits[(unsigned)v6 >> 5] |= 1u << ((unsigned)v6 & 31);
	bits[(unsigned)v7 >> 5] |= 1u << ((unsigned)v7 & 31);
	return this;
}
