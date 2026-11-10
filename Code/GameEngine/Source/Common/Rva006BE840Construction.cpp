// BFME2 construction workers: 0x006BE840/126B and 0x006BE8C0/115B.
// Donor: Open-BFME-1 10af19f44a89ab7ecc23195bb9a842ceafbc02c9,
// game/GameEngine/Source/Common/Rva0087F020FillBE.cpp. Keep its /O2 /Ob1
// /G6 /GX- and nested aggregate to reproduce the two induction cursors.
// Target evidence: Ghidra boundaries; both loops copy seven DWORDs, share
// the string at +0x1C through 0x000365F0, and copy bytes +0x20 and +0x21.
// The second byte is the BFME2-specific repair. Application identity and
// scalar meanings remain unknown; the grouping is a code-generation view.
// Caller 0x006BF800 uses these as STLport uninitialized_copy/fill_n workers,
// passing a fourth empty tag argument. The copy loop follows that source.
// BfmeTailBE is a one-pointer ABI view of the existing StringBase copy
// operation; its linker alias binds to the byte-verified private constructor.
// cl: /O2 /Ob1 /G6 /GX-

#include <new.h>

// The 0x24-byte element's member group at +0x10: the three dwords the matched
// siblings Rva0087EAA0Copy.cpp and Rva0087E9B0Fill.cpp spell BfmeCoordXX m_10,
// then the StringBase<char> tail whose copy ctor is the one out-of-line call
// this body makes (0x00887B60), then the flag byte at +0x20.
//
// Retail keeps a SECOND induction variable for this group: esi is seeded at
// first+0x18 and reaches the group's earlier fields with negative
// displacements (-0x14 .. -8). MSVC 7.1 only splits the implicit copy ctor
// into two cursors when the group is its own aggregate member, so the
// nesting here is what the byte-verified body witnesses, not a free choice.


struct BfmeFalseBE
{
};

struct BfmeTailBE
{
	char *m_p;
	BfmeTailBE(const BfmeTailBE &);
};

struct BfmeGroup10BE
{
	int m_10;
	int m_14;
	int m_18;
	BfmeTailBE m_1C;
	char m_20;
	char m_21;
};

struct BfmeElemBE
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeGroup10BE m_10;
};

// Export forces this inline worker to emit a foldable COMDAT. The insertion
// unit emits the same verified worker; an exclusive definition conflicts.
__declspec(noinline) __declspec(dllexport) inline BfmeElemBE *bfmeFillBE(BfmeElemBE *first, unsigned count,
	const BfmeElemBE &value, const BfmeFalseBE &)
{
	BfmeElemBE *cur = first;
	while (count > 0)
	{
		if (cur != 0)
			new (cur) BfmeElemBE(value);
		++cur;
		--count;
	}
	return cur;
}

BfmeElemBE *bfmeCopyBE(const BfmeElemBE *first, const BfmeElemBE *last,
    BfmeElemBE *result, const BfmeFalseBE &)
{
    BfmeElemBE *cur = result;
    for (; first != last; ++first, ++cur)
        if (cur != 0)
            new (cur) BfmeElemBE(*first);
    return cur;
}
